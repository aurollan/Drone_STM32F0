#pragma once
#include <stdint.h>
#include "stm32f0xx_usart.h"

uint32_t uart_send(USART_TypeDef* USARTx, uint8_t* data, uint32_t len);

