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


#include "keyboards/fingerpunch/fp_rgb_common.h"

// We must make sure that fp_rgb_matrix.h or fp_rgblight.h are included before this, since it depends on FP_LAYER_LIGHTING_MODE
#ifdef RGBLIGHT_ENABLE
#include "keyboards/fingerpunch/fp_rgblight.h"
#endif

#ifdef RGB_MATRIX_ENABLE
#include "keyboards/fingerpunch/fp_rgb_matrix.h"
#endif

#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
#    ifndef FP_LAYER_LIGHTING_HUE_0
#        define FP_LAYER_LIGHTING_HUE_0 HSV_BLUE
#    endif // FP_LAYER_LIGHTING_HUE_0

#    ifndef FP_LAYER_LIGHTING_HUE_1
#        define FP_LAYER_LIGHTING_HUE_1 HSV_WHITE
#    endif // FP_LAYER_LIGHTING_HUE_1

#    ifndef FP_LAYER_LIGHTING_HUE_2
#        define FP_LAYER_LIGHTING_HUE_2 HSV_GREEN
#    endif // FP_LAYER_LIGHTING_HUE_2

#    ifndef FP_LAYER_LIGHTING_HUE_3
#        define FP_LAYER_LIGHTING_HUE_3 HSV_PURPLE
#    endif // FP_LAYER_LIGHTING_HUE_3

#    ifndef FP_LAYER_LIGHTING_HUE_4
#        define FP_LAYER_LIGHTING_HUE_4 HSV_YELLOW
#    endif // FP_LAYER_LIGHTING_HUE_4

#    ifndef FP_LAYER_LIGHTING_HUE_5
#        define FP_LAYER_LIGHTING_HUE_5 HSV_MAGENTA
#    endif // FP_LAYER_LIGHTING_HUE_5

#    ifndef FP_LAYER_LIGHTING_HUE_6
#        define FP_LAYER_LIGHTING_HUE_6 HSV_CYAN
#    endif // FP_LAYER_LIGHTING_HUE_6

#    ifndef FP_LAYER_LIGHTING_HUE_7
#        define FP_LAYER_LIGHTING_HUE_7 HSV_SPRINGGREEN
#    endif // FP_LAYER_LIGHTING_HUE_7

#    ifndef FP_LAYER_LIGHTING_MODE_0
#        define FP_LAYER_LIGHTING_MODE_0 FP_LAYER_LIGHTING_MODE
#    endif // FP_LAYER_LIGHTING_MODE_0

#    ifndef FP_LAYER_LIGHTING_MODE_1
#        define FP_LAYER_LIGHTING_MODE_1 FP_LAYER_LIGHTING_MODE
#    endif // FP_LAYER_LIGHTING_MODE_1

#    ifndef FP_LAYER_LIGHTING_MODE_2
#        define FP_LAYER_LIGHTING_MODE_2 FP_LAYER_LIGHTING_MODE
#    endif // FP_LAYER_LIGHTING_MODE_2

#    ifndef FP_LAYER_LIGHTING_MODE_3
#        define FP_LAYER_LIGHTING_MODE_3 FP_LAYER_LIGHTING_MODE
#    endif // FP_LAYER_LIGHTING_MODE_3

#    ifndef FP_LAYER_LIGHTING_MODE_4
#        define FP_LAYER_LIGHTING_MODE_4 FP_LAYER_LIGHTING_MODE
#    endif // FP_LAYER_LIGHTING_MODE_4

#    ifndef FP_LAYER_LIGHTING_MODE_5
#        define FP_LAYER_LIGHTING_MODE_5 FP_LAYER_LIGHTING_MODE
#    endif // FP_LAYER_LIGHTING_MODE_5

#    ifndef FP_LAYER_LIGHTING_MODE_6
#        define FP_LAYER_LIGHTING_MODE_6 FP_LAYER_LIGHTING_MODE
#    endif // FP_LAYER_LIGHTING_MODE_6

#    ifndef FP_LAYER_LIGHTING_MODE_7
#        define FP_LAYER_LIGHTING_MODE_7 FP_LAYER_LIGHTING_MODE
#    endif // FP_LAYER_LIGHTING_MODE_7

#    ifndef FP_LAYER_LIGHTING_AUTO_MOUSE_HUE
#        define FP_LAYER_LIGHTING_AUTO_MOUSE_HUE HSV_ORANGE
#    endif // FP_LAYER_LIGHTING_AUTO_MOUSE_HUE

