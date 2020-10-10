#include "thermo_API.h"

void t_API_init(API_THERMO_STRUCT* t_data, uint8_t nb){

	spi_initial();

}



void t_init(API_THERMO_STRUCT *t_struct, char* name){

		strcpy(t_struct->name,name); //init Thermo name
		NSS_PIN = t_struct->pin; //Pass thermo pin
		maxim_31856_init(); //init the driver

}

//One_Shot_Conversion or Automatic_Conversion
void t_start(API_THERMO_STRUCT *t_struct, uint8_t conversion_mode){

	NSS_PIN = t_struct->pin;
	maxim_start_conversion(conversion_mode);

}

void t_stop(API_THERMO_STRUCT *t_struct){

	NSS_PIN = t_struct->pin;
	maxim_stop_conversion();

}

//Must be 16 row
void t_get(API_THERMO_STRUCT *t_struct){

	NSS_PIN = t_struct->pin;
	maxim_31856_read_nregisters(0x00,t_struct->data,16);

}

void t_junction_temp(const uint8_t * rxBuffer, long * data, double * temperature){

	long temperatureOffset = 0;

	*data = (rxBuffer[0] << 16 | rxBuffer[1] << 8 | rxBuffer[2]); //Concatenation des valeurs des 4 registres

	if (*data == 0xFFFFFFFF){
		//return -1;
	}else{
		temperatureOffset = (*data & 0xFF0000) >> 16;
	}

	//Gerer la cas du negatif A faire
    *data = *data >> 2;
    *temperature = (double) *data + temperatureOffset; //Ajout de la temperature offset
    *temperature *= 0.015625; //Comme un shift vers dizaines

}

void t_temp(const uint8_t * rxBuffer, long * data, double * temperature){
    
    *data = (rxBuffer[0] << 24 | rxBuffer[1] << 16 | rxBuffer[2] << 8 | rxBuffer[3]); //Concatenation des valeurs des 4 registres

	if(*data == 0xFFFFFFFF){
		//return -1; //pas de communication de la chip slave

	}else{
		*data = *data >> 13;
		//Celsius
		*temperature = (double) *data * API_DRIVER_CONST;
	}
    
}
