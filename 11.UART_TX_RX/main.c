#include <stdint.h>
#include "stm32f0xx_gpio.h"
#include "stm32f0xx_rcc.h"

void assert_failed(uint8_t* file, uint32_t line) {
    (void)file;
    (void)line;
}

int main(void) {
    GPIO_TypeDef GPIO;
    GPIO_Init();
    return (0);
}
