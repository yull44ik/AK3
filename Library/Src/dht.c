#include "DHT.h"

uint8_t Rh_byte1, Rh_byte2, Temp_byte1, Temp_byte2;
uint16_t SUM; uint8_t Presence = 0;

void port_init(){

	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	GPIOA->MODER |= GPIO_MODER_MODER1_0;
	GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR1_1;

}

void set_pin_input(){
	GPIOA->MODER &= ~GPIO_MODER_MODER1_0;
}

void set_pin_output(){
	GPIOA->MODER |= GPIO_MODER_MODER1_0;
	GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR1_0;
}

uint32_t gpio_read_pin(){
  uint32_t bitstatus = 0;
  if((GPIOA->IDR & GPIO_PIN_1) != (uint32_t)GPIO_PIN_RESET)
  {
    bitstatus = 1;
  }
  else
  {
    bitstatus = 0;
  }
  return bitstatus;
}

void delay_init(){

	  RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
	  TIM4->PSC = SystemCoreClock / 1000000 - 1;
	  TIM4->ARR = 0xFFFFFFFF;

	  TIM4->CR1 |= TIM_CR1_ARPE;
	  TIM4->EGR |= TIM_EGR_UG;

	  TIM4->CR1 |= TIM_CR1_CEN;
}
__STATIC_INLINE void delay(volatile uint32_t microseconds){

	uint32_t clk_cycle_start = TIM4->CNT;
	while ((TIM4->CNT - clk_cycle_start) < microseconds);
}

void DHT_Start (void)
{
	delay_init();

	set_pin_output();

	GPIOA->BSRR |= GPIO_BSRR_BR_1;

	delay (18000);

	GPIOA->BSRR |= GPIO_BSRR_BS_1;
    delay (20);
    set_pin_input();
}

uint8_t DHT_Check_Response (void)
{
	uint8_t Response = 0;
	delay (50);
	if (!(gpio_read_pin()))
	{
		delay (25);
		if ((gpio_read_pin())) Response = 1;
		else Response = -1;
	}
	while ((gpio_read_pin()));   // wait for the pin to go low

	return Response;
}

uint8_t DHT_Read (void)
{
	uint8_t i,j;

	for (j=0;j<8;j++)
	{
		while (!(gpio_read_pin()));
		delay (40);
		if (!(gpio_read_pin()))
		{
			i&= ~(1<<(7-j));
		}
		else i|= (1<<(7-j));
		while ((gpio_read_pin()));

	}
	return i;
}



void DHT_GetData (DHT_DataTypedef *DHT_Data)
{
    DHT_Start ();
	Presence = DHT_Check_Response ();
	Rh_byte1 = DHT_Read ();
	Rh_byte2 = DHT_Read ();
	Temp_byte1 = DHT_Read ();
	Temp_byte2 = DHT_Read ();
	SUM = DHT_Read();

	if (SUM == (Rh_byte1+Rh_byte2+Temp_byte1+Temp_byte2))
	{
		DHT_Data->Temperature = Temp_byte1 + 0.1 * Temp_byte2;
		DHT_Data->Humidity = Rh_byte1;

	}
}


