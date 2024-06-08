
#ifndef DHT_H_
#define DHT_H_

#include "stdint.h"
#include <stm32f4xx.h>
void port_init();
void set_pin_input();
void set_pin_output();
uint32_t gpio_read_pin();

typedef struct
{
	float Temperature;
	float Humidity;
}DHT_DataTypedef;


void DHT_GetData (DHT_DataTypedef *DHT_Data);



#endif /* DHT_H_ */
