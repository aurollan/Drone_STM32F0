#include <stdint.h>
#include "inc/dronef0_uart.h"
#include "stm32f0xx_flash.h"

void assert_failed(uint8_t* file, uint32_t line) {
    (void)file;
    (void)line;
}

int main(void) {
    RCC_ClocksTypeDef   clocks;
    FlagStatus          flag_status;

    /* Enabling HSI clock */
    RCC_HSICmd(ENABLE);
    /* Waiting HSI clock to be ready */
    while (RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);
    /* Switching systemclock to HSI clock */
    RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI);
    /* Checking if we got the right clock source */ 
    if (RCC_GetSYSCLKSource() == RCC_CFGR_SW_HSI) {
        /* Everything if OK */
    }
    /* Setting AHB periph clock to HSI speed */
    RCC_HCLKConfig(RCC_HCLK_Div1);
    /* Setting APB periph clock to HSI speed */
    RCC_PCLKConfig(RCC_HCLK_Div1);
    /* Now we check if we got expected clock frequency */
    RCC_GetClocksFreq(&clocks);
    if (clocks.HCLK_Frequency == HSI_VALUE) {
        /* Everything if OK */
    }
    if (clocks.PCLK_Frequency == HSI_VALUE) {
        /* Everything if OK */
    }
    if (clocks.SYSCLK_Frequency == HSI_VALUE) {
        /* Everything if OK */
    }
    if (clocks.USART1CLK_Frequency == HSI_VALUE) {
        /* Everything if OK */
    }
    if (clocks.USART2CLK_Frequency == HSI_VALUE) {
        /* Everything if OK */
    }
    /* Set the flash latency to correctly read data from flash */
    FLASH_SetLatency(FLASH_Latency_0);

    /* Evetything went as expected we can setup our peripherals */
    communication_initialize();
    while (1)
    {
        //while (USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == SET);
        //character = USART_ReceiveData(USART2);
        while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
        USART_SendData(USART1, 'c');

        flag_status = USART_GetFlagStatus(USART1, USART_FLAG_ORE);
        flag_status = USART_GetFlagStatus(USART1, USART_FLAG_NE);
        flag_status = USART_GetFlagStatus(USART1, USART_FLAG_FE);
        flag_status = USART_GetFlagStatus(USART1, USART_FLAG_PE);

        while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
        USART_SendData(USART2, 'c');

        flag_status = USART_GetFlagStatus(USART2, USART_FLAG_ORE);
        flag_status = USART_GetFlagStatus(USART2, USART_FLAG_NE);
        flag_status = USART_GetFlagStatus(USART2, USART_FLAG_FE);
        flag_status = USART_GetFlagStatus(USART2, USART_FLAG_PE);
    }
    (void)flag_status;
    return (0);
}
