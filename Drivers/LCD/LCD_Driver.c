#include "lcd.h"

void lcd_init(lcd_struct_t* lcd){

	lcd->lastOp = lcd_lastOpread;
	
	//Check interface 4 bit or 8 bit mode
	if(lcd->interfaceSize == lcd_size4){
		
		lcd->interfaceSize = lcd_size8;
		// setup sequence for 4 bit bus
		lcd_write(lcd,lcd_command,0b00110000);
		lcd_delay_ns(1);
		lcd_write(lcd,lcd_command,0b00110000);
		lcd_delay_ns(1);
		lcd_write(lcd,lcd_command,0b00110000);
		lcd_delay_ns(1);
		lcd_write(lcd,lcd_command,0b00100000);
		lcd_delay_ns(1);

		lcd->interfaceSize = lcd_size4;
		lcd_write(lcd,lcd_command,0b00101000);
		lcd_delay_ns(1);
		//display on and cursor and blinking cursor
		lcd_write(lcd,lcd_command,0b00001111);
		lcd_delay_ns(1);

		lcd_write(lcd,lcd_command,0b00000110);
		lcd_delay_ns(1);
		lcd_write(lcd,lcd_command,0b00000001);
		lcd_delay_ns(1);
		
	} else {
		
		lcd->interfaceSize = lcd_size8;
		// setup sequence for 8 bit bus
		lcd_write(lcd,lcd_command,0b00110000);
		lcd_delay_ns(1);
		lcd_write(lcd,lcd_command,0b00110000);
		lcd_delay_ns(1);
		lcd_write(lcd,lcd_command,0b00110000);
		lcd_delay_ns(1);
		//display on and cursor and blinking cursor
		lcd_write(lcd,lcd_command,0b00001111);
		lcd_delay_ns(1);

		lcd_write(lcd,lcd_command,0b00000110);
		lcd_delay_ns(1);
		lcd_write(lcd,lcd_command,0b00000001);
		lcd_delay_ns(1);
		
	}
}

void lcd_setMode(lcd_struct_t* lcd, uint32_t onOff,uint32_t blink, uint32_t cursor){

	uint8_t cmd = 0b00001000;
	//on/off
	if(onOff){
		cmd |= 1<<2;
	}
	if(blink){
		cmd |= 1<<0;
	}
	if(cursor){
		cmd |= 1<<1;
	}
	lcd_write(lcd,lcd_command,cmd);
}

void lcd_write(lcd_struct_t* lcd,enum lcd_opType op,uint8_t data){
	
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	//Setup the bus for write
	//make all data lines output
	int i = 0;
	for(;(i<8) && (lcd->lastOp == lcd_lastOpread);i++){
		//clear bits
		if(lcd->lcd_pin[i].gpioIsConfigured == 0) continue;
		//GPIO_InitStruct.Pin = lcd->dataPins[i];
		lcd->lcd_pin[i].gpioPort.X |= lcd->lcd_pin[i].gpioPin;
		//GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		lcd->lcd_pin[i].gpioPort.X |= lcd->lcd_pin[i].gpioMode;
		//GPIO_InitStruct.Pull = GPIO_NOPULL;
		lcd->lcd_pin[i].gpioPort.X |= lcd->lcd_pin[i].gpioPull;
		//GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		lcd->lcd_pin[i].gpioPort.X |= lcd->lcd_pin[i].gpioSpeed;
	}
	
	lcd->lastOp = lcd_lastOpWrite;
	
	//clear the rw line
	
	//set the write type
	
	//Do wathever
	if(lcd->interfaceSize == lcd_size4){
		int j = 0;
		for(;j<2;j++){
			//drive the e line high
			HAL_GPIO_WritePin(lcd->ePort,lcd->ePin,1);

			//write the data
			for(i=4;i<8;i++){
				HAL_GPIO_WritePin(lcd->dataPorts[i],lcd->dataPins[i],data & (1<<i));
			}

			lcd_delay_ns(1);
			//drive the e line low
			//HAL_GPIO_WritePin(lcd->ePort,lcd->ePin,0);
			lcd.ePort.DATA = 0;
			
			lcd_delay_ns(1);
			data = data<<4;
		}

	}
	else if(lcd->interfaceSize == lcd_size8){
		//drive the e line high
		HAL_GPIO_WritePin(lcd->ePort,lcd->ePin,1);

		//write the data
		for(i=0;i<8;i++){
			if(lcd->dataPorts[i] == 0) continue;
			//HAL_GPIO_WritePin(lcd->dataPorts[i],lcd->dataPins[i],data & (1<<i));
			lcd->lcd_pin[i].gpioPort.DATA |= lcd->data & (1<<i);
		}

		lcd_delay_ns(1);
		//drive the e line low
		HAL_GPIO_WritePin(lcd->ePort,lcd->ePin,0);
		lcd_delay_ns(1);
	}
}

void lcd_setCursor(lcd_struct_t* lcd,uint8_t x,uint8_t y){
	uint8_t poss=0;
	switch(y){
		case 0 : poss = 0;	  break;
		case 1 : poss = 0x40; break;
		case 2 : poss = 0x14; break;
		case 3 : poss = 0x54; break;
	}
	poss +=x;
	lcd_write(lcd,lcd_command,0b10000000 | poss);
}

void lcd_clear(lcd_struct_t* lcd){
	lcd_write(lcd,lcd_command,0x01);
	//osDelay(50);
}

void lcd_writeString(lcd_struct_t* lcd,char* str){
	uint32_t i = 0;
	for(;str[i];i++){
		lcd_write(lcd,lcd_data,str[i]);
	}
}

void lcd_delay_ns(uint8_t n){
	
	for(int i = 0; i<n; ++i){
	
		asm ("nop");
	
	}
}

void lcd_struct_configuration(lcd_struct_t* lcd){
	
	lcd->lcd_pin[0].gpioPort = X;
	lcd->lcd_pin[1].gpioPort = X;
	lcd->lcd_pin[2].gpioPort = X;
	lcd->lcd_pin[3].gpioPort = X;
	lcd->lcd_pin[4].gpioPort = X;
	lcd->lcd_pin[5].gpioPort = X;
	lcd->lcd_pin[6].gpioPort = X;
	lcd->lcd_pin[7].gpioPort = X;
	
	lcd->lcd_pin[0].gpioPin = X;
	lcd->lcd_pin[1].gpioPin = X;
	lcd->lcd_pin[2].gpioPin = X;
	lcd->lcd_pin[3].gpioPin = X;
	lcd->lcd_pin[4].gpioPin = X;
	lcd->lcd_pin[5].gpioPin = X;
	lcd->lcd_pin[6].gpioPin = X;
	lcd->lcd_pin[7].gpioPin = X;
	
	lcd->lcd_pin[7].gpioEnable = X;
	lcd->lcd_pin[7].gpioEnable = X;
	lcd->lcd_pin[7].gpioEnable = X;
	lcd->lcd_pin[7].gpioEnable = X;
	lcd->lcd_pin[7].gpioEnable = X;
	lcd->lcd_pin[7].gpioEnable = X;
	lcd->lcd_pin[7].gpioEnable = X;
	
	for(int i=0;i<8,++i){
		
		lcd->lcd_pin[0].Mode = X;
		lcd->lcd_pin[0].Pull = X;
		lcd->lcd_pin[0].Speed = X;
		
	}
	
}