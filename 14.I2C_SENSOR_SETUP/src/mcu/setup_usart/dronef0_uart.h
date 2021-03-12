#ifndef DRONEF0_UART_H
#define DRONEF0_UART_H

#include "stm32f0xx_gpio.h"
#include "stm32f0xx_usart.h"
#include "stm32f0xx_rcc.h"

void communication_initialize();
/**
 * @brief   Send data stream through USART communication
 * @param   USARTx          USART_TypeDef*. USART channel selected
 * @param   data            uint8_t*.       Memory to send data from
 * @param   len             uint32_t.       Number of data to send
 * @return  usart_isr_error uint32_t.       Contains only USART ISR register error bits
 */
uint32_t uart_send_data(USART_TypeDef* USARTx, uint8_t* data, uint32_t len);


#endif /* DRONEF0_UART_H */
