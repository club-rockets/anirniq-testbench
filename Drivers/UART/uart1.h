/*
 * uart1.h
 *
 *  Created on: 30 septembre 2020
 *      Author: Nathan Roussel and Marc-Andre Denis
 */

#ifndef DRIVERS_UART1_H_
#define DRIVERS_UART1_H_

#include <stdio.h>
#include "stm32f4xx.h"

#define UART1_BUFFER_SIZE 100

void uart1_init(void);

uint32_t uart1_transmit(uint8_t *buff,uint8_t size);

uint8_t uart1_rxBuffAvailable(void);

uint8_t uart1_get(void);

void uart1_registerRxCallback(void (*callback)(void));

#endif /* DRIVERS_UART1_H_ */