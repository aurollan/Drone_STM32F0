#include "stm32f0xx_tim.h"
#include "stm32f0xx_rcc.h"


#ifndef DRONE_F0_PWM_H
#define DRONE_F0_PWM_H

void pwm_initialize();
void set_duty_cycle(uint16_t TIM_Channel, uint8_t percentage);

#endif /* DRONE_F0_PWM_H */
