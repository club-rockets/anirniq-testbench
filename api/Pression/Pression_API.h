/*
 * thermocouple.h
 *
 *  Created on: 14 nov. 2019
 *      Author: Rouss & Duv
 */

#ifndef PRESSION_API_H_
#define PRESSION_API_H_

#include <String.h>
#include "buffer.h"
#include "ADC_Driver.h"
#include "uart1.h"
#include "uart2.h"

#define NB_PRESSURE 2

//Sending parameter
#define GROUND 0
#define AIR 1
#define ASCII 0
#define BINARY 1

typedef struct _API_PRESSURE_STRUCT{ // Structure of one thermocouple

  uint8_t		id;
  uint16_t       *data;

} API_PRESSURE_STRUCT;

void p_API_init(void);
void p_init(ACTUATOR_STRUCT *t_struct, uint8_t id, uint16_t *adr);
void p_start(uint16_t *data);
void p_send(ACTUATOR_STRUCT *t_struct, uint8_t port, uint8_t format);
void p_convert(ACTUATOR_STRUCT *t_struct);
void p_stop(void);
uint8_t p_push(ACTUATOR_STRUCT *t_struct, DataBuffer *buffer);

#endif
