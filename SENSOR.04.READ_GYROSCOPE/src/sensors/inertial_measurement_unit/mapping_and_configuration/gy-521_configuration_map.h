#pragma once
#include <stdint.h>

#define ACCEL_CONFIG_2G     ((uint8_t)(0x00 << 3))
#define ACCEL_CONFIG_4G     ((uint8_t)(0x01 << 3))
#define ACCEL_CONFIG_8G     ((uint8_t)(0x02 << 3))
#define ACCEL_CONFIG_16G    ((uint8_t)(0x03 << 3))

#define GYRO_CONFIG_250     ((uint8_t)(0x00 << 3))
#define GYRO_CONFIG_500     ((uint8_t)(0x01 << 3))
#define GYRO_CONFIG_1000    ((uint8_t)(0x02 << 3))
#define GYRO_CONFIG_2000    ((uint8_t)(0x03 << 3))

#define PWR_CLK_SEL_GYR_X   ((uint8_t)(0x01 << 0))

