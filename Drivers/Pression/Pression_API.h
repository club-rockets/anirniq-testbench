/*
 * thermocouple.h
 *
 *  Created on: 14 nov. 2019
 *      Author: Rouss & Duv
 */

#ifndef PRESSION_API_H_
#define PRESSION_API_H_

#include <String.h>
#include "ADC_Driver.h"
#include "uart1.h"
#include "uart2.h"

#define NB_PRESSURE 3

//Sending parameter
#define GROUND 0
#define AIR 1

typedef struct _API_PRESSURE_STRUCT{ // Structure of one thermocouple

  uint8_t		id;
  uint32_t       *data;
  uint16_t		prsdata;

} API_PRESSURE_STRUCT;

void p_API_init(API_PRESSURE_STRUCT* t_data, uint8_t nb);
void p_init(API_PRESSURE_STRUCT *t_struct, char* name);
void p_start(API_PRESSURE_STRUCT *t_struct, uint16_t *data);
void p_get(API_PRESSURE_STRUCT *t_struct, uint16_t data);
void p_send(API_PRESSURE_STRUCT *t_struct, uint8_t port);
void p_stop(void);

#endif
