#ifndef VALVE_DRIVER_H
#define VALVE_DRIVER_H

#include <stdio.h>
#include "stm32f4xx.h"

#define VALVE_GPIO GPIOE

void valve_initial(void);
void valve_open(uint8_t pin);
void valve_close(uint8_t pin);
uint8_t valve_getstatus(uint8_t pin);

#endif
