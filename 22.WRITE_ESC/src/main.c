#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "sensors/init_sensors.h"
#include "mcu/init_mcu.h"
#include "sensors/inertial_measurement_unit/application_interface/accelerometer/accelerometer.h"
#include "sensors/inertial_measurement_unit/application_interface/gyroscope/gyroscope.h"
#include "sensors/motors/application_interface/power.h"


void assert_failed(uint8_t* file, uint32_t line) {
    (void)file;
    (void)line;
}

int main(void) {
    uint32_t err;
    /* Init mcu */
    init_mcu();
    init_sensors();


    //uint8_t buffer[6];
    float x_g;
    float y_g;
    float z_g;
    float x_ds;
    float y_ds;
    float z_ds;
    set_motor_power(eMotor1, 50);
    while (1)
    {
        err = get_accel_g_data(&x_g, &y_g, &z_g);
        err = get_gyro_ds_data(&x_ds, &y_ds, &z_ds);
        if (err)
        {
            printf("an error occured\n");
        }
        else
        {
            printf("x_g = [%f] y_g = [%f] z_g = [%f]\n",x_g, y_g, z_g);
            printf("x_ds = [%f] y_ds = [%f] z_ds = [%f]\n",x_ds, y_ds, z_ds);
        }
    }
    return (0);
}
