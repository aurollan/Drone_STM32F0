#include "motors/setup_motors.h"
#include "inertial_measurement_unit/setup_imu.h"

uint32_t init_sensors(void)
{
    uint32_t err;
    err = setup_motors();
    err = init_inertial_measurement_unit();
    return (err);
}
