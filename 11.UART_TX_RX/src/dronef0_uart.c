#include "../inc/dronef0_uart.h"


static void GPIOA_initialize()
{
    GPIO_InitTypeDef GPIOA_init;

    GPIO_StructInit(&GPIOA_init);

    /* 
     * Enabling clock
     * GPIOA on AHBENR
     */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

    /*
     * GPIOA0 AF = USART1_CTS => unused (for rs-232)
     * GPIOA1 AF = USART1_RTS => unused (for rs-232)
     * GPIOA2 AF = USART1_TX  => used
     * GPIOA3 AF = USART1_RX  => used
     * GPIOA4 AF = USART1_CK  => unused (no synchronous UART)
     */

    GPIOA_init.GPIO_Mode  = GPIO_Mode_AF;
    GPIOA_init.GPIO_OType = GPIO_OType_PP;
    GPIOA_init.GPIO_Speed = GPIO_Speed_Level_3;
    GPIOA_init.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIOA_init.GPIO_Pin   = GPIO_Pin_9 | GPIO_Pin_10;

    /* Init GPIOA fo UART */
    GPIO_Init(GPIOA, &GPIOA_init);

    /*
     * Alternate Function = 1
     * Note That we don't use the same Pin Macro
     */
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_1);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_1);
}


void USART1_initialize()
{
    USART_InitTypeDef UART1_init;

    USART_StructInit(&UART1_init);

    /* 
     * Enabling clock
     * USART1 on APB2ENR
     */
    //RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);


    /* Init UART */
    UART1_init.USART_BaudRate = 9600; //default from structInit func is 9600
    UART1_init.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    UART1_init.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    UART1_init.USART_Parity = USART_Parity_No;
    UART1_init.USART_StopBits = USART_StopBits_1;
    UART1_init.USART_WordLength = USART_WordLength_8b;

    /* We want Interruption and maybe DMA */
    USART_Init(USART1, &UART1_init);
    USART_Cmd(USART1, ENABLE);
}

void communication_initialize() 
{
    /* Setting up GPIO */
    GPIOA_initialize();
    /* Setting up USART1 */
    USART1_initialize();
}
