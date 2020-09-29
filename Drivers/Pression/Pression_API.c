#include "Pression_API.h"

void p_API_init(API_PRESSURE_STRUCT *t_data, uint16_t *data, uint8_t nb){

	uint8_t i;

	for(i = 0;i<nb;i++){

		t_data->data = (uint32_t) &data[i];

	}

}

void p_init(API_PRESSURE_STRUCT *t_struct, char* name){

	strcpy(t_struct->name,name); //init Pressure name
	adc_init();

}

void p_start(API_PRESSURE_STRUCT *t_struct, uint16_t *data){

	adc_power(1);
	init_adc_dma((uint32_t) &data[0]);
	adc_multi_conversion();

}

void p_stop(void){

	adc_power(0);

}
