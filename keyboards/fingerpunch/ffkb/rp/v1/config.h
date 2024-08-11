/*
Copyright 2021 Sadek Baroudi <sadekbaroudi@gmail.com>

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

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 1000U

/* key matrix size */
/* Rows are doubled up */
#define MATRIX_ROWS 6
#define MATRIX_COLS 8

// SHIFT REGISTER
// Only needed for matrix_74hc595_spi.c
#define SHIFTREG_MATRIX_COL_CS GP5
#define SHIFTREG_DIVISOR 8 // needs to be the same as the PMW33XX_CS_DIVISOR below
#define MATRIX_ROW_PINS_SR { GP29, GP28, GP12, GP0, GP1, GP4 }

// SPI config for shift register (and trackball if enabled)
#define SPI_DRIVER SPID0
#define SPI_SCK_PIN GP22
#define SPI_MOSI_PIN GP23
#define SPI_MISO_PIN GP20

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

#define ENCODERS_PAD_A {GP24, GP8}
#define ENCODERS_PAD_B {GP6, GP7}
#define ENCODER_RESOLUTION 4

#ifdef FP_EVQ
#define ENCODERS_A_REVERSE
#define ENCODERS_B_REVERSE
#endif

// VIK pin config
#define VIK_SPI_DRIVER    SPID0
#define VIK_SPI_SCK_PIN   GP22
#define VIK_SPI_MOSI_PIN  GP23
#define VIK_SPI_MISO_PIN  GP20
#define VIK_SPI_CS        GP9
#define VIK_I2C_DRIVER    I2CD1
#define VIK_I2C_SDA_PIN   GP2
#define VIK_I2C_SCL_PIN   GP3
#define VIK_GPIO_1        GP27
#define VIK_GPIO_2        GP26
#define VIK_WS2812_DI_PIN GP25

// Used only if you have a display with RESET unconnected, set to unused pin
#define VIK_DISPLAY_RST_UNUSED_PIN GP15
#define FP_QP_ROTATION QP_ROTATION_270

/** add this back into fp_build.json and configure the stuff below
    {
        "type" : "single",
        "name" : "FP_PER_KEY_RGB",
        "user_input": "Do you have per key RGB LEDs?"
    },
    {
        "type" : "single",
        "name" : "FP_INDICATOR_LEDS",
        "user_input": "Do you have the indicator LEDs?"
    },
 */
#ifdef FP_INDICATOR_LEDS
    // TODO: figure out the firmware logic for the indicator leds
    #ifdef FP_PER_KEY_RGB
        // What do I do if there are indicators with per key rgb
    #else
        // What do I do if there are indicators but not per key rgb
    #endif
#endif

#ifdef CIRQUE_ENABLE
  // cirque trackpad config
  #define CIRQUE_PINNACLE_ADDR 0x2A
  #define POINTING_DEVICE_ROTATION_90
  #define CIRQUE_PINNACLE_TAP_ENABLE
  #define POINTING_DEVICE_TASK_THROTTLE_MS 5
  #define I2C1_CLOCK_SPEED  400000
  #define I2C1_DUTY_CYCLE FAST_DUTY_CYCLE_2
#endif

#ifdef FP_TRACKBALL_ENABLE
  // Trackball config
  #define PMW33XX_CS_PIN GP9
  #define PMW33XX_CS_DIVISOR 8 // needs to be the same as the SHIFTREG_DIVISOR above
  #define POINTING_DEVICE_INVERT_Y
#endif

#ifdef AUDIO_ENABLE
    #define AUDIO_VOICES
    #define AUDIO_PIN GP18
    #define AUDIO_PWM_DRIVER PWMD1
    #define AUDIO_PWM_CHANNEL RP2040_PWM_CHANNEL_A
    // #define AUDIO_PWM_PAL_MODE 42 // only if using AUDIO_DRIVER = pwm_hardware
    // #define NO_MUSIC_MODE
    #define AUDIO_ENABLE_TONE_MULTIPLEXING
    #define AUDIO_TONE_MULTIPLEXING_RATE_DEFAULT 10
    #define FP_AUDIO_MOUSE_BUTTONS
    #define FP_AUDIO_CUT_COPY_PASTE
    #define FP_AUDIO_SAVE
    #define FP_STARTUP_LIGHT HALF_NOTE(_E6), HALF_NOTE(_F6), HALF_NOTE(_C6), WHOLE_NOTE(_A5), WHOLE_DOT_NOTE(_F5),
    #define STARTUP_SONG SONG(FP_STARTUP_LIGHT)
    #define DEFAULT_LAYER_SONGS \
        { SONG(QWERTY_SOUND), SONG(COLEMAK_SOUND) }
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

//#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD

#include "keyboards/fingerpunch/src/config_post.h"
