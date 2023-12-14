// bin/fp_build.sh -k ffkb/lite/v1 -m sadekbaroudi -i -r -e "FP_CONVERT_TO=svlinky VIK_PMW3360=yes"
#ifdef VIK_TRACKBALL_ENABLE
#define POINTING_DEVICE_INVERT_Y
#endif

// bin/fp_build.sh -k ffkb/lite/v1 -m sadekbaroudi -i -r -e "FP_CONVERT_TO=svlinky VIK_PER56_CIRQUE_LEDS=yes"
#ifdef VIK_PER56_CIRQUE_LEDS
#define CIRQUE_PINNACLE_DIAMETER_MM 35
#define CIRQUE_PINNACLE_ATTENUATION 2X
#define CIRQUE_PINNACLE_TAP_ENABLE
#define POINTING_DEVICE_ROTATION_90
#endif