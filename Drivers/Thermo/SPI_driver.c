
#include "SPI_driver.h"

void spi_init(void){

    RCC->APB1ENR |= RCC_APB2ENR_SPI1EN; //Enable SPI clock
    
    /*Enable GPIO clock for spi 1*/
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

    //Set up GPIO
    SPI1_GPIO->MODER |= 0;

}

void spi_send(void){}