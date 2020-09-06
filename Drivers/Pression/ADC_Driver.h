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

/* GPIO DEFINE */

#define P1_GPIO_PORT GPIOA
#define P2_GPIO_PORT GPIOA
#define P3_GPIO_PORT GPIOA

#define P1_GPIO_CLK 0
#define P2_GPIO_CLK 0
#define P3_GPIO_CLK 0

#define P1_GPIO_ANALOG 0
#define P2_GPIO_ANALOG 0
#define P3_GPIO_ANALOG 0

/* ADC DEFINE */

#define P_ADC ADC1

#define P1_ADC_CLK 0
#define P2_ADC_CLK 0
#define P3_ADC_CLK 0

#define P1_EOC_MASK 1
#define P2_EOC_MASK 1
#define P3_EOC_MASK 1

#define MULTI_CHANNEL 0
#define SINGLE_SCAN 0
#define RESOLUTION (0x0 << 24)
#define P1_SAMPLE (0x0 << 0)
#define P2_SAMPLE (0x0 << 0)
#define P3_SAMPLE (0x0 << 0)

//Prototype
void adc_init(void);
void adc_conversion(uint32_t *adcDR);
float adc_pressureConvert(uint32_t adcval);

#endif /* PRESSION_ADC_DRIVER_H_ */
