#####
## Important note: If building for the svlinky, you also need to uncomment the lines below that set the MCU to RP2040!!
#####
MCU = atmega32u4
BOOTLOADER = atmel-dfu

ifeq ($(strip $(FP_CONVERT_TO)), svlinky)
   VIK_ENABLE = yes
   OPT_DEFS += -DFP_CONVERT_TO_SVLINKY
   ## Uncomment these two lines for svlinky
   # MCU = RP2040
   # BOOTLOADER = rp2040
endif

# $(info $(MCU))
# $(info $(BOOTLOADER))

PIN_COMPATIBLE=elite_c

DEFERRED_EXEC_ENABLE = yes
SRC +=  keyboards/fingerpunch/src/fp.c \
        keyboards/fingerpunch/src/fp_haptic.c \
        keyboards/fingerpunch/src/fp_audio.c \
        keyboards/fingerpunch/src/fp_keyhandler.c \
        keyboards/fingerpunch/src/fp_encoder.c \
        keyboards/fingerpunch/src/fp_pointing.c \
        keyboards/fingerpunch/src/fp_rgb_common.c \
        keyboards/fingerpunch/src/fp_rgblight.c \
        keyboards/fingerpunch/src/fp_rgb_matrix.c

include keyboards/fingerpunch/src/rules.mk