
#include "SPI_driver.h"

void spi_initial(void){

    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN; //Enable SPI clock
    
    /*Enable GPIO clock for spi 1*/
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    //Set up GPIO
    SPI1_GPIO->MODER |= GPIO_MODER_MODER5_1 | GPIO_MODER_MODER6_1 | GPIO_MODER_MODER7_1 | GPIO_MODER_MODER1_0 | GPIO_MODER_MODER10_0 | GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0; //Alternate function and GPIO

    SPI1_GPIO->PUPDR |= GPIO_PUPDR_PUPDR1_0 | GPIO_PUPDR_PUPDR10_0 | GPIO_PUPDR_PUPDR5_0 | GPIO_PUPDR_PUPDR8_0 | GPIO_PUPDR_PUPDR9_0; //GPIO pull up

    /* SPI CONFIGURATION */
    SPI1_GPIO->AFR[0] |= SPI1_CLK | SPI1_MISO | SPI1_MOSI; //Set GPIO to MOSI MISO and SCK

    T_SPI->CR1 &= ~SPI_CR1_BIDIMODE; //Enable bidirectionnal mode
    T_SPI->CR1 &= ~SPI_CR1_RXONLY; //Full duplex
    T_SPI->CR1 &= ~SPI_CR1_CRCEN; //CRC disable
    T_SPI->CR1 &= ~SPI_CR1_DFF; //Select 8-bit dataframe
    T_SPI->CR1 |= SPI_CR1_SSI; //Select software NSS
    T_SPI->CR1 |= SPI_CR1_SSM; //Select software NSS
    T_SPI->CR1 &= ~SPI_CR1_LSBFIRST; //Select MSB first
    T_SPI->CR1 |= (0b110<<3); //Baud rate /16

    T_SPI->CR1 |= SPI_CR1_CPHA | SPI_CR1_CPOL; //CPOL high and CPHA on second edge

    T_SPI->CR2 &= ~SPI_CR2_SSOE; //SS output enable
    T_SPI->CR2 |= SPI_CR2_RXNEIE;

    T_SPI->CR1 |= SPI_CR1_MSTR; //Master configuration
    T_SPI->CR1 |= SPI_CR1_SPE; //Enable the spi

    SPI1_GPIO->ODR |= (1<<8) | (1<<1) | (1<<9) | (1<<10); //Reset all the 4 NSS pins

}

void spi_dma_init(void){}

void spi_send(uint8_t data){


	SPI1_GPIO->ODR &= ~(1<<8);
	T_SPI->DR |= data;

}
