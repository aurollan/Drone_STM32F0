#include <stdint.h>
#include <string.h>
#include "sensor/setup_gy-521.h"
#include "mcu/setup_clock/dronef0_clock.h"
#include "mcu/setup_pwm/dronef0_pwm.h"

void assert_failed(uint8_t* file, uint32_t line) {
    (void)file;
    (void)line;
}

int main(void) {
    /* Evetything went as expected we can setup our peripherals */
    clock_initialize();
    pwm_initialize();
    set_duty_cycle(TIM_Channel_1, 25);
    set_duty_cycle(TIM_Channel_2, 50);
    set_duty_cycle(TIM_Channel_3, 75);
    set_duty_cycle(TIM_Channel_4, 100);
    while (1) {};
    return (0);
}
