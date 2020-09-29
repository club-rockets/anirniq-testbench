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

#define NB_PRESSURE 3

typedef struct _API_PRESSURE_STRUCT{ // Structure of one thermocouple

  char			name[20];
  uint32_t       *data;

} API_PRESSURE_STRUCT;

void p_API_init(API_PRESSURE_STRUCT* t_data, uint16_t *data, uint8_t nb);
void p_init(API_PRESSURE_STRUCT *t_struct, char* name);
void p_start(API_PRESSURE_STRUCT *t_struct, uint16_t *data);
void p_stop(void);

#endif
