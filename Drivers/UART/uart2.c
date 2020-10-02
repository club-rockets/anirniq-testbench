/*
 * uart2.c
 *
 *  Created on: 30 mai 2019
 *      Author: Marc-Andre Denis
 */

#include "uart2.h"

static void(*volatile uart2_rxCallback)(void) = 0;

volatile struct{
	uint8_t start,end;
	uint8_t Buff[UART2_BUFFER_SIZE];
} uart2_RxBuff = {0},uart2_RxBuff = {0};

void uart2_init() {

	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
	//enable the peripheral clock

    /*Enable GPIO clock for uart2*/
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    UART2_GPIO->MODER |= GPIO_MODER_MODER2_1 | GPIO_MODER_MODER3_1; //Alternate function
    UART2_GPIO->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR2 | GPIO_OSPEEDER_OSPEEDR3; //Full speed GPIO
    UART2_GPIO->PUPDR &= ~GPIO_PUPDR_PUPDR2; //No pull up nor pull down
    UART2_GPIO->PUPDR &= ~GPIO_PUPDR_PUPDR3; //No pull up nor pull down
    UART2_GPIO->AFR[0] |= (0x7<<8) | (0x7<<12); //Init alternate function

	//enable the peripheral
	USART2->CR1 |= USART_CR1_UE;

	//set baud rate settings 460800
	//settings for 42mhz APB1 clock

	//USART2->BRR = 11<<4 | 0x6;
	//USART2->BRR = 5<<4 | 0x7;
	USART2->BRR = 4375; //9600 baud for 42mhz clock

	//enable receiver mode
	USART2->CR1 |= USART_CR1_RE;
	//ENABLE TRANSMIT MODE
	USART2->CR1 |= USART_CR1_TE;

	//enable rxne interrupts
	USART2->CR1 |= USART_CR1_RXNEIE;

	//enable USART2 in nvic
	NVIC_SetPriority(USART2_IRQn, 2);
	NVIC_EnableIRQ(USART2_IRQn);
}


//return positive is transfer possible without buffer overrun
uint32_t uart2_transmit(uint8_t*buff,uint8_t size){
	//check for space
	if(uart2_RxBuff.end<uart2_RxBuff.start){
		if(uart2_RxBuff.start-uart2_RxBuff.end -1 < size) return 0;
	}
	else if (uart2_RxBuff.end>uart2_RxBuff.start){
		if(UART2_BUFFER_SIZE -1 -uart2_RxBuff.end + uart2_RxBuff.start < size) return 0;
	}

	//copy the data in the buffer
	uint8_t i;
	for(i=0;i<size;i++){
		uart2_RxBuff.end++;
		uart2_RxBuff.end%=UART2_BUFFER_SIZE;
		uart2_RxBuff.Buff[uart2_RxBuff.end] = buff[i];
	}
	//enable transmit interrupt
	USART2->CR1 |= USART_CR1_TXEIE;
	return 1;
}

uint8_t uart2_rxBuffAvailable(){
	return !(uart2_RxBuff.end == uart2_RxBuff.start);
}

uint8_t uart2_get(){
	uart2_RxBuff.start++;
	uart2_RxBuff.start%=UART2_BUFFER_SIZE;
	return uart2_RxBuff.Buff[uart2_RxBuff.start];
}

void uart2_registerRxCallback(void (*callback)(void)){
	uart2_rxCallback = callback;
}

void USART2_IRQHandler(void){
	if(USART2->SR & USART_SR_TXE){
		//if tx buffer not empty
		if(uart2_RxBuff.end-uart2_RxBuff.start){
			uart2_RxBuff.start++;
			uart2_RxBuff.start%=UART2_BUFFER_SIZE;
			USART2->DR = uart2_RxBuff.Buff[uart2_RxBuff.start];
		}
		else USART2->CR1 &=~USART_CR1_TXEIE;
	}
	if(USART2->SR & USART_SR_RXNE){
		uart2_RxBuff.end++;
		uart2_RxBuff.end%=UART2_BUFFER_SIZE;
		uart2_RxBuff.Buff[uart2_RxBuff.end] = USART2->DR;
		if(uart2_rxCallback){
			uart2_rxCallback();
		}
	}
}



