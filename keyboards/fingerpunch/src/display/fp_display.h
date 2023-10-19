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

#pragma once
#include QMK_KEYBOARD_H
#include "keyboards/fingerpunch/src/fp.h"

// Choose one of QP_ROTATION_0, QP_ROTATION_90, QP_ROTATION_180, QP_ROTATION_270
#ifndef FP_QP_ROTATION
    #define FP_QP_ROTATION QP_ROTATION_0
#endif

void fp_post_init_qp(void);
void fp_qp_init_display(void);
void fp_qp_load_initial_screen(void);
