/*
 * ADC_Driver.c
 *
 *  Created on: Sep 2, 2020
 *      Author: nathan
 */

#include "ADC_Driver.h"

void adc_init(void){

	/* ************ NOT CODE ************
	 * PRESSURE 1 (P1) = ADC CHANNEL 1, pin A5, GPIO A, pin number 30
	 * PRESSURE 2 (P2) = ADC CHANNEL 1, pin A6, GPIO A, pin number 31
	 * PRESSURE 3 (P3) = ADC CHANNEL 1, pin A7, GPIO A, pin number 32
	 * See ADC_Driver.h for correct define value */

	RCC->APB2ENR |= ADC1_EN; //Enable ADC clock
	RCC->AHB1ENR |= P1_GPIO_CLK | P2_GPIO_CLK | P3_GPIO_CLK; //Enable GPIO clock

	P1_GPIO_PORT->MODER |= P1_GPIO_ANALOG | P2_GPIO_ANALOG | P3_GPIO_ANALOG; //Configure GPIO to analog input
	P1_GPIO_PORT->PUPDR |= P1_GPIO_NO_PULL | P2_GPIO_NO_PULL | P3_GPIO_NO_PULL; //No pull mode

	RCC->CFGR |= ADC_DIV_2_PRESCALER; //Prescaler division by 2

	P_ADC->CR1 |= RESOLUTION; // Set the resolution of the ADC to 12 bits

	P_ADC->SMPR2 |= P1_SAMPLE | P2_SAMPLE | P3_SAMPLE; // Set the sample time to 3 cycles

}

void adc_multi_conversion(uint32_t *adcDR){


	/* ADC CONFIGURATION */

	/* LECTURE */

	/*while((P_ADC->CSR & P1_EOC_MASK) == 0);

	adcDR[0] = P_ADC->DR;

	while((P_ADC->CSR & P2_EOC_MASK) == 0);

	adcDR[1] = P_ADC->DR;

	while((P_ADC->CSR & P2_EOC_MASK) == 0);

	adcDR[2] = P_ADC->DR;*/

}

void adc_single_conversion(uint32_t *data){


	P_ADC->SQR1 |= SINGLE_CONVERSION; //Select the conversion mode

	P_ADC->SQR3 |= (P1_CHANNEL << 0); //Select the channel

	P_ADC->CR2 |= START_CONVERSION; //Start the conversion

	while((P_ADC->SR & ADC_EOC_MASK) == 0);

	*data = P_ADC->DR;

}

void adc_calibration(void){}

void adc_power(uint32_t val){

	if(val){

		P_ADC->CR2 |= ADC_POWER_UP; //Power up ADC

	}else if(!val){

		P_ADC->CR2 &= ~ADC_POWER_UP; //Power down ADC

	}

}

float adc_pressureConvert(uint32_t adcval){

    float temp = (float)adcval;
    temp -=745.0;
    temp /=5.956;
    return temp;

}
