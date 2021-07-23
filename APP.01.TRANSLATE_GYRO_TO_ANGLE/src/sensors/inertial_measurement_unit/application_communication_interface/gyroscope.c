#include "stdio.h"
#include "arm_math.h"
#include <stdint.h>
#include "sensors/inertial_measurement_unit/bus_communication_interface/imu_bus_interface.h"
#include "sensors/inertial_measurement_unit/mapping_and_configuration/gy-521_register_map.h"
#include "sensors/inertial_measurement_unit/mapping_and_configuration/gy-521_configuration_map.h"

extern const uint8_t gyro_scale_config;
int32_t g_x_gyro_calibration;
int32_t g_y_gyro_calibration;
int32_t g_z_gyro_calibration;

/**
 * @brief   Retrieve gyroscope data from sensor registers
 *
 * @param   buffer  : Memory to store retrieved data
 * @param   len     : number of register to retrieve data from
 *
 * @return  0 is everything went right, another value otherwise
 */
static uint32_t    get_gyro_register_data(uint8_t *buffer, uint8_t len)
{
    uint32_t ret;

    ret = retrieve_data(GYRO_XOUT_H, buffer, len);
    
    return (ret);
}

/**
 * @brief   Format data read from gyroscope register
 *
 * @param   x_raw : translated data x
 * @param   y_raw : translated data y
 * @param   z_raw : translated data z
 *
 * @return  0 is everything went right, another value otherwise
 */
static uint32_t     get_gyro_raw_data(int16_t *x_raw, int16_t *y_raw, int16_t *z_raw)
{
    uint32_t    ret;
    uint8_t     buffer[6];

    ret = get_gyro_register_data((uint8_t*)buffer, sizeof(buffer));
    if (0 == ret)
    {
        *x_raw =  ((int16_t)buffer[0] << 8); /* high */
        *x_raw += ((int16_t)buffer[1] << 0); /* low  */
        *y_raw =  ((int16_t)buffer[2] << 8); /* high */
        *y_raw += ((int16_t)buffer[3] << 0); /* low  */
        *z_raw =  ((int16_t)buffer[4] << 8); /* high */
        *z_raw += ((int16_t)buffer[5] << 0); /* low  */
    }
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
            scaling_divider = 131.0f;
            break;
        case GYRO_CONFIG_500:
            scaling_divider = 65.5f;
            break;
        case GYRO_CONFIG_1000:
            scaling_divider = 32.8f;
            break;
        case GYRO_CONFIG_2000:
            scaling_divider = 16.4f;
            break;
        default:
            scaling_divider = 1.0f;
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
    float       scaling_divider;
    int16_t     x_raw;
    int16_t     y_raw;
    int16_t     z_raw;

    ret = get_gyro_raw_data(&x_raw, &y_raw, &z_raw);
    if (0 == ret)
    {
        scaling_divider = get_gyro_scaling_divider(gyro_scale_config);

        /* Improve precision with calibration offset */
        x_raw += g_x_gyro_calibration;
        y_raw += g_y_gyro_calibration;
        z_raw += g_z_gyro_calibration;

        /* Translate to d/s value */
        *x_degree_second = (float)x_raw / scaling_divider;
        *y_degree_second = (float)y_raw / scaling_divider;
        *z_degree_second = (float)z_raw / scaling_divider;
    }
    return (ret);
}

uint32_t    get_gyro_angles(float *x_angle_rotation,
                            float *y_angle_rotation,
                            float *z_angle_rotation)
{
    float               x_degree_second;
    float               y_degree_second;
    float               z_degree_second;
    uint32_t            err;
    uint16_t            time_delta_ms;
    uint16_t            new_timestamp_ms;
    static  uint16_t    last_timestamp_ms;
    static  uint16_t    init;

    err = 0;
    if (0 == init)
    {
        last_timestamp_ms = get_timestamp_ms();
        *x_angle_rotation = 0;
        *y_angle_rotation = 0;
        *z_angle_rotation = 0;
        init += 1;
        return (err);
    }
    err = get_gyro_ds_data(&x_degree_second, &y_degree_second, &z_degree_second);

    new_timestamp_ms  = get_timestamp_ms();
    time_delta_ms     = new_timestamp_ms - last_timestamp_ms;
    last_timestamp_ms = new_timestamp_ms;

    *x_angle_rotation = ((float)time_delta_ms / 1000.0f) * x_degree_second;
    *y_angle_rotation = ((float)time_delta_ms / 1000.0f) * y_degree_second;
    *z_angle_rotation = ((float)time_delta_ms / 1000.0f) * z_degree_second;

    return (err);
}


uint32_t    gyro_calibration()
{
    uint32_t    ret;
    int32_t     measure;
    int32_t     measure_max;
    int16_t     x_raw;
    int16_t     y_raw;
    int16_t     z_raw;
    int32_t     x_raw_sum;
    int32_t     y_raw_sum;
    int32_t     z_raw_sum;

    measure     = 0;
    measure_max = 100;
    x_raw_sum   = 0;
    y_raw_sum   = 0;
    z_raw_sum   = 0;
    while (measure < measure_max)
    {
        ret = get_gyro_raw_data(&x_raw, &y_raw, &z_raw);
        if (0 != ret)
        {
            break;
        }
        x_raw_sum  += x_raw;
        y_raw_sum  += y_raw;
        z_raw_sum  += z_raw;
        measure++;
    }

    g_x_gyro_calibration  = (x_raw_sum / measure) * -1;
    g_y_gyro_calibration  = (y_raw_sum / measure) * -1;
    g_z_gyro_calibration  = (z_raw_sum / measure) * -1;

    return (ret);
}

