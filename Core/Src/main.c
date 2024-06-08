#include "main.h"


void SystemClock_Config(void);

DHT_DataTypedef DHT11_Data;
float Temperature, Humidity;
uint32_t flag =0;
char trans_temp[5];
char trans_hum[5];


int main(void)
{

  HAL_Init();

  i2c_port_init();
  port_init();

  SystemClock_Config();

  while (1)
  {
	  DHT_GetData(&DHT11_Data);
	  Temperature = DHT11_Data.Temperature;
	  Humidity = DHT11_Data.Humidity;
	  void Display_Temp (float Temp)
	  {

	  	char str[20] = {0};
	  	lcd_put_cur(0, 0);

	  	sprintf (str, "Temp: %.2f ", Temp);


	  	lcd_send_string(str);
	  	lcd_send_data('C');
	  }

	  void Display_Rh (float Rh)
	  {
	  	char str[20] = {0};
	  	lcd_put_cur(1, 0);


	  	sprintf (str, "RH: %.2f ", Rh);

	  	lcd_send_string(str);
	  	lcd_send_data('%');
	  }


	  float_to_char(Temperature, trans_temp);
	  float_to_char(Humidity, trans_hum);
	  uart_transmit(trans_temp, 5);
	  uart(',');
	  uart_transmit(trans_hum, 5);

	  uart('\n');
  }
}


void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};


  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);


  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 72;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }


  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}


void Error_Handler(void)
{

  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
