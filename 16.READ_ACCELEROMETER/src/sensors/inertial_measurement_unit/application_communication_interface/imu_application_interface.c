#include <stdint.h>
#include "sensors/inertial_measurement_unit/bus_communication_interface/imu_bus_interface.h"
#include "sensors/inertial_measurement_unit/mapping_and_configuration/gy-521_register_map.h"
#include "sensors/inertial_measurement_unit/mapping_and_configuration/gy-521_configuration_map.h"

extern const uint8_t accel_scale_config;

/**
 * @brief   Retrieve accelerometer raw data measured by sensor
 *
 * @param   buffer : Memory to store retrieved data
 *
 * @return  0 is everything went right, another value otherwise
 */
static  uint32_t    get_accel_raw_data(uint8_t *buffer, uint8_t len)
{
    uint32_t ret;

    ret = retrieve_data(ACCEL_XOUT_H, buffer, len);
    
    return (ret);
}

/**
 * @brief   Retrieve scaling divider according to config
 *
 * @param   accel_scale : accelerometer scale set in sensor configuration
 *
 * @return  scaling_dividor value
 */
static  uint16_t    get_scaling_divider(uint8_t accel_scale)
{
    uint16_t scaling_divider;

    scaling_divider = 1;
    switch (accel_scale)
    {
        case ACCEL_CONFIG_2G:
            scaling_divider = 16384;
            break;
        case ACCEL_CONFIG_4G:
            scaling_divider = 8192;
            break;
        case ACCEL_CONFIG_8G:
            scaling_divider = 4096;
            break;
        case ACCEL_CONFIG_16G:
            scaling_divider = 2048;
            break;
        default:
            scaling_divider = 1;
            break;
    }
    return (scaling_divider);
}

/**
 * @brief   Retrieve accelerometer g data measured by sensor
 *
 * @param   x_g : g force on x axis
 * @param   y_g : g force on y axis
 * @param   z_g : g force on z axis
 *
 * @return  0 if everything went right, another value otherwise
 */
uint32_t get_accel_g_data(float *x_g, float *y_g, float *z_g)
{
    uint32_t    ret;
    uint8_t     buffer[6];
    uint16_t    scaling_divider;

    ret = get_accel_raw_data(buffer, sizeof(buffer));
    if (0 == ret)
    {
        scaling_divider = get_scaling_divider(accel_scale_config);
        /* Store retrived data */
        *x_g =  ((uint16_t)buffer[0] << 8); /* high */
        *x_g += ((uint16_t)buffer[1] << 0); /* low */
        *y_g =  ((uint16_t)buffer[2] << 8); /* high */
        *y_g += ((uint16_t)buffer[3] << 0); /* low */
        *z_g =  ((uint16_t)buffer[4] << 8); /* high */
        *z_g += ((uint16_t)buffer[5] << 0); /* low */

        /* Translate to g value */
        *x_g /= scaling_divider;
        *y_g /= scaling_divider;
        *z_g /= scaling_divider;
    }
    return (ret);
}
