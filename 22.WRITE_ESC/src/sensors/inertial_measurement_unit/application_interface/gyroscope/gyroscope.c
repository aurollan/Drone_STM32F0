#include <stdint.h>
#include "sensors/inertial_measurement_unit/mcu_interface/imu_mcu.h"
#include "sensors/inertial_measurement_unit/mapping_and_configuration/gy-521_register_map.h"
#include "sensors/inertial_measurement_unit/mapping_and_configuration/gy-521_configuration_map.h"

extern const uint8_t gyro_scale_config;

/**
 * @brief   Retrieve accelerometer raw data measured by sensor
 *
 * @param   buffer : Memory to store retrieved data
 *
 * @return  0 is everything went right, another value otherwise
 */
static uint32_t    get_gyro_raw_data(uint8_t *buffer, uint8_t len)
{
    uint32_t ret;

    ret = retrieve_data(GYRO_XOUT_H, buffer, len);
    
    return (ret);
}


/**
 * @brief   Retrieve scaling divider according to config
 *
 * @param   gyro_scale : accelerometer scale set in sensor configuration
 *
 * @return  scaling_dividor value
 */
static  float    get_gyro_scaling_divider(uint8_t accel_scale)
{
    float scaling_divider;

    scaling_divider = 1;
    switch (accel_scale)
    {
        case GYRO_CONFIG_250:
            scaling_divider = 131;
            break;
        case GYRO_CONFIG_500:
            scaling_divider = 65.5;
            break;
        case GYRO_CONFIG_1000:
            scaling_divider = 32.8;
            break;
        case GYRO_CONFIG_2000:
            scaling_divider = 16.4;
            break;
        default:
            scaling_divider = 1;
            break;
    }
    return (scaling_divider);
}

/**
 * @brief   Retrieve gyroscope degree per second data measured by sensor
 *
 * @param   x_degree_second : degree per second on x axis
 * @param   y_degree_second : degree per second on y axis
 * @param   z_degree_second : degree per second on z axis
 *
 * @return  0 if everything went right, another value otherwise
 */
uint32_t get_gyro_ds_data(float *x_degree_second, float *y_degree_second, float *z_degree_second)
{
    uint32_t    ret;
    int8_t     buffer[6];
    uint16_t    scaling_divider;

    ret = get_gyro_raw_data((uint8_t*)buffer, sizeof(buffer));
    if (0 == ret)
    {
        scaling_divider = get_gyro_scaling_divider(gyro_scale_config);

        *x_degree_second =  ((int16_t)buffer[0] << 8); /* high */
        *x_degree_second += ((int16_t)buffer[1] << 0); /* low */
        *y_degree_second =  ((int16_t)buffer[2] << 8); /* high */
        *y_degree_second += ((int16_t)buffer[3] << 0); /* low */
        *z_degree_second =  ((int16_t)buffer[4] << 8); /* high */
        *z_degree_second += ((int16_t)buffer[5] << 0); /* low */

        /* Translate to g value */
        *x_degree_second /= scaling_divider;
        *y_degree_second /= scaling_divider;
        *z_degree_second /= scaling_divider;
    }
    return (ret);
}


