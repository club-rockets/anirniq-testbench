#ifndef SPI2_DRIVER_H_
#define SPI2_DRIVER_H_

#include <stdio.h>
#include "stm32f4xx.h"

#define SPI2_GPIO GPIOB
#define SD_SPI SPI2

#define USE_DEFAULT_CRITICAL_CALLBACK

//Alternate function configuration
#define SPI2_CLK (0b0101<<(5*4))
#define SPI2_MISO (0b0101<<(6*4))
#define SPI2_MOSI (0b0101<<(7*4))

/* PROTOTYPE */

void spi2_initial(void);
void spi2_dma_init(void);
void spi2_send(uint8_t data);

//From MAXIM INT
uint8_t SPI2_Write(uint8_t *buffer, uint8_t nBytes);
uint8_t SPI2_Read(uint8_t *buffer, uint8_t nBytes);
uint8_t SPI2_WriteByte(uint8_t data);
uint8_t SPI2_ReadByte(void);
void Set_DRDY_Pin_INPUT(void);
uint8_t DRDY_Pin_Value(void);
void Enable_Exti(void);    //enable external interrupt

uint16_t SPI_I2S_ReceiveData(SPI_TypeDef* SPIx);

void EnterCriticalSection_UserCallback(void);
void ExitCriticalSection_UserCallback(void);

#endif
