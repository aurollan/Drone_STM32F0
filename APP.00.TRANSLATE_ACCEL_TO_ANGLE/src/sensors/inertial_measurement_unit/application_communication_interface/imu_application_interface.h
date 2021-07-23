#pragma once

#include <stdint.h>

/**
 * @brief   Retrieve accelerometer g data measured by sensor
 *
 * @param   x_g : g force on x axis
 * @param   y_g : g force on y axis
 * @param   z_g : g force on z axis
 *
 * @return  0 if everything went right, another value otherwise
 */
uint32_t get_accel_g_data(float *x_g, float *y_g, float *z_g);
