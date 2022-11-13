/* Copyright 2022 Sadek Baroudi
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "keyboards/fingerpunch/fp_pointing.h"
#include "math.h"

#ifdef POINTING_DEVICE_ENABLE

static bool scrolling_enabled = false;
static bool scrolling_layer_enabled = false;
static bool sniping_enabled = false;
static bool sniping_layer_enabled = false;
static bool zooming_enabled = false;
static bool zooming_layer_enabled = false;
static bool zooming_hold = false;

void fp_scroll_layer_set(bool scroll_value) {
    scrolling_layer_enabled = scroll_value;
    fp_scroll_apply_dpi();
}

void fp_scroll_keycode_set(bool scroll_value) {
    scrolling_enabled = scroll_value;
    fp_scroll_apply_dpi();
}

void fp_scroll_keycode_toggle(void) {
    scrolling_enabled = !scrolling_enabled;
    fp_scroll_apply_dpi();
}

bool fp_scroll_get(void) {
    return (scrolling_enabled || scrolling_layer_enabled);
}

void fp_scroll_apply_dpi(void) {
    // We don't want to apply the dpi change if sniping mode is enabled, since that will win!
    if(!fp_snipe_get()) {
        if(fp_scroll_get()) {
            pointing_device_set_cpi(FP_POINTING_SCROLLING_DPI);
        } else {
#ifdef POINTING_DEVICE_COMBINED
            fp_pointing_device_set_cpi_combined_defaults();
#else
            pointing_device_set_cpi(FP_POINTING_DEFAULT_DPI);
#endif
        }
    }
}

void fp_snipe_layer_set(bool snipe_value) {
    sniping_layer_enabled = snipe_value;
    fp_snipe_apply_dpi();
}

void fp_snipe_keycode_set(bool snipe_value) {
    sniping_enabled = snipe_value;
    fp_snipe_apply_dpi();
}

void fp_snipe_keycode_toggle(void) {
    sniping_enabled = !sniping_enabled;
    fp_snipe_apply_dpi();
}

bool fp_snipe_get(void) {
    return (sniping_enabled || sniping_layer_enabled);
}

void fp_snipe_apply_dpi(void) {
    if(fp_snipe_get()) {
        pointing_device_set_cpi(FP_POINTING_SNIPING_DPI);
    } else {
        pointing_device_set_cpi(FP_POINTING_DEFAULT_DPI);
    }
}

void fp_zoom_layer_set(bool zoom_value) {
    zooming_layer_enabled = zoom_value;
}

void fp_zoom_keycode_set(bool zoom_value) {
    zooming_enabled = zoom_value;
}

void fp_zoom_keycode_toggle(void) {
    zooming_enabled = !zooming_enabled;
}

bool fp_zoom_get(void) {
    return (zooming_enabled || zooming_layer_enabled);
}

uint32_t fp_zoom_unset_hold(uint32_t triger_time, void *cb_arg) {
    zooming_hold = false;
    return 0;
}

report_mouse_t pointing_device_task_kb(report_mouse_t mouse_report) {
    if (fp_scroll_get()) {
        mouse_report.h = mouse_report.x;
        mouse_report.v = -mouse_report.y;
        mouse_report.x = 0;
        mouse_report.y = 0;
    } else if (fp_zoom_get()) {
        bool zoom_in = false;
        mouse_xy_report_t zoom_value = mouse_report.y;
        if (zoom_value < 0) {
            zoom_in = true;
            zoom_value = -zoom_value;
        }

#ifdef FP_MAC_PREFERRED
        register_code(KC_LGUI);
#else
        register_code(KC_LCTL);
#endif
        // Set timer to prevent mass zoom and set threshold for zoom value, otherwise too sensitive
        if (!zooming_hold && zoom_value > 1) {
            zooming_hold = true;
            defer_exec(50, fp_zoom_unset_hold, NULL);
            if (zoom_in) {
                tap_code(KC_MS_WH_UP);
            } else {
                tap_code(KC_MS_WH_DOWN);
            }
        }
#ifdef FP_MAC_PREFERRED
        unregister_code(KC_LGUI);
#else
        unregister_code(KC_LCTL);
#endif
        mouse_report.h = 0;
        mouse_report.v = 0;
        mouse_report.x = 0;
        mouse_report.y = 0;

    }

    mouse_report = pointing_device_task_user(mouse_report);
    return mouse_report;
}

layer_state_t fp_layer_state_set_pointing(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case FP_POINTING_SCROLLING_LAYER:
#ifdef FP_POINTING_SCROLLING_LAYER_ENABLE
            fp_scroll_layer_set(true);
#endif
            break;
        case FP_POINTING_SNIPING_LAYER:
#ifdef FP_POINTING_SNIPING_LAYER_ENABLE
            fp_snipe_layer_set(true);
#endif
            break;
        case FP_POINTING_ZOOMING_LAYER:
#ifdef FP_POINTING_ZOOMING_LAYER_ENABLE
            fp_zoom_layer_set(true);
#endif
            break;
#ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
        case AUTO_MOUSE_DEFAULT_LAYER:
            // Do nothing, but this needs to exist so we don't go into the "default" below and automatically
            // disable the scroll/snipe adjustments because we used the pointing device
            // Problem happens when POINTING_DEVICE_AUTO_MOUSE_ENABLE and FP_POINTING_SCROLLING_LAYER_ENABLE or
            // FP_POINTING_SNIPING_LAYER_ENABLE are enabled at the samet time
            break;
#endif
        default:
            if (scrolling_layer_enabled) {
#ifdef FP_POINTING_SCROLLING_LAYER_ENABLE
                fp_scroll_layer_set(false);
#endif
            }
            if (sniping_layer_enabled) {
#ifdef FP_POINTING_SNIPING_LAYER_ENABLE
                fp_snipe_layer_set(false);
#endif
            }
            if (zooming_layer_enabled) {
#ifdef FP_POINTING_ZOOMING_LAYER_ENABLE
                fp_zoom_layer_set(false);
#endif
            }
            break;
    }
    return state;
}

#ifdef POINTING_DEVICE_COMBINED
report_mouse_t pointing_device_task_combined_kb(report_mouse_t left_report, report_mouse_t right_report) {
    if (FP_POINTING_COMBINED_SCROLLING_LEFT) {
        left_report.h = left_report.x;
        left_report.v = -left_report.y;
        left_report.x = 0;
        left_report.y = 0;
    }

    if (FP_POINTING_COMBINED_SCROLLING_RIGHT) {
        right_report.h = right_report.x;
        right_report.v = -right_report.y;
        right_report.x = 0;
        right_report.y = 0;
    }

    return pointing_device_task_combined_user(left_report, right_report);
}

void fp_pointing_device_set_cpi_combined_defaults(void) {
    pointing_device_set_cpi_on_side(true, FP_POINTING_SCROLLING_DPI); //Set cpi on left side to a low value for slower scrolling.
    pointing_device_set_cpi_on_side(false, FP_POINTING_DEFAULT_DPI); //Set cpi on right side to a reasonable value for mousing.
}
#endif

void pointing_device_init_kb(void) {
#   ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
    set_auto_mouse_enable(true);         // always required before the auto mouse feature will work
#   endif

    pointing_device_init_user();
}

#ifdef FP_TRACKBALL_ENABLE
// Override when using a trackball so that you can account for acciental triggers due to a sensitive sensor
bool auto_mouse_activation(report_mouse_t mouse_report) {
    // If we're in sniping mode, lower the threshold, otherwise give it some room to move for accidental triggers of auto mouse layer
    if (fp_snipe_get()) {
        return fabs(mouse_report.x) >= 0.5 || fabs(mouse_report.y) >= 0.5 || fabs(mouse_report.h) >= 0.5 || fabs(mouse_report.v) >= 0.5 || mouse_report.buttons;
    } else {
        return fabs(mouse_report.x) >= FP_AUTO_MOUSE_TRACKBALL_SENSITIVITY ||
               fabs(mouse_report.y) >= FP_AUTO_MOUSE_TRACKBALL_SENSITIVITY ||
               fabs(mouse_report.h) >= FP_AUTO_MOUSE_TRACKBALL_SENSITIVITY ||
               fabs(mouse_report.v) >= FP_AUTO_MOUSE_TRACKBALL_SENSITIVITY ||
               mouse_report.buttons;
    }
}
#endif

bool fp_process_record_pointing(uint16_t keycode, keyrecord_t *record) {
#   ifndef FP_DISABLE_CUSTOM_KEYCODES
    switch (keycode) {
        case FP_SCROLL_TOG:
            if (record->event.pressed) {
                fp_scroll_keycode_toggle();
            }
            break;
        case FP_SCROLL_ON:
            if (record->event.pressed) {
                fp_scroll_keycode_set(true);
            }
            break;
        case FP_SCROLL_OFF:
            if (record->event.pressed) {
                fp_scroll_keycode_set(true);
            }
            break;
        case FP_SNIPE_TOG:
            if (record->event.pressed) {
                fp_snipe_keycode_toggle();
            }
            break;
        case FP_SNIPE_ON:
            if (record->event.pressed) {
                fp_snipe_keycode_set(true);
            }
            break;
        case FP_SNIPE_OFF:
            if (record->event.pressed) {
                fp_snipe_keycode_set(true);
            }
            break;
        case FP_ZOOM_TOG:
            if (record->event.pressed) {
                fp_zoom_keycode_toggle();
            }
            break;
        case FP_ZOOM_ON:
            if (record->event.pressed) {
                fp_zoom_keycode_set(true);
            }
            break;
        case FP_ZOOM_OFF:
            if (record->event.pressed) {
                fp_zoom_keycode_set(true);
            }
            break;
        default:
            break;
    }
#   endif // FP_DISABLE_CUSTOM_KEYCODES

    return true;
}

#endif
