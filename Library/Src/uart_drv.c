#include "uart_drv.h"

void uart_init(void){
	  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	  RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

	  GPIOA->MODER |= GPIO_MODER_MODE2_1;
	  GPIOA->MODER |= GPIO_MODER_MODE3_1;

	  GPIOA->AFR[0] |= GPIO_AF7_USART1 << 8;
	  GPIOA->AFR[0] |= GPIO_AF7_USART1 << 12;

	  USART2->CR1 &= ~USART_CR1_M;
	  USART2->CR2 &= ~USART_CR2_STOP;

	  USART2->BRR = (6<<0) | (234<<4);

	  USART2->CR1 |= USART_CR1_TE;
	  USART2->CR1 |= USART_CR1_RE;

	  USART2->CR1 |= USART_CR1_UE;
}

void uart_transmit(char *data, int length){
	for (int i = 0; i < length; i++) {
	    while (!(USART2->SR & USART_SR_TXE));
	    USART2->DR = data[i];
	    while (!(USART2->SR & USART_SR_TC));
	}
}

void float_to_char(float num, char str[]){
	int new_int = (int)num;
	int x = 0;

	str[x++] = '0' + (char)(new_int / 10);
	str[x++] = '0' + (char)(new_int % 10);
	str[x++] = '.';

	float new_float = num - new_int;
	int y = 0;
	while (y < 2) {
	    new_float *= 10;
	    int rrr = (int)new_float;
	    str[x++] = '0' + (char)rrr;
	    new_float -= rrr;
	    y++;
	}
}

void uart(char data){
	while(!(USART2->SR & USART_SR_TXE));
	USART2->DR = data;
	while(!(USART2->SR & USART_SR_TC));
}


