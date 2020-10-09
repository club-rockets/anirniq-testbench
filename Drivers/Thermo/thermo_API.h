/*
 * thermocouple.h
 *
 *  Created on: 14 nov. 2019
 *      Author: Rouss & Duv
 */

#ifndef THERMO_API_H_
#define THERMO_API_H_

#include <String.h>
#include "MAX31856drv.h"

#define NB_THERMO 5
#define API_DRIVER_CONST 0.0078125

#define SPI_T1 (1<<8)

typedef struct _API_THERMO_STRUCT{ // Structure of one thermocouple

  char			name[20];
  GPIO_TypeDef* GPIO;
  uint32_t      pin;
  uint8_t       data[16];

} API_THERMO_STRUCT; 

void t_junction_temp (const uint8_t * rxBuffer, long * data, double * temperature);    ///< Pointer to \ref ARM_SPI_GetVersion : Get driver version.
void t_temp        (const uint8_t * rxBuffer, long * data, double * temperature);    ///< Pointer to \ref ARM_SPI_GetCapabilities : Get driver capabilities.
void API_init(API_THERMO_STRUCT* t_data, uint8_t nb);
void t_init(API_THERMO_STRUCT *t_struct, char* name);                                                         ///< Pointer to \ref ARM_SPI_Initialize : Initialize SPI Interface.                                                       ///< Pointer to \ref ARM_SPI_Uninitialize : De-initialize SPI Interface.
void t_get(API_THERMO_STRUCT *t_struct);                                                        ///< Pointer to \ref ARM_SPI_PowerControl : Control SPI Interface Power.                                                          ///< Pointer to \ref ARM_SPI_Send : Start sending data to SPI Interface.
void t_start(API_THERMO_STRUCT *t_struct,uint8_t conversion_mode);
void t_stop(API_THERMO_STRUCT *t_struct);

#endif
