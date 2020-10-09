#ifndef TIME_DRIVER_H_
#define TIME_DRIVER_H_

#include <stdio.h>
#include "stm32f4xx.h"

void systick_initial(void);
void wait(uint32_t delay);
uint32_t get_time_ms(void);

#endif
