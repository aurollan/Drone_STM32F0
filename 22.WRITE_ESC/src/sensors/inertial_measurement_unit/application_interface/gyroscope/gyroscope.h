/**
 * @brief   Retrieve gyroscope degree per second data measured by sensor
 *
 * @param   x_degree_second : degree per second on x axis
 * @param   y_degree_second : degree per second on y axis
 * @param   z_degree_second : degree per second on z axis
 *
 * @return  0 if everything went right, another value otherwise
 */
uint32_t get_gyro_ds_data(float *x_degree_second, float *y_degree_second, float *z_degree_second);

