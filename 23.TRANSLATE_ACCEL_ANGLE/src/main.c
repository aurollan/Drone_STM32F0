#include <arm_math.h>
#include <math.h>
#include <stdint.h>
#include <string.h>
#include "sensors/inertial_measurement_unit/imu_init.h"
#include "sensors/inertial_measurement_unit/application_communication_interface/imu_application_interface.h"
#include "mcu/setup_uart/dronef0_uart_tx_rx.h"
#include "mcu/init_mcu.h"
#include "sensors/inertial_measurement_unit/bus_communication_interface/imu_bus_interface.h"

#include <stdio.h>

void assert_failed(uint8_t* file, uint32_t line) {
    (void)file;
    (void)line;
}

int main(void) {
    uint32_t err;

    /* Init mcu */
    init_mcu();
    /* Don't start application if initialization fail */
    if (0 != init_inertial_measurement_unit()) {
        while(1);
    }
    //uint8_t buffer[6];
    float x_g;
    float y_g;
    float z_g;

    float x_a;
    float y_a;
    // float z_a;

    float x_squared;
    float y_squared;
    float z_squared;

    float x_multiplication;
    float y_multiplication;

    float x_sqrt;
    float y_sqrt;

    float x_div;
    float y_div;

    float x_atanf;
    float y_atanf;
    while (1)
    {
        err = get_accel_g_data(&x_g, &y_g, &z_g);
        if (err)
        {
            printf("an error occured\n");
        }
        else
        {
            // printf("x_g = [%f] y_g = [%f] z_g = [%f]\n",x_g, y_g, z_g);
            //x_a = acosf(x_g);
            //y_a = acosf(y_g);
            //z_a = acosf(z_g);

            x_squared  = x_g * x_g;
            y_squared  = y_g * y_g;
            z_squared  = z_g * z_g;

            //printf("x_squared = [%f]\n", x_squared);
            //printf("y_squared = [%f]\n", y_squared);
            //printf("z_squared = [%f]\n", z_squared);

            x_multiplication = y_squared + z_squared;
            y_multiplication = x_squared + z_squared;

            // printf("x_multiplication = [%f]\n", x_multiplication);
            // printf("y_multiplication = [%f]\n", y_multiplication);

            x_sqrt = sqrtf(x_multiplication);
            y_sqrt = sqrtf(y_multiplication);

            // printf("x_sqrt = [%f]\n", x_sqrt);
            // printf("y_sqrt = [%f]\n", y_sqrt);

            x_div = x_g / x_sqrt;
            y_div = y_g / y_sqrt;
            // printf("x_division = [%f]\n", x_div);
            // printf("y_division = [%f]\n", y_div);


            x_atanf = atanf(x_div);
            y_atanf = atanf(y_div);

            (void)x_atanf;
            (void)y_atanf;

            // printf("x_atanf = [%f]\n", x_atanf);
            // printf("y_atanf = [%f]\n", y_atanf);

            x_a = atanf(x_g / (sqrtf(y_g * y_g + z_g * z_g))) * 180.0 / PI;
            y_a = atanf(y_g / (sqrtf(x_g * x_g + z_g * z_g))) * 180.0 / PI;
            printf("x_angle = [%f] y_angle = [%f] \n",x_a, y_a);
            // printf("x_angle = [%f] y_angle = [%f] z_angle = [%f]\n",x_a, y_a, z_a);
        }
        
    }
    return (0);
}
