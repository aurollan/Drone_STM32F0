#include <stdint.h>
#include <string.h>
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
        uint32_t i2c_isr_err_occured;
        i2c_isr_err_occured = set_gy_521_pwr(0x00);
    while (1)
    {
        //uint8_t who_am_i;
        uint8_t pwr;
        //i2c_isr_err_occured = get_gy_521_who_am_i(&who_am_i);
        i2c_isr_err_occured = get_gy_521_pwr(&pwr);

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
                if (i2c_isr_err_occured & I2C_FLAG_NACKF)
                {
                    uart_send_data(USART1, (uint8_t*)"ERR_NACK\n", 9);
                    // Clearing NACK flag for the next communication
                    I2C1->ISR &= ~I2C_FLAG_NACKF;
                }
        }
    }
    return (0);
}
