/*
 * thermocouple.h
 *
 *  Created on: 14 nov. 2019
 *      Author: Rouss & Duv
 */

#ifndef THERMO_API_H_
#define THERMO_API_H_

#include "SPI_driver.h"

// MAX31856 Registers
// Register 0x00: CR0
#define CR0_AUTOMATIC_CONVERSION                0x80
#define CR0_ONE_SHOT                            0x40
#define CR0_OPEN_CIRCUIT_FAULT_TYPE_K           0x10    // Type-K is 10 to 20 Ohms
#define CR0_COLD_JUNCTION_DISABLED              0x08
#define CR0_FAULT_INTERRUPT_MODE                0x04
#define CR0_FAULT_CLEAR                         0x02
#define CR0_NOISE_FILTER_50HZ                   0x01
// Register 0x01: CR1
#define CR1_AVERAGE_1_SAMPLE                    0x00
#define CR1_AVERAGE_2_SAMPLES                   0x10
#define CR1_AVERAGE_4_SAMPLES                   0x20
#define CR1_AVERAGE_8_SAMPLES                   0x30
#define CR1_AVERAGE_16_SAMPLES                  0x40
#define CR1_THERMOCOUPLE_TYPE_B                 0x00
#define CR1_THERMOCOUPLE_TYPE_E                 0x01
#define CR1_THERMOCOUPLE_TYPE_J                 0x02
#define CR1_THERMOCOUPLE_TYPE_K                 0x03
#define CR1_THERMOCOUPLE_TYPE_N                 0x04
#define CR1_THERMOCOUPLE_TYPE_R                 0x05
#define CR1_THERMOCOUPLE_TYPE_S                 0x06
#define CR1_THERMOCOUPLE_TYPE_T                 0x07
#define CR1_VOLTAGE_MODE_GAIN_8                 0x08
#define CR1_VOLTAGE_MODE_GAIN_32                0x0C
// Register 0x02: MASK
#define MASK_COLD_JUNCTION_HIGH_FAULT           0x20
#define MASK_COLD_JUNCTION_LOW_FAULT            0x10
#define MASK_THERMOCOUPLE_HIGH_FAULT            0x08
#define MASK_THERMOCOUPLE_LOW_FAULT             0x04
#define MASK_VOLTAGE_UNDER_OVER_FAULT           0x02
#define MASK_THERMOCOUPLE_OPEN_FAULT            0x01
// Register 0x0F: SR
#define SR_FAULT_COLD_JUNCTION_OUT_OF_RANGE     0x80
#define SR_FAULT_THERMOCOUPLE_OUT_OF_RANGE      0x40
#define SR_FAULT_COLD_JUNCTION_HIGH             0x20
#define SR_FAULT_COLD_JUNCTION_LOW              0x10
#define SR_FAULT_THERMOCOUPLE_HIGH              0x08
#define SR_FAULT_THERMOCOUPLE_LOW               0x04
#define SR_FAULT_UNDER_OVER_VOLTAGE             0x02
#define SR_FAULT_OPEN                           0x01

#define NB_THERMO 5

//Prototype
void init(void);
void start(void);
void stop(void);
void junction_temp(const uint8_t * rxBuffer, long * data, double * temperature);
void temp(const uint8_t * rxBuffer, long * data, double * temperature);

#endif