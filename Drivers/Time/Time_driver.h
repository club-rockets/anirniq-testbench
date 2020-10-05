#ifndef TIME_DRIVER_H_
#define TIME_DRIVER_H_

#include <stdio.h>
#include "stm32f4xx.h"

void systick_initial(uint16_t freq);
void wait(uint16_t delay);

#endif
