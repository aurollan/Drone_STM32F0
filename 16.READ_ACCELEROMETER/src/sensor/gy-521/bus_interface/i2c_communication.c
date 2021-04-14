#include "mcu/setup_i2c/dronef0_i2c.h"
/**
 * @brief   Set the register with configuration chose
 *
 * @param   register_to_set. The register address we want to configure
 *
 * @return  
 */

uint32_t set_register_config(uint8_t register_to_set, uint8_t configuration)
{
    uint32_t i2c_isr_err_occured;

    i2c_isr_err_occured = i2c_write(I2C1, (uint16_t)I2C_SLAVE_ADDR_AD1 << 1, register_to_set, configuration);

    return (i2c_isr_err_occured);
}

uint32_t    get_register_config(uint8_t register_to_read, uint8_t* config_read)
{

    uint32_t i2c_isr_err_occured;

    i2c_isr_err_occured = i2c_read(I2C1, (uint16_t)(I2C_SLAVE_ADDR_AD1) << 1, register_to_read,  config_read, 1);

    return (i2c_isr_err_occured);

}

uint32_t    retrieve_data(uint8_t start_register, uint8_t len, uint8_t* buffer)
{
    uint32_t i2c_isr_err_occured;

    i2c_isr_err_occured = i2c_read(I2C1, (uint16_t)(I2C_SLAVE_ADDR_AD1) << 1, start_register,  buffer, len);

    return (i2c_isr_err_occured);
}

