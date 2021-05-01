#include "mcu/pwm/sensor_interface/write_pwm.h"
#include "stm32f0xx_tim.h"

/**
 * @brief   Set speed as persent of available power.
 *          Regarding our available range to handle speed (from 1 to 2 ms)
 *          we translate speed in micro second duty cycle.
 * @param   percentage uint8_t. Speed in percent of power
 * @return  Nothing
 */
void set_duty_cycle(uint16_t TIM_Channel, uint16_t us)
{
    switch (TIM_Channel)
    {
        case TIM_Channel_1:
            TIM_SetCompare1(TIM3, us);
            break;
        case TIM_Channel_2:
            TIM_SetCompare2(TIM3, us);
            break;
        case TIM_Channel_3:
            TIM_SetCompare3(TIM3, us);
            break;
        case TIM_Channel_4:
            TIM_SetCompare4(TIM3, us);
            break;
        default:
            break;
    }
}
