#pragma once

#include <stdint.h>
#include "sensors/motors/mapping_and_configuration/motors.h"

void power_to_esc(enum motors selected_motor, uint8_t percentage);
