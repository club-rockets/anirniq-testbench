#ifndef _LCD_H_
#define _LCD_H_

#include "stm32f4xx_hal.h"

typedef struct {
	
	GPIO_TypeDef* gpioPort;
	uint32_t gpioPin;
	uint32_t gpioMode;
	uint32_t gpioPull;
	uint32_t gpioSpeed;
	uint32_t gpioEnable;
	uint8_t gpioIsConfigured = 0;
	
} lcd_gpio

typedef struct {

	lcd_gpio lcd_pin[8];

	enum{lcd_size4,lcd_size8} interfaceSize;
	enum{lcd_lastOpWrite,lcd_lastOpread} lastOp;

} lcd_struct_t;

enum lcd_opType{lcd_data,lcd_command};

void lcd_init(lcd_struct_t* lcd);

void lcd_setMode(lcd_struct_t* lcd, uint32_t onOff,uint32_t blink, uint32_t cursor);

void lcd_write(lcd_struct_t* lcd,enum lcd_opType op,uint8_t data);

void lcd_setCursor(lcd_struct_t* lcd,uint8_t x,uint8_t y);

void lcd_clear(lcd_struct_t* lcd);

void lcd_writeString(lcd_struct_t* lcd,char* str);

void lcd_delay_ns(uint8_t n);

void lcd_struct_configuration(lcd_struct_t* lcd);

#endif //_LCD_H_
