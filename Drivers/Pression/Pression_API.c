#include "Pression_API.h"

void p_API_init(void){

	adc_init();

}

void p_init(API_PRESSURE_STRUCT *t_struct, uint8_t id, uint16_t *adr){

	t_struct->id = id;
	t_struct->data = adr;

}

void p_start(uint16_t *data){

	adc_power(1);
	init_adc_dma((uint32_t) &data[0]);
	adc_multi_conversion();

}

void p_send(API_PRESSURE_STRUCT *t_struct, uint8_t port, uint8_t format){


	if(!format){

		char strdata[8];
		char strid[8];
		sprintf(strdata,"%d",*t_struct->data);
		sprintf(strid,"%d",t_struct->id);

		if(!port){

			uart2_transmit("#SENSOR_ID:",13);
			uart2_transmit(strid,strlen(strid));
			uart2_transmit("#DATA:",6);
			uart2_transmit(strdata,strlen(strdata));

		}else{

			uart1_transmit("#SENSOR_ID:",13);
			uart1_transmit(strid,strlen(strid));
			uart1_transmit("#DATA:",6);
			uart1_transmit(strdata,strlen(strdata));

		}

	}else{}
}

void p_stop(void){

	adc_power(0);

}

uint8_t p_push(API_PRESSURE_STRUCT *t_struct, DataBuffer *buffer){

	DataBuffer_Element newData;

	newData.node = XML_NODE;
	newData.id = t_struct->id;

	newData.data.adr = t_struct->data;
	newData.data.nb = 1;
	newData.data.type = sizeof(*(t_struct->data));

	return put(buffer, newData);

}
