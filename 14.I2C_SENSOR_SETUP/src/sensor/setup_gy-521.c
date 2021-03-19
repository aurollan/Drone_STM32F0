#include "setup_gy-521.h"
#include "gy-521_register_map.h"
#include "mcu/setup_i2c/dronef0_i2c.h"

uint32_t    get_gy_521_who_am_i(uint8_t* who_am_i)
{
    uint32_t i2c_isr_err_occured;
    i2c_isr_err_occured = i2c_read(I2C1, WHO_AM_I << 1, who_am_i, 1);
    return (i2c_isr_err_occured);
}

