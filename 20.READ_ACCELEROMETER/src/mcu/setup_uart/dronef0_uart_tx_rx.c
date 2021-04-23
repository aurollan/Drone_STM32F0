#include "stm32f0xx_usart.h"

/**
 * @brief   Check if a uart communication error occured
 */
uint32_t uart_error_occur(USART_TypeDef* USARTx)
{
    uint32_t usart_isr_error;

    usart_isr_error = 0;
    if (SET ==USART_GetFlagStatus(USARTx, USART_FLAG_ORE))
    {
        usart_isr_error |= USART_FLAG_ORE;
    }
    if (SET ==USART_GetFlagStatus(USARTx, USART_FLAG_NE))
    {
        usart_isr_error |= USART_FLAG_NE;
    }
    if (SET ==USART_GetFlagStatus(USARTx, USART_FLAG_FE))
    {
        usart_isr_error |= USART_FLAG_FE;
    }
    if (SET ==USART_GetFlagStatus(USARTx, USART_FLAG_PE))
    {
        usart_isr_error |= USART_FLAG_PE;
    }
    return (usart_isr_error);
}

/**
 * @brief   Send data stream through USART communication
 * @param   USARTx          USART_TypeDef*. USART channel selected
 * @param   data            uint8_t*.       Memory to send data from
 * @param   len             uint32_t.       Number of data to send
 * @return  usart_isr_error uint32_t.       Contains only USART ISR register error bits
 */
uint32_t uart_send(USART_TypeDef* USARTx, uint8_t* data, uint32_t len)
{
    uint32_t index;
    uint32_t usart_isr_error;

    index           = 0;
    usart_isr_error = 0;
    while (index < len)
    {
        while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) != SET);
        USART_SendData(USARTx, data[index]);
        usart_isr_error |= uart_error_occur(USARTx);
        if (usart_isr_error)
        {
            break;
        }
        index++;
    }
    return (usart_isr_error);
}

