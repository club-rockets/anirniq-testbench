/*
 * thermocouple.h
 *
 *  Created on: 14 nov. 2019
 *      Author: Rouss & Duv
 */

#ifndef _API_H_
#define _API_H_

#include "actuator.h"

//DEFINE HERE
#define NB_XXXXXXXX 2

//PROTOTYPE HERE
void X_init(SENSOR_STRUCT *t_struct, uint8_t id);                                                         ///< Pointer to \ref ARM_SPI_Initialize : Initialize SPI Interface.                                                       ///< Pointer to \ref ARM_SPI_Uninitialize : De-initialize SPI Interface.
void X_get(SENSOR_STRUCT *t_struct);                                                        ///< Pointer to \ref ARM_SPI_PowerControl : Control SPI Interface Power.                                                          ///< Pointer to \ref ARM_SPI_Send : Start sending data to SPI Interface.
void X_start(SENSOR_STRUCT *t_struct);
void X_stop(SENSOR_STRUCT *t_struct);

#endif
