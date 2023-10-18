/* Copyright 2023 Sadek Baroudi
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

#include "keyboards/fingerpunch/src/display/fp_display.h"
#include "keyboards/fingerpunch/src/display/gc9a01.h"

#ifdef QUANTUM_PAINTER_ENABLE
#include "qp.h"

painter_device_t lcd;

void fp_post_init_qp(void) {
    lcd = qp_gc9a01_make_spi_device(FP_QP_DISPLAY_WIDTH, FP_QP_DISPLAY_HEIGHT, DISPLAY_CS_PIN, DISPLAY_DC_PIN, DISPLAY_RST_PIN, 4, 0);
    qp_init(lcd, QP_ROTATION_0);
    qp_rect(lcd, 0, 0, 239, 319, 0, 255, 255, true);

    if (qp_lvgl_attach(lcd)) {
        fp_qp_load_initial_screen();
    }
}

static void fp_qp_set_arc_angle(void* obj, int32_t v) {
    lv_arc_set_value(obj, v);
}

/**
 * Create an arc which acts as a loader.
 */
void fp_qp_load_initial_screen(void) {
    /*Create an Arc*/
    lv_obj_t* arc = lv_arc_create(lv_scr_act());
    lv_arc_set_rotation(arc, 270);
    lv_arc_set_bg_angles(arc, 0, 360);
    lv_obj_remove_style(arc, NULL, LV_PART_KNOB);  /*Be sure the knob is not displayed*/
    lv_obj_clear_flag(arc, LV_OBJ_FLAG_CLICKABLE); /*To not allow adjusting by click*/
    lv_obj_center(arc);

    static lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, arc);
    lv_anim_set_exec_cb(&a, fp_qp_set_arc_angle);
    lv_anim_set_time(&a, 1000);
    lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE); /*Just for the demo*/
    lv_anim_set_repeat_delay(&a, 500);
    lv_anim_set_values(&a, 0, 100);
    lv_anim_start(&a);
}
#endif