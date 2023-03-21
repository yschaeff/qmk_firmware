#include_next <mcuconf.h>

#undef STM32_PWM_USE_TIM1
#define STM32_PWM_USE_TIM1                  TRUE

#undef STM32_PWM_USE_TIM2
#define STM32_PWM_USE_TIM2                  TRUE

#undef STM32_ST_USE_TIMER
#define STM32_ST_USE_TIMER 5

#undef STM32_GPT_USE_TIM3
#define STM32_GPT_USE_TIM3                  TRUE