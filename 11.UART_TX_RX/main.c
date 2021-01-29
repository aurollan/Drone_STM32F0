#include <stdint.h>
#include "inc/dronef0_uart.h"

void assert_failed(uint8_t* file, uint32_t line) {
    (void)file;
    (void)line;
}

int main(void) {
    uint16_t character;

    communication_initialize();
    while (1)
    {
        character = USART_ReceiveData(USART1);
        USART_SendData(USART1, character);
    }
    return (0);
}
