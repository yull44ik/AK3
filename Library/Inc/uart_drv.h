#ifndef INC_UART_DRV_H_
#define INC_UART_DRV_H_

#include "stm32f4xx_hal.h"
#include "stm32f407xx.h"

void uart_init(void);
void uart_transmit(char *data, int length);
void float_to_char(float num, char str[]);
void uart(char data);

#endif /* INC_UART_DRV_H_ */
