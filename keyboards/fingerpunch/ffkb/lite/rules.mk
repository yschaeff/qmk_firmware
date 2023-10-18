#####
## Important note: If building for the svlinky, you also need to uncomment the lines below that set the MCU to RP2040!!
#####
MCU = atmega32u4
BOOTLOADER = atmel-dfu

ifeq ($(strip $(FP_CONVERT_TO)), svlinky)
   VIK_ENABLE = yes
   OPT_DEFS += -DFP_CONVERT_TO_SVLINKY
   ## Uncomment these two lines for svlinky
   MCU = RP2040
   BOOTLOADER = rp2040
endif

# $(info $(MCU))
# $(info $(BOOTLOADER))

PIN_COMPATIBLE=elite_c

include keyboards/fingerpunch/src/rules.mk