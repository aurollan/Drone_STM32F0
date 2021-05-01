#include "stm32f0xx_rcc.h"
#include "stm32f0xx_flash.h"

void clock_initialize(void)
{
    RCC_ClocksTypeDef   clocks;
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
}

