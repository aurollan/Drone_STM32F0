#include "stm32f0xx_usart.h"

void    uart_send(uint8_t *data, uint16_t len)
{
    uint16_t index;
    while (index < len)
    {
        USART_SendData(USART1, data[index]);
        index++;
    }
}

