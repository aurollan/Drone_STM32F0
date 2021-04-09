#include "setup_gy-521.h"
#include "gy-521_register_map.h"
#include "gy-521_configuration_map.h"


uint32_t    get_gy_521_who_am_i(uint8_t* who_am_i)
{
    uint32_t i2c_isr_err_occured;

    i2c_isr_err_occured = i2c_read(I2C1, (uint16_t)(I2C_SLAVE_ADDR_AD1) << 1, WHO_AM_I,  who_am_i, 1);
    return (i2c_isr_err_occured);
}

uint32_t get_gy_521_pwr(uint8_t* pwr)
{

    uint32_t i2c_isr_err_occured;

    i2c_isr_err_occured = i2c_read(I2C1, (uint16_t)(I2C_SLAVE_ADDR_AD1) << 1, PWR_MGMT_1,  pwr, 1);
    return (i2c_isr_err_occured);
}

uint32_t set_gy_521_pwr(uint8_t data)
{

    uint32_t i2c_isr_err_occured;

    i2c_isr_err_occured = i2c_write(I2C1, (uint16_t)(I2C_SLAVE_ADDR_AD1) << 1, PWR_MGMT_1,  data);
    return (i2c_isr_err_occured);
}

uint32_t    wakeup_from_sleep()
{
    uint32_t i2c_isr_err_occured;

    i2c_isr_err_occured = i2c_write(I2C1, (uint16_t)(I2C_SLAVE_ADDR_AD1) << 1, PWR_MGMT_1, (uint8_t)0x00);
    return (i2c_isr_err_occured);
}
