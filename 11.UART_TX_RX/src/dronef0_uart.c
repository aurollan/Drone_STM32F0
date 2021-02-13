#include "../inc/dronef0_uart.h"

static void GPIOB_initialize()
{
    GPIO_InitTypeDef GPIOB_init;

    GPIO_StructInit(&GPIOB_init);

    /* 
     * Enabling clock
     * GPIOB on AHBENR
     */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

    /*
     * GPIOB6 AF = USART1_TX  => used
     * GPIOB7 AF = USART1_RX  => used
     */

    GPIOB_init.GPIO_Mode  = GPIO_Mode_AF;
    GPIOB_init.GPIO_OType = GPIO_OType_PP;
    GPIOB_init.GPIO_Speed = GPIO_Speed_Level_3;
    GPIOB_init.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIOB_init.GPIO_Pin   = GPIO_Pin_6 | GPIO_Pin_7;

    /* Init GPIOB fo UART */
    GPIO_Init(GPIOB, &GPIOB_init);

    /*
     * Alternate Function = 0
     * Note That we don't use the same Pin Macro
     */
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_0);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_0);
}

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
     * GPIOA14 AF = USART1_TX  => used
     * GPIOA15 AF = USART1_RX  => used
     */

    GPIOA_init.GPIO_Mode  = GPIO_Mode_AF;
    GPIOA_init.GPIO_OType = GPIO_OType_PP;
    GPIOA_init.GPIO_Speed = GPIO_Speed_Level_3;
    GPIOA_init.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIOA_init.GPIO_Pin   = GPIO_Pin_2 | GPIO_Pin_3;

    /* Init GPIOA fo UART */
    GPIO_Init(GPIOA, &GPIOA_init);

    /*
     * Alternate Function = 1
     * Note That we don't use the same Pin Macro
     */
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_1);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_1);
}

void USART2_initialize()
{
    USART_InitTypeDef UART2_init;

    USART_StructInit(&UART2_init);

    /* 
     * Enabling clock
     * USART2 on APB2ENR
     */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);


    /* Init UART */
    UART2_init.USART_BaudRate = 9600; //default from structInit func is 9600
    UART2_init.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    UART2_init.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    UART2_init.USART_Parity = USART_Parity_No;
    UART2_init.USART_StopBits = USART_StopBits_1;
    UART2_init.USART_WordLength = USART_WordLength_8b;

    /* We want Interruption and maybe DMA */
    USART_Init(USART2, &UART2_init);
    USART_Cmd(USART2, ENABLE);
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
    GPIOB_initialize();
    /* Setting up USART */
    USART1_initialize();
    USART2_initialize();
}
