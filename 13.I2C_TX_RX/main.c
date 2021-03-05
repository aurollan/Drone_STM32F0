#include <stdint.h>
#include "inc/dronef0_uart.h"
#include "inc/dronef0_clock.h"
#include "inc/dronef0_i2c.h"

void assert_failed(uint8_t* file, uint32_t line) {
    (void)file;
    (void)line;
}

int main(void) {
    FlagStatus          flag_status;

    /* Evetything went as expected we can setup our peripherals */
    clock_initialize();
    I2C_IT_T = 0;
    communication_initialize();
    i2c_initialize();
    while (1)
    {
        //while (USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == SET);
        //character = USART_ReceiveData(USART2);
        while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
        USART_SendData(USART1, 'c');

        flag_status = USART_GetFlagStatus(USART1, USART_FLAG_ORE);
        flag_status = USART_GetFlagStatus(USART1, USART_FLAG_NE);
        flag_status = USART_GetFlagStatus(USART1, USART_FLAG_FE);
        flag_status = USART_GetFlagStatus(USART1, USART_FLAG_PE);

        while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
        USART_SendData(USART2, 'c');

        flag_status = USART_GetFlagStatus(USART2, USART_FLAG_ORE);
        flag_status = USART_GetFlagStatus(USART2, USART_FLAG_NE);
        flag_status = USART_GetFlagStatus(USART2, USART_FLAG_FE);
        flag_status = USART_GetFlagStatus(USART2, USART_FLAG_PE);
    }
    return (0);
}
