#include <stdint.h>
#include <string.h>
#include "sensors/inertial_measurement_unit/imu_init.h"
#include "sensors/inertial_measurement_unit/application_communication_interface/imu_application_interface.h"
#include "mcu/setup_uart/dronef0_uart_tx_rx.h"
#include "mcu/init_mcu.h"
#include "sensors/inertial_measurement_unit/bus_communication_interface/imu_bus_interface.h"

#include "mcu/setup_timer/dronef0_timer.h"
#include <stdio.h>

void assert_failed(uint8_t* file, uint32_t line) {
    (void)file;
    (void)line;
}

int main(void) {
    /* Init mcu */
    init_mcu();

    uint8_t data;
    uint32_t err;
    data = 0x00;
    err = get_register_config(((uint8_t)0x75), &data);
    if (err)
    {
        printf("An error occur\n");
    }
    printf("WHOAMI [%x]\n", data);

    /* Don't start application if initialization fail */
    if (0 != init_inertial_measurement_unit()) {
        while(1);
    }
    //uint8_t buffer[6];
    float x_angle = 0;
    float y_angle = 0;
    float z_angle = 0;

    float x_angle_rotation = 0;
    float y_angle_rotation = 0;
    float z_angle_rotation = 0;
    while (1)
    {
        volatile uint16_t time;
        time = get_counter_ms();
        while (time + 1000 > get_counter_ms()) {};
        err = get_gyro_angles(&x_angle_rotation, &y_angle_rotation, &z_angle_rotation);
        if (err)
        {
            printf("an error occured\n");
        }
        else
        {
            x_angle += x_angle_rotation;
            y_angle += y_angle_rotation;
            z_angle += z_angle_rotation;
            printf("x_angle = [%f] y_angle = [%f] z_angle = [%f]\n",x_angle, y_angle, z_angle);
        }
    }
    return (0);
}
