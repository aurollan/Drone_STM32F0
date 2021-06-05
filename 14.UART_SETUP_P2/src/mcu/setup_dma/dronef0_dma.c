#include "stm32f0xx_rcc.h"
#include "stm32f0xx_dma.h"
#include "stm32f0xx_usart.h"

char command;

void setup_DMA(void)
{
    DMA_InitTypeDef DMA_InitStruct;

    RCC_AHBPeriphClockCmd(RCC_AHBENR_DMA1EN, ENABLE);

    DMA_StructInit(&DMA_InitStruct);
    DMA_DeInit(DMA1_Channel3);

    DMA_InitStruct.DMA_BufferSize         = 1;
    DMA_InitStruct.DMA_DIR                = DMA_DIR_PeripheralSRC;
    DMA_InitStruct.DMA_M2M                = DMA_M2M_Disable;
    DMA_InitStruct.DMA_MemoryBaseAddr     = (uint32_t)&command;
    DMA_InitStruct.DMA_MemoryDataSize     = DMA_PeripheralDataSize_Byte;
    DMA_InitStruct.DMA_MemoryInc          = DMA_MemoryInc_Disable;
    DMA_InitStruct.DMA_Mode               = DMA_Mode_Circular;
    DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)(&(USART1->RDR));
    DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStruct.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;
    DMA_InitStruct.DMA_Priority           = DMA_Priority_VeryHigh;

    DMA_Init(DMA1_Channel3, &DMA_InitStruct);

    DMA_Cmd(DMA1_Channel3, ENABLE);
    command = 's';
}
