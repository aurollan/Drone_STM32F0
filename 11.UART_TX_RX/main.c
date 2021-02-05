#include <stdint.h>
#include "inc/dronef0_uart.h"

void assert_failed(uint8_t* file, uint32_t line) {
    (void)file;
    (void)line;
}

int main(void) {
    communication_initialize();
    while (1)
    {
        //while (USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == SET);
        //character = USART_ReceiveData(USART2);
        while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
        USART_SendData(USART2, 'c');
    }
    return (0);
}
