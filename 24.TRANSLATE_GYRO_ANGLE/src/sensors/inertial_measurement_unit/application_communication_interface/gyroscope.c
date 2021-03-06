#include "stdio.h"
#include "arm_math.h"
#include <stdint.h>
#include "sensors/inertial_measurement_unit/bus_communication_interface/imu_bus_interface.h"
#include "sensors/inertial_measurement_unit/mapping_and_configuration/gy-521_register_map.h"
#include "sensors/inertial_measurement_unit/mapping_and_configuration/gy-521_configuration_map.h"

extern const uint8_t gyro_scale_config;
float g_x_gyro_calibration;
float g_y_gyro_calibration;
float g_z_gyro_calibration;

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
            scaling_divider = 131.0;
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
    int8_t      buffer[6];
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

        printf("x d/s = [%f]\n", *x_degree_second);
        printf("y d/s = [%f]\n", *y_degree_second);
        printf("z d/s = [%f]\n", *z_degree_second);

        /*improve accuracy with calibration when done */
        *x_degree_second += g_x_gyro_calibration;
        *y_degree_second += g_y_gyro_calibration;
        *z_degree_second += g_z_gyro_calibration;
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
    uint32_t    measure;
    uint32_t    measure_max;
    float       x_degree_second;
    float       y_degree_second;
    float       z_degree_second;
    float       x_degree_second_sum;
    float       y_degree_second_sum;
    float       z_degree_second_sum;

    measure             = 0;
    measure_max         = 100;
    x_degree_second_sum = 0;
    y_degree_second_sum = 0;
    z_degree_second_sum = 0;
    while (measure < measure_max)
    {
        ret = get_gyro_ds_data(&x_degree_second, &y_degree_second, &z_degree_second);
        if(ret)
        {
            break;
        }
        x_degree_second_sum += x_degree_second;
        y_degree_second_sum += y_degree_second;
        z_degree_second_sum += z_degree_second;
        measure++;
    }
    g_x_gyro_calibration  = (x_degree_second_sum / (float)measure_max) * -1;
    g_y_gyro_calibration  = (y_degree_second_sum / (float)measure_max) * -1;
    g_z_gyro_calibration  = (z_degree_second_sum / (float)measure_max) * -1;

    printf("number of measure = [%ld]\n", measure);
    printf("x calib on measure = [%f]\n", g_x_gyro_calibration);
    printf("y calib on measure = [%f]\n", g_y_gyro_calibration);
    printf("z calib on measure = [%f]\n", g_z_gyro_calibration);

    return (ret);
}

