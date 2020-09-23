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

	P_ADC->CR1 |= RESOLUTION | (1<<8); // Set the resolution of the ADC to 12 bits
	P_ADC->CR2 |= (1<<9) | (1<<8);

	P_ADC->SMPR2 |= P1_SAMPLE | P2_SAMPLE | P3_SAMPLE; // Set the sample time to 3 cycles

}

void adc_multi_conversion(void){


	/* ADC CONFIGURATION */
	P_ADC->SQR1 |= MULTIPLE_CONVERSION; //Select the conversion mode

	P_ADC->SQR3 |= (P1_CHANNEL << 0) | (P2_CHANNEL << 5) | (P3_CHANNEL << 10); //Select the channel

	P_ADC->CR2 |= START_CONVERSION; //Start the conversion

}

void init_adc_dma(uint32_t data_adr){

	RCC->AHB1ENR |= (1<<22);

	DMA2_Stream0->CR &= (0b000<<25);
	DMA2_Stream0->CR &= (0b00<<23);
	DMA2_Stream0->CR &=(0b00<<21);
	DMA2_Stream0->CR |= (0b10<<16) | (1<<13) | (1<<11) | (1<<10) | (1<<8);
	DMA2_Stream0->CR |= (0<<9);
	DMA2_Stream0->CR |= (0b00<<6);
	DMA2_Stream0->NDTR = 3;
	DMA2_Stream0->PAR = (uint32_t) &P_ADC->DR;
	DMA2_Stream0->M0AR = data_adr;
	DMA2_Stream0->FCR = 0x00000021;

	DMA2_Stream0->CR |= (1<<0);

}

void adc_single_conversion(uint32_t *data){


	P_ADC->SQR1 &= (0x0<<20); //Select the conversion mode

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
