/*
 * uart1.c
 *
 *  Created on: 30 septembre 2020
 *      Author: Nathan Roussel and Marc-Andre Denis
 */

#include "uart1.h"

static void(*volatile uart1_rxCallback)(void) = 0;

volatile struct{
	uint8_t start,end;
	uint8_t Buff[UART1_BUFFER_SIZE];
} uart1_RxBuff = {0},uart1_TxBuff = {0};

void uart1_init() {

	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
	//enable the peripheral clock

    /*Enable GPIO clock for uart2*/
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

    GPIOA->MODER |= GPIO_MODER_MODER6_1 | GPIO_MODER_MODER7_1; //Alternate function
    GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR6 | GPIO_OSPEEDER_OSPEEDR7; //Full speed GPIO
    GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR6; //No pull up nor pull down
    GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR7; //No pull up nor pull down
    GPIOA->AFR[0] |= (0x7<<24) | (0x7<<28); //Init alternate function

	//enable the peripheral
	USART1->CR1 |= USART_CR1_UE;

	//set baud rate settings 460800
	//settings for 42mhz APB1 clock

	//USART2->BRR = 11<<4 | 0x6;
	USART1->BRR = 5<<4 | 0x7;
	//USART1->BRR = 4375; //9600 baud for 42mhz clock

	//enable receiver mode
	USART1->CR1 |= USART_CR1_RE;
	//ENABLE TRANSMIT MODE
	USART1->CR1 |= USART_CR1_TE;

	//enable rxne interrupts
	USART1->CR1 |= USART_CR1_RXNEIE;

	//enable USART2 in nvic
	NVIC_SetPriority(USART1_IRQn, 3);
	NVIC_EnableIRQ(USART1_IRQn);
}


//return positive is transfer possible without buffer overrun
uint32_t uart1_transmit(uint8_t*buff,uint8_t size){
	//check for space
	if(uart1_TxBuff.end<uart1_TxBuff.start){
		if(uart1_TxBuff.start-uart1_TxBuff.end -1 < size) return 0;
	}
	else if (uart1_TxBuff.end>uart1_TxBuff.start){
		if(UART1_BUFFER_SIZE -1 -uart1_TxBuff.end + uart1_TxBuff.start < size) return 0;
	}

	//copy the data in the buffer
	uint8_t i;
	for(i=0;i<size;i++){
		uart1_TxBuff.end++;
		uart1_TxBuff.end%=UART1_BUFFER_SIZE;
		uart1_TxBuff.Buff[uart1_TxBuff.end] = buff[i];
	}
	//enable transmit interrupt
	USART2->CR1 |= USART_CR1_TXEIE;
	return 1;
}

uint8_t uart1_rxBuffAvailable(){
	return !(uart1_RxBuff.end == uart1_RxBuff.start);
}

uint8_t uart1_get(){
	uart1_RxBuff.start++;
	uart1_RxBuff.start%=UART1_BUFFER_SIZE;
	return uart1_RxBuff.Buff[uart1_RxBuff.start];
}

void uart1_registerRxCallback(void (*callback)(void)){
	uart1_rxCallback = callback;
}

void USART1_IRQHandler(void){
	if(USART2->SR & USART_SR_TXE){
		//if tx buffer not empty
		if(uart1_TxBuff.end-uart1_TxBuff.start){
			uart1_TxBuff.start++;
			uart1_TxBuff.start%=UART1_BUFFER_SIZE;
			USART2->DR = uart1_TxBuff.Buff[uart1_TxBuff.start];
		}
		else USART2->CR1 &=~USART_CR1_TXEIE;
	}
	if(USART2->SR & USART_SR_RXNE){
		uart1_RxBuff.end++;
		uart1_RxBuff.end%=UART1_BUFFER_SIZE;
		uart1_RxBuff.Buff[uart1_RxBuff.end] = USART2->DR;
		if(uart1_rxCallback){
			uart1_rxCallback();
		}
	}
}