#    ifndef FP_LAYER_LIGHTING_AUTO_MOUSE_MODE
#        define FP_LAYER_LIGHTING_AUTO_MOUSE_MODE FP_LAYER_LIGHTING_MODE
#    endif // FP_LAYER_LIGHTING_AUTO_MOUSE_HUE

#    ifndef FP_LAYER_LIGHTING_CAPS_LOCK_HUE
#        define FP_LAYER_LIGHTING_CAPS_LOCK_HUE HSV_RED
#    endif // FP_LAYER_LIGHTING_AUTO_MOUSE_HUE

#    ifndef FP_LAYER_LIGHTING_CAPS_LOCK_MODE
#        define FP_LAYER_LIGHTING_CAPS_LOCK_MODE FP_LAYER_LIGHTING_MODE
#    endif // FP_LAYER_LIGHTING_AUTO_MOUSE_HUE

layer_state_t fp_layer_state_set_rgb(layer_state_t state) {
    switch (get_highest_layer(state)) {
        // TODO: This logic is clearly flawed, decide what to do with this
#       if defined(FP_LAYER_LIGHTING_ENABLE) && defined(AUTO_MOUSE_DEFAULT_LAYER) && !defined(FP_LAYER_LIGHTING_ENABLE)
        case AUTO_MOUSE_DEFAULT_LAYER:
            fp_rgb_set_hsv_and_mode(FP_LAYER_LIGHTING_AUTO_MOUSE_HUE, FP_LAYER_LIGHTING_AUTO_MOUSE_MODE);
            break;
#       endif
        case 0:
#           ifdef FP_LAYER_LIGHTING_ENABLE
            if (fp_caps_lock_get()) {
                fp_rgb_set_hsv_and_mode(FP_LAYER_LIGHTING_CAPS_LOCK_HUE, FP_LAYER_LIGHTING_CAPS_LOCK_MODE);
            } else {
                fp_rgb_set_hsv_and_mode(FP_LAYER_LIGHTING_HUE_0, FP_LAYER_LIGHTING_MODE_0);
            }
#           endif
            break;
        case 1:
#           ifdef FP_LAYER_LIGHTING_ENABLE
            fp_rgb_set_hsv_and_mode(FP_LAYER_LIGHTING_HUE_1, FP_LAYER_LIGHTING_MODE_1);
#           endif
            break;
        case 2:
#           ifdef FP_LAYER_LIGHTING_ENABLE
            fp_rgb_set_hsv_and_mode(FP_LAYER_LIGHTING_HUE_2, FP_LAYER_LIGHTING_MODE_2);
#           endif
            break;
        case 3:
#           ifdef FP_LAYER_LIGHTING_ENABLE
            fp_rgb_set_hsv_and_mode(FP_LAYER_LIGHTING_HUE_3, FP_LAYER_LIGHTING_MODE_3);
#           endif
            break;
        case 4:
#           ifdef FP_LAYER_LIGHTING_ENABLE
            fp_rgb_set_hsv_and_mode(FP_LAYER_LIGHTING_HUE_4, FP_LAYER_LIGHTING_MODE_4);
#           endif
            break;
        case 5:
#           ifdef FP_LAYER_LIGHTING_ENABLE
            fp_rgb_set_hsv_and_mode(FP_LAYER_LIGHTING_HUE_5, FP_LAYER_LIGHTING_MODE_5);
#           endif
            break;
        case 6:
#           ifdef FP_LAYER_LIGHTING_ENABLE
            fp_rgb_set_hsv_and_mode(FP_LAYER_LIGHTING_HUE_6, FP_LAYER_LIGHTING_MODE_6);
#           endif
            break;
        case 7:
#           ifdef FP_LAYER_LIGHTING_ENABLE
            fp_rgb_set_hsv_and_mode(FP_LAYER_LIGHTING_HUE_7, FP_LAYER_LIGHTING_MODE_7);
#           endif
            break;
        default:
            // default to layer 0 behavior
#           ifdef FP_LAYER_LIGHTING_ENABLE
            fp_rgb_set_hsv_and_mode(FP_LAYER_LIGHTING_HUE_0, FP_LAYER_LIGHTING_MODE_0);
#           endif
            break;
    }
    return state;
}
#endif
