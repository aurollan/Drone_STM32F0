#include "stm32f0xx_i2c.h"
#include "stm32f0xx_usart.h"
#include "stm32f0xx_tim.h"
#include "mcu/clock/setup/dronef0_clock.h"
#include "mcu/uart/setup/dronef0_uart.h"
#include "mcu/i2c/setup/dronef0_i2c.h"


/**
 * Communication bus used
 *
 * GPIOB
 * GPIOB 06 => USART1_TX
 * GPIOB 07 => USART1_RX
 *
 * GPIOB
 * GPIOB 08 => I2C1_SCL
 * GPIOB 09 => I2C1_SDA
 *
 * GPIOB
 * GPIOB 04 => TIM3_CH1
 * GPIOB 05 => TIM3_CH2
 * GPIOB 00 => TIM3_CH3
 * GPIOB 01 => TIM3_CH4
 */
const TIM_TypeDef*   MOTORS      = TIM3;


void    init_mcu(void)
{
    clock_initialize();
    uart_initialize();
    i2c_initialize();
    return ;
}
