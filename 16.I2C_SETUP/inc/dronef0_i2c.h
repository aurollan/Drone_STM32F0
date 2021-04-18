#ifndef DRONE_F0_I2C_H
#define DRONE_F0_I2C_H

#include "stm32f0xx_gpio.h"
#include "stm32f0xx_i2c.h"
#include "stm32f0xx_rcc.h"
#include <errno.h>

#define      I2C_MAX_RETRY  ((uint32_t)100000)

void i2c_initialize();
uint32_t i2c_read(I2C_TypeDef* I2Cx, uint16_t register_to_read, uint8_t *received_data, uint8_t number_of_bytes_to_read);
uint32_t i2c_write(I2C_TypeDef* I2Cx, uint8_t register_to_write, uint8_t data_to_write);


#endif /* DRONE_F0_I2C_H */

