#ifndef SPI_DRIVER_H_
#define SPI_DRIVER_H_

#include <stdio.h>
#include "stm32f4xx.h"

#define SPI1_GPIO GPIOA
#define T_SPI SPI1

//From MAXIM INT
#define SPI_CS_HIGH 0
#define SPI_CS_LOW 0         
   
#define USE_DEFAULT_CRITICAL_CALLBACK 

//Alternate function configuration
#define SPI1_CLK (0b0101<<(5*4))
#define SPI1_MISO (0b0101<<(6*4))
#define SPI1_MOSI (0b0101<<(7*4))

/* PROTOTYPE */

void spi_initial(void);
void spi_dma_init(void);
void spi_send(uint8_t data);

//From MAXIM INT
uint8_t SPI_Write(uint8_t *buffer, uint8_t nBytes);
uint8_t SPI_Read(uint8_t *buffer, uint8_t nBytes);  
uint8_t SPI_WriteByte(uint8_t data);
uint8_t SPI_ReadByte(void);
void Set_DRDY_Pin_INPUT(void);
uint8_t DRDY_Pin_Value(void);
void Enable_Exti(void);    //enable external interrupt
    
void EnterCriticalSection_UserCallback(void);
void ExitCriticalSection_UserCallback(void);   

#endif
