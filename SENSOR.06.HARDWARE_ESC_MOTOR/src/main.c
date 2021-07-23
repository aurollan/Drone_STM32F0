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
    /* Init mcu */
    init_mcu();
    init_sensors();


    set_motor_power(eMotor1, 0);
    set_motor_power(eMotor2, 25);
    set_motor_power(eMotor3, 50);
    set_motor_power(eMotor4, 75);
    while (1);
    return (0);
}
