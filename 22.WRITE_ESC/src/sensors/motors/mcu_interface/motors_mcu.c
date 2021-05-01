#include "mcu/pwm/sensor_interface/pwm_write.h"
#include "sensors/motors/mapping_and_configuration/motors.h"

const uint16_t max_duty_cycle = 2000;

void power_to_esc(enum motors selected_motor, uint8_t percentage)
{
    uint16_t percentage_in_us;
    
    percentage_in_us = 0;
    if (percentage > 100)
    {
        /**
         * Prevent max_duty_cycle overflow
         */
        percentage = 100;
    }
    else if (0 == percentage)
    {
        percentage = 1;
    }
    percentage_in_us =  max_duty_cycle / 100;
    percentage_in_us *= percentage;
    switch (selected_motor)
    {
        case eMotor1:
            set_duty_cycle(TIM_Channel_1, percentage_in_us);
            break;
        case eMotor2:
            set_duty_cycle(TIM_Channel_2, percentage_in_us);
            break;
        case eMotor3:
            set_duty_cycle(TIM_Channel_3, percentage_in_us);
            break;
        case eMotor4:
            set_duty_cycle(TIM_Channel_4, percentage_in_us);
            break;
    }
}
