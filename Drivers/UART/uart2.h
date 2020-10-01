/*
 * uart2.h
 *
 *  Created on: 30 mai 2019
 *      Author: Marc-Andre Denis
 */

#ifndef DRIVERS_UART2_H_
#define DRIVERS_UART2_H_

#include <stdio.h>
#include "stm32f4xx.h"

#define UART2_BUFFER_SIZE 100

void uart2_init(void);

uint32_t uart2_transmit(uint8_t *buff,uint8_t size);

uint8_t uart2_rxBuffAvailable(void);

uint8_t uart2_get(void);

void uart2_registerRxCallback(void (*callback)(void));

#endif /* DRIVERS_UART2_H_ */
