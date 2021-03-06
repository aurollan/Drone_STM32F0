#include "sensors/motors/mcu_interface/motors_mcu.h"
#include "sensors/motors/mapping_and_configuration/motors.h"

void set_motor_power(enum motors selected_motor, uint8_t percentage)
{
    power_to_esc(selected_motor, percentage);
}
