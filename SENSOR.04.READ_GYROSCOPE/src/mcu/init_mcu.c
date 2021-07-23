#include "stm32f0xx_i2c.h"
#include "stm32f0xx_usart.h"
#include "stm32f0xx_tim.h"
#include "mcu/setup_clock/dronef0_clock.h"
#include "mcu/setup_uart/dronef0_uart.h"
#include "mcu/setup_i2c/dronef0_i2c.h"


/**
 * GPIOA
 * GPIOA 02 => USART1_TX
 * GPIOA 03 => USART1_RX
 */
const USART_TypeDef* COMM_IN_OUT = USART2;
/**
 * GPIOB
 * GPIOB 08 => I2C1_SCL
 * GPIOB 09 => I2C1_SDA
 */
const I2C_TypeDef*   IMU_SENSOR  = I2C1;

/**
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
