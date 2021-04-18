#include <stdint.h>
#include "mcu/init_mcu.h"

void assert_failed(uint8_t* file, uint32_t line) {
    (void)file;
    (void)line;
}

int main(void) {
    init_mcu();
    while (1);
    return (0);
}
