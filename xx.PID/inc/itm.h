#ifndef __ITM_H__
#define __ITM_H__

#include "stm32f303xc.h"

int _write(int32_t file, char* ptr, int32_t len);
void ITM_init(void);

#endif
