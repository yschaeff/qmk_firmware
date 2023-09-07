/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "keyboards/fingerpunch/src/config.h"

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

// Got help from https://www.eisbahn.jp/yoichiro/2022/08/luankey_pico_qmk_firmware.html
#define SPLIT_TRANSPORT_MIRROR
#define SPLIT_POINTING_ENABLE
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_MODS_ENABLE
#define SPLIT_HAPTIC_ENABLE

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

#ifdef RGBLIGHT_ENABLE
    #define RGBLIGHT_SPLIT
    #ifdef FP_VIK_PERS60_MODULE
    #define RGBLED_SPLIT { 10, 6 }
    #define RGBLED_NUM 16
    #define RGBLIGHT_LED_MAP { 5, 4, 3, 2, 1, 0, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 }
    #else
    #define RGBLED_SPLIT { 6, 6 }
    #define RGBLED_NUM 12
    #define RGBLIGHT_LED_MAP { 5, 4, 3, 2, 1, 0, 6, 7, 8, 9, 10, 11 }
    #endif
    #define RGBLIGHT_HUE_STEP 16
    #define RGBLIGHT_SAT_STEP 16
    #define RGBLIGHT_VAL_STEP 16
    #define RGBLIGHT_LIMIT_VAL 255 /* The maximum brightness level for RGBLIGHT_ENABLE */
    #define RGBLIGHT_SLEEP  /* If defined, the RGB lighting will be switched off when the host goes to sleep */
    #define RGBLIGHT_EFFECT_ALTERNATING
    #define RGBLIGHT_EFFECT_BREATHING
    #define RGBLIGHT_EFFECT_CHRISTMAS
    #define RGBLIGHT_EFFECT_KNIGHT
    #define RGBLIGHT_EFFECT_RAINBOW_MOOD
    #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
    #define RGBLIGHT_EFFECT_SNAKE
    #define RGBLIGHT_EFFECT_STATIC_GRADIENT
    #define RGBLIGHT_EFFECT_TWINKLE
#endif

#ifdef HAPTIC_ENABLE
    #define FB_ERM_LRA 1
    #define FB_BRAKEFACTOR 3 // For 1x:0, 2x:1, 3x:2, 4x:3, 6x:4, 8x:5, 16x:6, Disable Braking:7
    #define FB_LOOPGAIN 1 // For  Low:0, Medium:1, High:2, Very High:3
    #define RATED_VOLTAGE 2
    #define V_PEAK 2.8
    #define V_RMS 2.0
    #define F_LRA 150 // resonance freq
    #define DRV_GREETING  alert_750ms
    #define FP_HAPTIC_MOUSE_BUTTONS
    #define FP_HAPTIC_CUT_COPY_PASTE
    #define FP_HAPTIC_SAVE
#endif

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
