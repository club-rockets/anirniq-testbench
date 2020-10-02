#include "Pression_API.h"

void p_API_init(API_PRESSURE_STRUCT *t_data, uint8_t nb){



}

void p_init(API_PRESSURE_STRUCT *t_struct, uint8_t id){

	t_struct->id = id;
	adc_init();

}

void p_start(API_PRESSURE_STRUCT *t_struct, uint16_t *data){

	adc_power(1);
	init_adc_dma((uint32_t) &data[0]);
	adc_multi_conversion();

}

void p_get(API_PRESSURE_STRUCT *t_struct, uint16_t data){

	t_struct->prsdata = data;

}

void p_send(API_PRESSURE_STRUCT *t_struct, uint8_t port){

	char strdata[8];
	char strid[8];
	sprintf(strdata,"%d",t_struct->prsdata);
	sprintf(strid,"%d",t_struct->id);

	if(!port){

		uart2_transmit("#SENSOR_NAME:",13);
		uart2_transmit(strid,strlen(strid));
		uart2_transmit("#DATA:",6);
		uart2_transmit(strdata,strlen(strdata));

	}else{

		uart1_transmit("#SENSOR_NAME:",13);
		uart1_transmit(strid,strlen(strid));
		uart1_transmit("#DATA:",6);
		uart1_transmit(strdata,strlen(strdata));

	}
}

void p_stop(void){

	adc_power(0);

}
