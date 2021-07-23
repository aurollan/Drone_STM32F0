#pragma once

#include "stm32f0xx_i2c.h"

#define      I2C_MAX_RETRY  ((uint32_t)10000)

void i2c_initialize();
uint32_t i2c_read(uint16_t device_addr, uint16_t register_to_read, uint8_t *received_data, uint8_t number_of_bytes_to_read);
uint32_t i2c_write(uint16_t device_addr, uint8_t register_to_write, uint8_t data_to_write);


