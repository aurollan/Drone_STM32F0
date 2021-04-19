#include "stm32f0xx_gpio.h"
#include "stm32f0xx_usart.h"
#include "stm32f0xx_rcc.h"


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
     * GPIOA14 AF = USART1_TX  => available and selected
     * GPIOA15 AF = USART1_RX  => available and selected
     */

    GPIOA_init.GPIO_Mode  = GPIO_Mode_AF;
    GPIOA_init.GPIO_OType = GPIO_OType_PP;
    GPIOA_init.GPIO_Speed = GPIO_Speed_Level_2;
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
     * USART2 on APB1ENR
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

void uart_initialize() 
{
    /* Setting up GPIO */
    GPIOA_initialize();
    /* Setting up USART */
    USART2_initialize();
}
