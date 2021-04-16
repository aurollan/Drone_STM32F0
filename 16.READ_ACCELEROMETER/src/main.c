#include <stdint.h>
#include <string.h>
#include "sensors/inertial_measurement_unit/imu_init.h"
#include "mcu/setup_clock/dronef0_clock.h"
#include "mcu/setup_i2c/dronef0_i2c.h"
#include "mcu/setup_uart/dronef0_uart.h"

void assert_failed(uint8_t* file, uint32_t line) {
    (void)file;
    (void)line;
}

int main(void) {
    /* Everything went as expected we can setup our mcu */
    clock_initialize();
    i2c_initialize();
    uart_initialize();
    /* Don't start application if initialization fail */
    if (0 != init_inertial_measurement_unit()) {
        while(1);
    }
    while (1) {};
    return (0);
}
