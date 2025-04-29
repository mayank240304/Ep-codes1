/* Includes ------------------------------------------------------------------*/
#include "main.h"

void uart3Config()
{
	// 1. Enable the UART CLOCK and GPIO CLOCK
		RCC->APB1ENR |= (1<<18);  // Enable UART2 CLOCK
		RCC->AHB1ENR |= (1<<2); // Enable GPIOC CLOCK

		// 2. Configure the UART PINs for ALternate Functions
		GPIOC->MODER |= (2<<20);  // Bits (21:20)= 1:0 --> Alternate Function for Pin PC10
		GPIOC->MODER |= (2<<22);  // Bits (23:22)= 1:0 --> Alternate Function for Pin PC11

		GPIOC->OSPEEDR |= (3<<20) | (3<<22);  // Bits (23:22)= 1:1 and Bits (21:20)= 1:1 --> High Speed for PIN PC11 and PC10

		GPIOC->AFR[1] |= (7<<8);  // Bytes (11:10:9:8) = 0:1:1:1  --> AF7 Alternate function for USART2 at Pin PC10
		GPIOC->AFR[1] |= (7<<12); // Bytes (15:14:13:12) = 0:1:1:1  --> AF7 Alternate function for USART2 at Pin PC11

		// 3. Enable the USART by writing the UE bit in USART_CR1 register to 1.
		USART3->CR1 = 0x00;  // clear all
		USART3->CR1 |= (1<<13);  // UE = 1... Enable USART

		// 4. Program the M bit in USART_CR1 to define the word length.
		USART3->CR1 &= ~(1<<12);  // M =0; 8 bit word length

		// 5. Select the desired baud rate using the USART_BRR register.
		USART3->BRR = (3<<0) | (104<<4);   // Baud rate of 9600, PCLK1 at 16MHz

		// 6. Enable the Transmitter/Receiver by Setting the TE and RE bits in USART_CR1 Register
		USART3->CR1 |= (1<<2); // RE=1.. Enable the Receiver
		USART3->CR1 |= (1<<3);  // TE=1.. Enable Transmitter
	}

void uartsendChar(unsigned char dat)
{
	USART3->DR = dat; // load the data into DR register
		while (!(USART3->SR & (1<<6)));  // Wait for TC to SET.. This indicates that the data has been transmitted
}

void uartsendString(char* string)
{
	while (*string) uartsendChar(*string++);
}

unsigned char uartgetChar()
{
	unsigned char ret;

		while (!(USART3->SR & (1<<5)));  // wait for RXNE bit to set
		ret = USART3->DR;  // Read the data. This clears the RXNE also
		return ret;
}

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
unsigned char retdata;
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();
  /* Configure the system clock */
  SystemClock_Config();
  uart3Config();
  /* USER CODE BEGIN WHILE */
  uartsendString("Type a key on PC Keyboard\r\n");
  HAL_Delay(1000);
  while (1)
  {

	  retdata = uartgetChar();
       retdata+= 1;
	  uartsendChar(retdata);
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
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

