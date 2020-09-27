/*
 * thermocouple.h
 *
 *  Created on: 14 nov. 2019
 *      Author: Rouss & Duv
 */

#ifndef THERMO_API_H_
#define THERMO_API_H_

#include "SPI_driver.h"
#include "MAX31856drv.h"

#define NB_THERMO 5
#define API_DRIVER_CONST 0.0078125

typedef struct _API_THERMO_STRUCT{ // Structure of one thermocouple

  GPIO_TypeDef* myGPIO;
  uint32_t      enMask;
  uint8_t       data;

} API_THERMO_STRUCT; 

void junction_temp (const uint8_t * rxBuffer, long * data, double * temperature);    ///< Pointer to \ref ARM_SPI_GetVersion : Get driver version.
void temp        (const uint8_t * rxBuffer, long * data, double * temperature);    ///< Pointer to \ref ARM_SPI_GetCapabilities : Get driver capabilities.
void init         (uint8_t nb);                                                           ///< Pointer to \ref ARM_SPI_Initialize : Initialize SPI Interface.
void uninit        (void);                                                           ///< Pointer to \ref ARM_SPI_Uninitialize : De-initialize SPI Interface.
void get         (void);                                                           ///< Pointer to \ref ARM_SPI_PowerControl : Control SPI Interface Power.
void who           (void);                                                           ///< Pointer to \ref ARM_SPI_Send : Start sending data to SPI Interface.

#endif
