#include "SPI2_driver.h"

/* SPI2 PINOUT
 * SCK = PB13
 * MISO = PB14
 * MOSI = PB15
 * nCS = PB12
 */


void spi2_initial(uint8_t baud){

    RCC->APB1ENR |= RCC_APB1ENR_SPI2EN; //Enable SPI clock
    
    /*Enable GPIO clock for spi 1*/
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

    //Set up GPIO
    SPI2_GPIO->MODER |= GPIO_MODER_MODER15_1 | GPIO_MODER_MODER14_1 | GPIO_MODER_MODER13_1 | GPIO_MODER_MODER12_0; //Alternate function and GPIO

    SPI2_GPIO->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR15 | GPIO_OSPEEDER_OSPEEDR14 | GPIO_OSPEEDER_OSPEEDR13; //Full speed GPIO

    SPI2_GPIO->PUPDR |= GPIO_PUPDR_PUPDR13_0 | GPIO_PUPDR_PUPDR12_0; //GPIO pull up

  //  SPI1_GPIO->PUPDR |= GPIO_PUPDR_PUPDR6_0; //pull down

    /* SPI CONFIGURATION */
    SPI2_GPIO->AFR[1] |= SPI2_CLK | SPI2_MISO | SPI2_MOSI; //Set GPIO to MOSI MISO and SCK

    SD_SPI->CR1 &= ~SPI_CR1_BIDIMODE; //Enable bidirectionnal mode
    SD_SPI->CR1 &= ~SPI_CR1_RXONLY; //Full duplex
    SD_SPI->CR1 &= ~SPI_CR1_CRCEN; //CRC disable
    SD_SPI->CR1 &= ~SPI_CR1_DFF; //Select 8-bit dataframe
    SD_SPI->CR1 |= SPI_CR1_SSI; //Select software NSS
    SD_SPI->CR1 |= SPI_CR1_SSM; //Select software NSS
    SD_SPI->CR1 &= ~SPI_CR1_LSBFIRST; //Select MSB first
    SD_SPI->CR1 |= (baud<<3); //Baud rate /16

    SD_SPI->CR1 &= ~SPI_CR1_CPOL; //CPOL high and CPHA on second edge
    SD_SPI->CR1 &= ~SPI_CR1_CPHA;

    SD_SPI->CR2 &= ~SPI_CR2_SSOE; //SS output enable

    SD_SPI->CR1 |= SPI_CR1_MSTR; //Master configuration
    SD_SPI->CR1 |= SPI_CR1_SPE; //Enable the spi

    SPI2_GPIO->ODR |= (1<<12); //Reset all the NSS pins

}

void spi2_dma_init(void){}

uint8_t SPI2_WriteByte(uint8_t data){

	while((SD_SPI->SR & SPI_SR_TXE) != SPI_SR_TXE); //Check if TX buffer empty
	SD_SPI->DR = (uint16_t)data; //Send data to TX buffer
	while((SD_SPI->SR & SPI_SR_RXNE) != SPI_SR_RXNE);//Check if RX buffer is full
	data = (uint8_t)SD_SPI->DR;

	return 0;

}

uint8_t SPI2_ReadByte(void){

	while((SD_SPI->SR & SPI_SR_TXE) != SPI_SR_TXE); //Check if TX buffer empty
	SD_SPI->DR = 0xff; //Send data to TX buffer (dummy value)
	while((SD_SPI->SR & SPI_SR_RXNE) != SPI_SR_RXNE);//Check if RX buffer is full

	return (uint8_t)SD_SPI->DR;

}

uint8_t SPI2_Write(uint8_t *buffer, uint8_t nBytes){

	uint8_t i;
	for(i=0;i<nBytes;i++){

		while((SD_SPI->SR & SPI_SR_TXE) != SPI_SR_TXE); //Check if TX buffer empty
		SD_SPI->DR = (uint16_t)buffer[i];
		while((SD_SPI->SR & SPI_SR_RXNE) != SPI_SR_RXNE);//Check if RX buffer is full
		buffer[i] = (uint8_t)SD_SPI->DR;

	}

	return 0;
}

uint8_t SPI2_Read(uint8_t *buffer, uint8_t nBytes){

	uint8_t i;

	  for(i=0;i<nBytes;i++){

		  while((SD_SPI->SR & SPI_SR_TXE) != SPI_SR_TXE); //Check if TX buffer empty
		  SD_SPI->DR = (uint16_t)0x00; //Send data to TX buffer (dummt write)
		  while((SD_SPI->SR & SPI_SR_RXNE) != SPI_SR_RXNE);//Check if RX buffer is full
		  buffer[i] = (uint8_t)SD_SPI->DR;

	  }

	  return 0;
}
