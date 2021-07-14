#include "stm32f0xx_tim.h"
#include "stm32f0xx_rcc.h"

uint16_t get_counter_ms()
{
    return (TIM6->CNT);
}

void timer_initialize()
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    TIM_DeInit(TIM6);
    TIM_TimeBaseStructInit(&TIM_TimeBaseInitStruct);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);

    /* 8 Mhz clock and we want to count us */
    TIM_TimeBaseInitStruct.TIM_ClockDivision     = TIM_CKD_DIV1;
    TIM_TimeBaseInitStruct.TIM_CounterMode       = TIM_CounterMode_Up;
    TIM_TimeBaseInitStruct.TIM_Period            = UINT16_MAX;
    /* 8 000 000  / (7 999 + 1) = 1 000 */
    TIM_TimeBaseInitStruct.TIM_Prescaler         = 7999;

    TIM_TimeBaseInit(TIM6, &TIM_TimeBaseInitStruct);

    TIM_Cmd(TIM6, ENABLE);
}
