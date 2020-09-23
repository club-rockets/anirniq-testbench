#ifndef SPI_DRIVER_H_
#define SPI_DRIVER_H_

#include <stdio.h>
#include "stm32f4xx.h"

#define SPI1_GPIO GPIOA
#define T_SPI SPI1

//Alternate function configuration
#define SPI1_CLK (0b0101<<(5*4))
#define SPI1_MISO (0b0101<<(6*4))
#define SPI1_MOSI (0b0101<<(7*4))

/* PROTOTYPE */

void spi_init(void);
void spi_send(void);
void spi_dma_init(void);


#endif