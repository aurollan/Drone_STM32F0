#include <stdint.h>
#include <string.h>
#include "sensor/setup_gy-521.h"
#include "mcu/setup_clock/dronef0_clock.h"
#include "mcu/setup_i2c/dronef0_i2c.h"
#include "mcu/setup_uart/dronef0_uart.h"

void assert_failed(uint8_t* file, uint32_t line) {
    (void)file;
    (void)line;
}

int main(void) {
    /* Evetything went as expected we can setup our peripherals */
    clock_initialize();
    i2c_initialize();
    uart_initialize();
    while (1) {};
    return (0);
}
