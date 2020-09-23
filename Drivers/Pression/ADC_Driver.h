/*
 * ADC_Driver.h
 *
 *  Created on: Sep 2, 2020
 *      Author: nathan
 */

#ifndef PRESSION_ADC_DRIVER_H_
#define PRESSION_ADC_DRIVER_H_

#include <stdio.h>
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

/* GPIO DEFINE */

#define P1_GPIO_PORT GPIOA
#define P2_GPIO_PORT GPIOA
#define P3_GPIO_PORT GPIOA

#define P1_GPIO_CLK (1<<0)
#define P2_GPIO_CLK (1<<0)
#define P3_GPIO_CLK (1<<0)

#define P1_GPIO_NO_PULL (0x0<<10)
#define P2_GPIO_NO_PULL (0x0<<12)
#define P3_GPIO_NO_PULL (0x0<<14)

#define P1_CHANNEL 5
#define P2_CHANNEL 6
#define P3_CHANNEL 7

#define P1_GPIO_ANALOG (0x3<<10)
#define P2_GPIO_ANALOG (0x3<<12)
#define P3_GPIO_ANALOG (0x3<<14)

/* ADC DEFINE */

#define P_ADC ADC1
#define ADC_DIV_2_PRESCALER (0x4<<13)

#define ADC_POWER_UP (1<<0)

#define ADC1_EN (1<<8)

#define ADC_EOC_MASK (1<<1)

#define MULTI_CHANNEL 0
#define SINGLE_CHANNEL 0
#define SINGLE_CONVERSION (0x0<<20)
#define MULTIPLE_CONVERSION (0x2<<20)
#define RESOLUTION (0x0<<24)
#define P1_SAMPLE (0x0<<15)
#define P2_SAMPLE (0x0<<18)
#define P3_SAMPLE (0x0<<21)

#define START_CONVERSION (1<<30)

//Prototype
void adc_init(void);
void adc_power(uint32_t val);
float adc_pressureConvert(uint32_t adcval);
void adc_single_conversion(uint32_t *data);
void adc_multi_conversion(void);
void adc_calibration(void);
void init_adc_dma(uint32_t data_adr);

#endif /* PRESSION_ADC_DRIVER_H_ */
