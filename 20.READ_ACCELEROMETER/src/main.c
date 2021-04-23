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
    /* Init mcu */
    init_mcu();

    uint8_t data;
    while (1) {
        get_register_config(((uint8_t)0x75), &data);
        data += 35;
        uart_send(USART1, &data, 1);
    }

    /* Don't start application if initialization fail */
    if (0 != init_inertial_measurement_unit()) {
        while(1);
    }
    //uint8_t buffer[6];
    char str[100];
    float x_g;
    float y_g;
    float z_g;
    while (1)
    {
        get_accel_g_data(&x_g, &y_g, &z_g);
        sprintf(str,"x_g = [%f]\n y_g = [%f]\n z_g = [%f]\n",x_g, y_g, z_g);
        uart_send(USART1, (uint8_t*)str, strlen(str));
    }
    return (0);
}
