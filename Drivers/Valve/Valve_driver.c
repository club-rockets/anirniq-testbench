#include "Valve_driver.h"

void valve_initial(void){

RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN; //Enable GPIO clock

VALVE_GPIO->MODER |= GPIO_MODER_MODER1_0 | GPIO_MODER_MODER2_0; //Set up GPIO
VALVE_GPIO->PUPDR |= GPIO_PUPDR_PUPDR1_0 | GPIO_PUPDR_PUPDR2_0; //GPIO pull up

VALVE_GPIO->ODR &= GPIO_ODR_ODR_1 | GPIO_ODR_ODR_2; //Set GPIO to 0

}

void valve_open(uint8_t pin){

    VALVE_GPIO->ODR |= (1<<pin);

}

void valve_close(uint8_t pin){

    VALVE_GPIO->ODR &= ~(1<<pin);

}

uint8_t valve_getstatus(uint8_t pin){

    uint32_t data;

    data = (VALVE_GPIO->ODR & (1<<pin)>>pin);

    return data;
}