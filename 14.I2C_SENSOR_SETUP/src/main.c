#include <stdint.h>
#include "sensor/setup_gy-521.h"
#include "mcu/setup_usart/dronef0_uart.h"
#include "mcu/setup_clock/dronef0_clock.h"
#include "mcu/setup_i2c/dronef0_i2c.h"

void assert_failed(uint8_t* file, uint32_t line) {
    (void)file;
    (void)line;
}

int main(void) {
    /* Evetything went as expected we can setup our peripherals */
    clock_initialize();
    communication_initialize();
    i2c_initialize();
    while (1)
    {
        uint8_t who_am_i;
        uint32_t i2c_isr_err_occured;
        i2c_isr_err_occured = get_gy_521_who_am_i(&who_am_i);

        if (i2c_isr_err_occured)
        {
                if (i2c_isr_err_occured & I2C_FLAG_BERR)
                {
                    uart_send_data(USART1, (uint8_t*)"ERR_BERR\n", 9);
                }
                if (i2c_isr_err_occured & I2C_FLAG_BUSY)
                {
                    uart_send_data(USART1, (uint8_t*)"ERR_BUSY\n", 9);
                }
                if (i2c_isr_err_occured & I2C_FLAG_ARLO)
                {
                    uart_send_data(USART1, (uint8_t*)"ERR_ARLO\n", 9);
                }
                if (i2c_isr_err_occured & I2C_FLAG_OVR)
                {
                    uart_send_data(USART1, (uint8_t*)"ERR_OVR\n", 8);
                }
                if (i2c_isr_err_occured & I2C_FLAG_TIMEOUT)
                {
                    uart_send_data(USART1, (uint8_t*)"ERR_TOUT\n", 9);
                }
        }
        else
        {
            while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
            USART_SendData(USART1, who_am_i);

            while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
            USART_SendData(USART2, who_am_i);
        }
    }
    return (0);
}
