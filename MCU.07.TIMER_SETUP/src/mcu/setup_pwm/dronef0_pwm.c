#include "dronef0_pwm.h"

const uint16_t max_duty_cycle = 2000;

const uint32_t second_in_ms = 1000;
uint16_t clock_frequency_to_ms(void)
{
    uint16_t prescaler;
    RCC_ClocksTypeDef   clocks;

    prescaler = 0;
    RCC_GetClocksFreq(&clocks);
    
    
   if (clocks.SYSCLK_Frequency > second_in_ms)
   {
       prescaler = (clocks.SYSCLK_Frequency / second_in_ms);
   }
   return (prescaler);

}

const uint32_t second_in_us = 1000000;
uint16_t clock_frequency_to_us(void)
{
    uint16_t            prescaler;
    RCC_ClocksTypeDef   clocks;

    prescaler = 0;
    RCC_GetClocksFreq(&clocks);
    
    
   if (clocks.SYSCLK_Frequency > second_in_us)
   {
       /**
        * UINT32_MAX / 1 000 000 = 4 294
        * We are sur it fit in an uint16
       */
       prescaler = (clocks.SYSCLK_Frequency / second_in_us);
   }
   return (prescaler);
}

void pwm_gpio_initialize(void)
{


    /** 
     * Init struct with default setup
     */
    GPIO_InitTypeDef GPIOB_init;

    /** 
     * Enabling clock
     * GPIOB on AHBENR
     */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

    /**
     * PA6 => TIM3_CH1
     * PA7 => TIM3_CH2
     * PB0 => TIM3_CH3
     * PB1 => TIM3_CH4
     *
     * PB4 => TIM3_CH1
     * PB5 => TIM3_CH2
     *
     */
    GPIOB_init.GPIO_Mode  = GPIO_Mode_AF;
    GPIOB_init.GPIO_OType = GPIO_OType_PP;
    GPIOB_init.GPIO_Speed = GPIO_Speed_Level_2;
    GPIOB_init.GPIO_PuPd  = GPIO_PuPd_NOPULL;
    GPIOB_init.GPIO_Pin   = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5;

    /**
     * Init GPIOB for PWM
     */
    GPIO_Init(GPIOB, &GPIOB_init);
    /**
     * Alternate Function = 1
     * Note That we don't use the same Pin Macro
     * And both pin use the same AF.
     */
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource0,  GPIO_AF_1);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource1,  GPIO_AF_1);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource4, GPIO_AF_1);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource5, GPIO_AF_1);

}

void pwm_initialize(void)
{
    /* Setting up GPIO used for PWM */
    pwm_gpio_initialize();
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    /**
     * TIM3 with four channels for our 4 motors
     */
    TIM_OCInitTypeDef timer_oc;
    TIM_TimeBaseInitTypeDef timer_base;

    TIM_DeInit(TIM3);
    TIM_TimeBaseStructInit(&timer_base);

    timer_base.TIM_ClockDivision = TIM_CKD_DIV1;
    timer_base.TIM_CounterMode = TIM_CounterMode_Up;
    timer_base.TIM_Period = 20000; /* 20000 us for 20 ms */
    timer_base.TIM_Prescaler = clock_frequency_to_us() - 1;
    timer_base.TIM_RepetitionCounter = 0x0000;
    TIM_TimeBaseInit(TIM3, &timer_base);

    TIM_OCStructInit(&timer_oc);

    timer_oc.TIM_OCIdleState  = TIM_OCIdleState_Reset;
    timer_oc.TIM_OCMode       = TIM_OCMode_PWM1;
    timer_oc.TIM_OCPolarity   = TIM_OCPolarity_High;
    timer_oc.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
    timer_oc.TIM_OutputState  = TIM_OutputState_Enable;
    timer_oc.TIM_OutputNState = TIM_OutputNState_Disable;
    timer_oc.TIM_Pulse        = 0x0000;


    TIM_ARRPreloadConfig(TIM3, ENABLE);
    TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
    TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
    TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
    TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);

    TIM_OC1Init(TIM3, &timer_oc);
    TIM_OC2Init(TIM3, &timer_oc);
    TIM_OC3Init(TIM3, &timer_oc);
    TIM_OC4Init(TIM3, &timer_oc);

    TIM_CCxCmd(TIM3, TIM_Channel_1, TIM_CCx_Enable);
    TIM_CCxCmd(TIM3, TIM_Channel_2, TIM_CCx_Enable);
    TIM_CCxCmd(TIM3, TIM_Channel_3, TIM_CCx_Enable);
    TIM_CCxCmd(TIM3, TIM_Channel_4, TIM_CCx_Enable);

    /* FlagStatus TIM_GetFlagStatus(TIM3, uint16_t TIM_FLAG); */
    /* void TIM_ClearFlag(TIM3, uint16_t TIM_FLAG); */
    /* void TIM_InternalClockConfig(TIM_TypeDef* TIMx); */

    TIM_Cmd(TIM3, ENABLE);
}

/**
 * @brief   Set speed as persent of available power.
 *          Regarding our available range to handle speed (from 1 to 2 ms)
 *          we translate speed in micro second duty cycle.
 * @param   percentage uint8_t. Speed in percent of power
 * @return  Nothing
 */
void set_duty_cycle(uint16_t TIM_Channel, uint8_t percentage)
{
    uint32_t percentage_in_us;

    percentage_in_us = 0;
    if (percentage > 100)
    {
        /**
         * Prevent max_duty_cycle overflow
         */
        percentage = 100;
    }
    percentage_in_us =  max_duty_cycle / 100;
    percentage_in_us *= percentage;

    switch (TIM_Channel)
    {
        case TIM_Channel_1:
            TIM_SetCompare1(TIM3, percentage_in_us);
            break;
        case TIM_Channel_2:
            TIM_SetCompare2(TIM3, percentage_in_us);
            break;
        case TIM_Channel_3:
            TIM_SetCompare3(TIM3, percentage_in_us);
            break;
        case TIM_Channel_4:
            TIM_SetCompare4(TIM3, percentage_in_us);
            break;
        default:
            break;
    }
}
