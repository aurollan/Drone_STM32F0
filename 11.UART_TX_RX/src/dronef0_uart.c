#include "../inc/dronef0_uart.h"

int USART_initialize()
{
    int ret;
    GPIO_InitTypeDef GPIOA_init;

    ret = 0;
    memset(&GPIOA_init, 0, sizeof(GPIO_InitTypeDef));

    /* 
     * Enabling clocks
     *
     * GPIOA on AHBENR
     * USART1 on APB2ENR
     */
    RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOAEN, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2ENR_USART1EN, ENABLE);

    /*
     * AF = 1
     * GPIOA0 = USART1_CTS
     * GPIOA1 = USART1_RTS
     * GPIOA2 = USART1_TX
     * GPIOA3 = USART1_RX
     * GPIOA4 = USART1_CK
     */

    GPIOA_init.GPIO_Mode = GPIO_Mode_AF;
    GPIOA_init.GPIO_OType = GPIO_OType_PP;
    GPIOA_init.GPIO_Speed = GPIO_Speed_Level_3;
    GPIOA_init.GPIO_PuPd = GPIO_PuPd_UP;
    GPIOA_init.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;

    /* Init GPIOA fo UART */
    GPIO_Init(GPIOA, &GPIOA_init);

    /* Init UART */
    /* We want Interruption and maybe DMA */
    return (ret);
}
