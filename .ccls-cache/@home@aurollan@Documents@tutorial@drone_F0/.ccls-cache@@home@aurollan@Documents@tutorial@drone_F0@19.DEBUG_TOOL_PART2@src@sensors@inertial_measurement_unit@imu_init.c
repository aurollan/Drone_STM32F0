#include "mapping_and_configuration/gy-521_register_map.h"
#include "mapping_and_configuration/gy-521_configuration_map.h"
#include "bus_communication_interface/imu_bus_interface.h"

const uint8_t accel_scale_config = ACCEL_CONFIG_8G;

uint32_t init_inertial_measurement_unit(void)
{
    uint32_t ret;

    ret = 0;
    /* Input disable and default Digital Low Pass Filter value */
    ret |= set_register_config(CONFIG, 0x00);

    /* Setup only full scale range */
    ret |= set_register_config(ACCEL_CONFIG, accel_scale_config);

    /* We don't use FIFO */
    ret |= set_register_config(FIFO_EN, 0x00);

    /* We don't use interruption for this simple tutorial */
    ret |= set_register_config(INT_ENABLE, 0x00);

    /* As recommeanded in datasheet, we use a gyroscope clock as reference clock */
    ret |= set_register_config(PWR_MGMT_1, PWR_CLK_SEL_GYR_X);
    

    return (ret);
}
