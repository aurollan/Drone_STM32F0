#include <stdint.h>
#include "mcu/init_mcu.h"
#include "mcu/setup_dma/dronef0_dma_receive.h"
#include "stm32f0xx_usart.h"

void assert_failed(uint8_t* file, uint32_t line)
{
    (void)file;
    (void)line;
}

int main(void) 
{
    init_mcu();
    while (1) 
    {
        while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) != SET);
        USART_SendData(USART1, command);
        while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) != SET);
        USART_SendData(USART1, '\n');
    }
    return (0);
}
