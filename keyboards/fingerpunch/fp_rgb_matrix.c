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

#include "keyboards/fingerpunch/fp_rgb_matrix.h"

#ifdef RGB_MATRIX_ENABLE
layer_state_t fp_layer_state_set_rgb_matrix(layer_state_t state) {
    switch (get_highest_layer(state)) {
        default:
            break;
    }
    return state;
}

bool fp_process_record_rgb_matrix(uint16_t keycode, keyrecord_t *record) {
#   ifndef FP_DISABLE_CUSTOM_KEYCODES
    switch (keycode) {
        default:
            break;
    }
#   endif // FP_DISABLE_CUSTOM_KEYCODES

    return true;
}
#endif
