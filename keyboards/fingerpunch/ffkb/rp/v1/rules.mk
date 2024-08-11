CIRQUE_ENABLE = yes
FP_TRACKBALL_ENABLE = no
RGB_MATRIX_ENABLE = yes
FP_EVQ = yes
AUDIO_ENABLE = yes
HAPTIC_ENABLE = no

CAPS_WORD_ENABLE = yes
KEY_OVERRIDE_ENABLE = yes




AUDIO_ENABLE ?= no
AUDIO_DRIVER = pwm_hardware

HAPTIC_ENABLE ?= no
HAPTIC_DRIVER = drv2605l

VIK_ENABLE = yes

ifeq ($(strip $(FP_INDICATOR_LEDS)), yes)
   OPT_DEFS += -DFP_INDICATOR_LEDS
endif

ifeq ($(strip $(FP_PER_KEY_RGB)), yes)
   OPT_DEFS += -DFP_PER_KEY_RGB
endif

ifeq ($(strip $(FP_TRACKBALL_ENABLE)), yes)
   MOUSEKEY_ENABLE := yes  # not required, but enabling for mouse button keys
   POINTING_DEVICE_ENABLE := yes
   POINTING_DEVICE_DRIVER := pmw3360
   QUANTUM_LIB_SRC += spi_master.c
   OPT_DEFS += -DFP_TRACKBALL_ENABLE
endif

ifeq ($(strip $(FP_EC11)), yes)
   ENCODER_ENABLE := yes
   OPT_DEFS += -DFP_EC11_UNDER_PALMS
endif

ifeq ($(strip $(FP_EVQ)), yes)
   ENCODER_ENABLE := yes
   OPT_DEFS += -DFP_EVQ_UNDER_PALMS
endif

ifeq ($(strip $(CIRQUE_ENABLE)), yes)
   MOUSEKEY_ENABLE := yes  # not required, but enabling for mouse button keys
   POINTING_DEVICE_ENABLE := yes
   POINTING_DEVICE_DRIVER := cirque_pinnacle_i2c
   #POINTING_DEVICE_DRIVER := cirque_pinnacle_spi
   OPT_DEFS += -DCIRQUE_ENABLE
endif

include keyboards/fingerpunch/src/rules.mk
