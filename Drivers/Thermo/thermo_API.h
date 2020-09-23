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

//Prototype
void junction_temp(const uint8_t * rxBuffer, long * data, double * temperature);
void temp(const uint8_t * rxBuffer, long * data, double * temperature);

#endif