#ifndef SYSTICK_H
#define SYSTICK_H
#include "stm32f1xx_hal.h"

void Delay_us(uint32_t us);
void Delay_ms(uint32_t ms);
void Delay_s(uint32_t s);

#endif
