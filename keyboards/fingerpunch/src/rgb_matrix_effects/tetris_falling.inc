#ifdef RGB_MATRIX_FRAMEBUFFER_EFFECTS
// Step 1.
// Declare custom effects using the RGB_MATRIX_EFFECT macro
// (note the lack of semicolon after the macro!)
RGB_MATRIX_EFFECT(tetris_falling)

// Step 2.
// Define effects inside the `RGB_MATRIX_CUSTOM_EFFECT_IMPLS` ifdef block
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "eeprom.h"
#include "eeconfig.h"

// https://qph.cf2.quoracdn.net/main-qimg-356e2b21c801381db2890dab49a9ea88
#define I_BLOCK 0
#define J_BLOCK 1
#define L_block 2
#define O_block 3
#define S_block 4
#define T_block 5
#define Z_block 6

#define I_BLOCK_HUE 127 // cyan
#define J_BLOCK_HUE 169 // blue
#define L_BLOCK_HUE 21  // orange
#define O_BLOCK_HUE 43  // yellow
#define S_BLOCK_HUE 85  // green
#define T_BLOCK_HUE 180 // purple
#define Z_BLOCK_HUE 0   // red

uint8_t get_tetromino_color(uint8_t tetromino_number) {
    const uint8_t tetromino_colors[7] = {
        I_BLOCK_HUE,
        J_BLOCK_HUE,
        L_BLOCK_HUE,
        O_BLOCK_HUE,
        S_BLOCK_HUE,
        T_BLOCK_HUE,
        Z_BLOCK_HUE
    };

    if (tetromino_number < 0 || tetromino_number > 6) {
        return 0;
    }

    return tetromino_colors[tetromino_number];
}

bool[4][4] get_tetromino_matrix(uint8_t tetromino_number) {
    switch (tetromino_number):
        case I_BLOCK:
            return {{{false}, {false}, {false}, {false}},
                    {{false}, {false}, {false}, {false}},
                    {{false}, {false}, {false}, {false}},
                    {{true},  {true},  {true},  {true} }};
            break;
        case J_BLOCK:
            return {{{false}, {false}, {false}, {false}},
                    {{false}, {false}, {false}, {false}},
                    {{true},  {false}, {false}, {false}},
                    {{true},  {true},  {true},  {false}}};
            break;
        case L_BLOCK:
            return {{{false}, {false}, {false}, {false}},
                    {{false}, {false}, {false}, {false}},
                    {{true},  {true},  {true},  {false}},
                    {{true},  {false}, {false}, {false}}};
            break;
        case O_BLOCK:
            return {{{false}, {false}, {false}, {false}},
                    {{false}, {false}, {false}, {false}},
                    {{true},  {true},  {false}, {false}},
                    {{true},  {true},  {false}, {false}}};
            break;
        case S_BLOCK:
            return {{{false}, {false}, {false}, {false}},
                    {{false}, {false}, {false}, {false}},
                    {{false}, {true},  {true},  {false}},
                    {{true},  {true},  {false}, {false}}};
            break;
        case T_BLOCK:
            return {{{false}, {false}, {false}, {false}},
                    {{false}, {false}, {false}, {false}},
                    {{false}, {true},  {false}, {false}},
                    {{true},  {true},  {true},  {false}}};
            break;
        case Z_BLOCK:
            return {{{false}, {false}, {false}, {false}},
                    {{false}, {false}, {false}, {false}},
                    {{true},  {true},  {false}, {false}},
                    {{false}, {true},  {true},  {false}}};
            break;
        default:
            break;
    
    return {{{false}, {false}, {false}, {false}},
            {{false}, {false}, {false}, {false}},
            {{false}, {false}, {false}, {false}},
            {{false}, {false}, {false}, {false}}};

}

static bool tetris_falling(effect_params_t* params) {

    // Initialize variables that are used across runs
    static bool tetris_restart = true;
    static uint8_t drop_active  = 0;
    static uint8_t active_tetromino = 0;
    static uint8_t active_tetromino_col = 0;
    static uint8_t active_tetromino_row = 0;

    // Either this is the first time we run, or the last loop resulted in a collision, so we restarted
    if (tetris_restart) {
        rgb_matrix_set_color_all(0, 0, 0);
        memset(g_rgb_frame_buffer, 0, sizeof(g_rgb_frame_buffer));
        drop_active = 0;
    }

    // The previous turn resulted in a settled tetromino, so need a new piece to drop. Randomly select piece and column to drop in
    // (Note: todo) There is logic to make sure that it doesn't select a piece / column that results in the tetromino being "off screen"
    if (drop_active == 0) {
        drop_active = 1;
        active_tetromino = rand() % 7;
        active_tetromino_col = rand() % MATRIX_COLS;
        active_tetromino_row = 0;
        tetris_restart = false;
    }

    // for (uint8_t col = 0; col < MATRIX_COLS; col++) {
    //     for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
    //         if (row == 0 && drop == 0 && rand() < RAND_MAX / RGB_DIGITAL_RAIN_DROPS) {
    //             // top row, pixels have just fallen and we're
    //             // making a new rain drop in this column
    //             g_rgb_frame_buffer[row][col] = max_intensity;
    //         } else if (g_rgb_frame_buffer[row][col] > 0 && g_rgb_frame_buffer[row][col] < max_intensity) {
    //             // neither fully bright nor dark, decay it
    //             if (decay == decay_ticks) {
    //                 g_rgb_frame_buffer[row][col]--;
    //             }
    //         }
    //         // set the pixel colour
    //         uint8_t led[LED_HITS_TO_REMEMBER];
    //         uint8_t led_count = rgb_matrix_map_row_column_to_led(row, col, led);

    //         // TODO: multiple leds are supported mapped to the same row/column
    //         if (led_count > 0) {
    //             if (g_rgb_frame_buffer[row][col] > pure_green_intensity) {
    //                 const uint8_t boost = (uint8_t)((uint16_t)max_brightness_boost * (g_rgb_frame_buffer[row][col] - pure_green_intensity) / (max_intensity - pure_green_intensity));
    //                 rgb_matrix_set_color(led[0], boost, max_intensity, boost);
    //             } else {
    //                 const uint8_t green = (uint8_t)((uint16_t)max_intensity * g_rgb_frame_buffer[row][col] / pure_green_intensity);
    //                 rgb_matrix_set_color(led[0], 0, green, 0);
    //             }
    //         }
    //     }
    // }
    // if (decay == decay_ticks) {
    //     decay = 0;
    // }

    // if (++drop > drop_ticks) {
    //     // reset drop timer
    //     drop = 0;
    //     for (uint8_t row = MATRIX_ROWS - 1; row > 0; row--) {
    //         for (uint8_t col = 0; col < MATRIX_COLS; col++) {
    //             // if ths is on the bottom row and bright allow decay
    //             if (row == MATRIX_ROWS - 1 && g_rgb_frame_buffer[row][col] == max_intensity) {
    //                 g_rgb_frame_buffer[row][col]--;
    //             }
    //             // check if the pixel above is bright
    //             if (g_rgb_frame_buffer[row - 1][col] >= max_intensity) { // Note: can be larger than max_intensity if val was recently decreased
    //                 // allow old bright pixel to decay
    //                 g_rgb_frame_buffer[row - 1][col] = max_intensity - 1;
    //                 // make this pixel bright
    //                 g_rgb_frame_buffer[row][col] = max_intensity;
    //             }
    //         }
    //     }
    // }
    // return false;
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif // RGB_MATRIX_FRAMEBUFFER_EFFECTS