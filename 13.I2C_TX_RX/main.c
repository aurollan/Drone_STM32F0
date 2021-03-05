#include <stdint.h>
#include "inc/dronef0_uart.h"
#include "inc/dronef0_clock.h"
#include "inc/dronef0_i2c.h"

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
        //while (USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == SET);
        //character = USART_ReceiveData(USART2);
        while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
        USART_SendData(USART1, 'c');


        while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
        USART_SendData(USART2, 'c');

    }
    return (0);
}
