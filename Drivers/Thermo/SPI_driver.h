#ifndef SPI_DRIVER_H_
#define SPI_DRIVER_H_

#include <stdio.h>
#include "stm32f4xx.h"

#define SPI1_GPIO GPIOC

/* PROTOTYPE */

void spi_init(void);
void spi_send(void);


#endif