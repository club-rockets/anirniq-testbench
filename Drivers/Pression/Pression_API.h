/*
 * thermocouple.h
 *
 *  Created on: 14 nov. 2019
 *      Author: Rouss & Duv
 */

#ifndef PRESSION_API_H_
#ifndef PRESSION_API_H_

#include <String.h>
#include "ADC_Driver.h"

#define NB_PRESSION 5

typedef struct _API_PRESSURE_STRUCT{ // Structure of one thermocouple

  char			name[20];
  uint8_t       *data;

} API_PRESSURE_STRUCT; 

void p_API_init(API_PRESSURE_STRUCT* t_data, uint8_t *data, uint8_t nb);
void p_init(API_PRESSURE_STRUCT *t_struct, char* name);
void p_start(API_PRESSURE_STRUCT *t_struct);
void p_stop(void);

#endif