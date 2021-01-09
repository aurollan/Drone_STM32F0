#include "../inc/dronef0_uart.h"

int USART_initialize()
{
    int ret;
    GPIO_InitTypeDef GPIOA_init;

    ret = 0;
    /* Enabling GPIOA clock */
    RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOAEN, ENABLE);


    /*
     * AF = 1
     * GPIOA0 = USART1_CTS
     * GPIOA1 = USART1_RTS
     * GPIOA2 = USART1_TX
     * GPIOA3 = USART1_RX
     * GPIOA4 = USART1_CK
     */

    /* Init UART */
    /* We want Interruption and maybe DMA */
    GPIO_Init(GPIOA, &GPIOA_init);

    return (ret);
}
