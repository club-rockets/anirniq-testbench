/*
 * ADC_Driver.c
 *
 *  Created on: Sep 2, 2020
 *      Author: nathan
 */

#include "ADC_Driver.h"

void adc_init(void){

	/* PRESSURE 1 (P1) = ADC CHANNEL X, pin X, GPIO X
	 * PRESSURE 2 (P2) = ADC CHANNEL X, pin X, GPIO X
	 * PRESSURE 3 (P3) = ADC CHANNEL X, pin X, GPIO X
	 *
	 * See ADC_Driver.h for correct define value */

	RCC->APB2ENR |= P1_ADC_CLK | P2_ADC_CLK | P3_ADC_CLK; //Enable ADC clock

	RCC->AHB1ENR |= P1_GPIO_CLK | P2_GPIO_CLK | P3_GPIO_CLK; //Enable GPIO clock

	P1_GPIO_PORT->MODER |= P1_GPIO_ANALOG | P2_GPIO_ANALOG | P3_GPIO_ANALOG; //Configure GPIO to analog input

	P_ADC->CR1 |= RESOLUTION; // Set the resolution of the ADC to 12 bits

	P_ADC->SMPR1 |= P1_SAMPLE | P2_SAMPLE | P3_SAMPLE; // Set the sample time to 3 cycles

}

void adc_conversion(uint32_t *adcDR){


	/* ADC CONFIGURATION */

	/* LECTURE */

	while((ADC->CSR & P1_EOC_MASK) == 0);

	adcDR[0] = P_ADC->DR;

	while((ADC->CSR & P2_EOC_MASK) == 0);

	adcDR[1] = P_ADC->DR;

	while((ADC->CSR & P2_EOC_MASK) == 0);

	adcDR[2] = P_ADC->DR;


}

float adc_pressureConvert(uint32_t adcval){

    float temp = (float)adcval;
    temp -=745.0;
    temp /=5.956;
    return temp;

}
