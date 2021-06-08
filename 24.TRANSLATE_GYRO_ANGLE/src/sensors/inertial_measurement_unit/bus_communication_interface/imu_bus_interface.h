#pragma once

#include <stdint.h>

/**
 * @brief   Get the timestamp in us
 *
 * @return  timestamp value in us
 */
uint32_t    get_timestamp_us(void);
    
/**
 * @brief   Set the specified register with configuration chosed
 *
 * @param   register_to_set : The register address we want to configure
 * @param   configuration   : The configuration to set for specified register
 *
 * @return  0 if everything went right, another value otherwise
 */
uint32_t    set_register_config(uint8_t register_to_set, uint8_t configuration);

/**
 * @brief   Get the specified register configuration
 *
 * @param   register_to_get : The register address we want to get configuration from
 * @param   configuration   : Memory to store value read
 *
 * @return  0 if everything went right, another value otherwise
 */
uint32_t    get_register_config(uint8_t register_to_read, uint8_t* config_read);

/**
 * @brief   Get a stream of data from the specified register
 *
 * @param   start_register : The register address we want to start get data from
 * @param   buffer         : Memory to store value read
 * @param   len            : Number of data to read and store
 *
 * @return  0 if everything went right, another value otherwise
 */
uint32_t    retrieve_data(uint8_t start_register, uint8_t* buffer, uint8_t len);
