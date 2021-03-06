#include "mcu/i2c/setup/dronef0_i2c.h"
#include "sensors/inertial_measurement_unit/mapping_and_configuration/gy-521_register_map.h"

/**
 * @brief   Set the specified register with configuration chosed
 *
 * @param   register_to_set : The register address we want to configure
 * @param   configuration   : The configuration to set for specified register
 *
 * @return  0 if everything went right, another value otherwise
 */
uint32_t set_register_config(uint8_t register_to_set, uint8_t configuration)
{
    uint32_t i2c_isr_err_occured;

    i2c_isr_err_occured = i2c_write((uint16_t)I2C_SLAVE_ADDR_AD1 << 1, register_to_set, configuration);

    return (i2c_isr_err_occured);
}

/**
 * @brief   Get the specified register configuration
 *
 * @param   register_to_get : The register address we want to get configuration from
 * @param   configuration   : Memory to store value read
 *
 * @return  0 if everything went right, another value otherwise
 */
uint32_t    get_register_config(uint8_t register_to_read, uint8_t* config_read)
{

    uint32_t i2c_isr_err_occured;

    i2c_isr_err_occured = i2c_read((uint16_t)(I2C_SLAVE_ADDR_AD1) << 1, register_to_read,  config_read, 1);

    return (i2c_isr_err_occured);

}

/**
 * @brief   Get a stream of data from the specified register
 *
 * @param   start_register : The register address we want to start get data from
 * @param   buffer         : Memory to store value read
 * @param   len            : Number of data to read and store
 *
 * @return  0 if everything went right, another value otherwise
 */
uint32_t    retrieve_data(uint8_t start_register, uint8_t* buffer, uint8_t len)
{
    uint32_t i2c_isr_err_occured;

    i2c_isr_err_occured = i2c_read((uint16_t)(I2C_SLAVE_ADDR_AD1) << 1, start_register,  buffer, len);

    return (i2c_isr_err_occured);
}

