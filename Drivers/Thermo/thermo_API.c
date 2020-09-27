#include "thermo_API.h"

void init(uint8_t nb){



}
void deinit(void){}
void start(void){}
void stop(void){}
void junction_temp(const uint8_t * rxBuffer, long * data, double * temperature){

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

void temp(const uint8_t * rxBuffer, long * data, double * temperature){	
    
    *data = (rxBuffer[0] << 24 | rxBuffer[1] << 16 | rxBuffer[2] << 8 | rxBuffer[3]); //Concatenation des valeurs des 4 registres

	if(*data == 0xFFFFFFFF){
		//return -1; //pas de communication de la chip slave

	}else{
		*data = *data >> 13;
		//Celsius
		*temperature = (double) *data * API_DRIVER_CONST;
	}
    
}
