# See https://github.com/sadekbaroudi/vik

# rules.mk options
# VIK_ENABLE
# VIK_HAPTIC
# VIK_PER56_CIRQUE_LEDS
# VIK_PER56_CIRQUE_LEDS
# VIK_PER56_PMW3360_LEDS
# VIK_PMW3360
# VIK_WEACT_ST7735
# VIK_VIK_GC9A01

ifeq ($(strip $(VIK_HAPTIC)), yes)
   HAPTIC_ENABLE = yes
   OPT_DEFS += -DVIK_HAPTIC
endif

ifeq ($(strip $(VIK_PER56_CIRQUE_LEDS)), yes)
   CIRQUE_ENABLE = yes
   ENCODER_ENABLE = yes
#    RGBLIGHT_ENABLE = yes # you need to choose whether or not this is enabled within the keyboard or user rules.mk
   OPT_DEFS += -DVIK_PER56_CIRQUE_LEDS
endif

ifeq ($(strip $(VIK_PER56_PMW3360_LEDS)), yes)
   PMW3360_ENABLE = yes
   ENCODER_ENABLE = yes
#    RGBLIGHT_ENABLE = yes # you need to choose whether or not this is enabled within the keyboard or user rules.mk
   OPT_DEFS += -DVIK_PER56_PMW3360_LEDS
endif

ifeq ($(strip $(VIK_PMW3360)), yes)
   PMW3360_ENABLE = yes
   OPT_DEFS += -DVIK_PMW3360
endif

ifeq ($(strip $(VIK_WEACT_ST7735)), yes)
   # For LCD backlight toggling
   BACKLIGHT_ENABLE = yes
   BACKLIGHT_DRIVER = software

   QUANTUM_PAINTER_ENABLE = yes
   QUANTUM_PAINTER_DRIVERS += st7735_spi
   QUANTUM_PAINTER_LVGL_INTEGRATION = yes
#    SRC += fonts/urbanist24.qff.c fonts/urbanist36.qff.c 
#    SRC += fonts/roboto12.qff.c fonts/roboto18.qff.c fonts/roboto14.qff.c
#    SRC += display.c
#    WPM_ENABLE 					= yes
   OPT_DEFS += -DVIK_WEACT_ST7735
endif

ifeq ($(strip $(VIK_VIK_GC9A01)), yes)
   QUANTUM_PAINTER_ENABLE = yes
   QUANTUM_PAINTER_DRIVERS += st7735_spi
   QUANTUM_PAINTER_LVGL_INTEGRATION = yes
#    SRC += fonts/urbanist24.qff.c fonts/urbanist36.qff.c 
#    SRC += fonts/roboto12.qff.c fonts/roboto18.qff.c fonts/roboto14.qff.c
#    SRC += display.c
#    WPM_ENABLE 					= yes
   OPT_DEFS += -DVIK_VIK_GC9A01
endif

ifeq ($(strip $(PMW3360_ENABLE)), yes)
   POINTING_DEVICE_ENABLE := yes
   POINTING_DEVICE_DRIVER := pmw3360
   QUANTUM_LIB_SRC += spi_master.c
   OPT_DEFS += -DVIK_TRACKBALL_ENABLE
endif
