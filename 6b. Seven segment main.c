#include "main.h"

void SSInit()
{
//enable the clock to the GPIOA,GPIOB,GPIOE and GPIOC
	RCC->AHB1ENR |= (1<<0)|(1<<1)|(1<<2)|(1<<4); //ENABLE GPIOA,GPIOB,GPIOC,GPIOE

//make pins mode as GPIO OUTPUT (set bits as 0:1 i.e.2)
	GPIOA->MODER |= (1<<8)|(1<<12);//PA4 ,PA6 as GPIO
	GPIOB->MODER |= (1<<12)|(1<<14);//PB6,PB7
	GPIOC->MODER |= (1<<12)|(1<<14);//PC6 and PC7 as GPIO
	GPIOE->MODER |= (1<<0)|(1<<2)|(1<<4)|(1<<8)|(1<<10)|(1<<12);//PE0,PE1,PE2,PE4,PE5,PE6 as GPIO

//set pins speed as HIGH (1:0)
	GPIOA->OSPEEDR |= (2<<8)|(2<<12);//PA4,PA6
	GPIOB->OSPEEDR |= (2<<12)|(2<<14);//PB6,PB7
	GPIOC->OSPEEDR |= (2<<12)|(2<<14);//PC6 and PC7
	GPIOE->OSPEEDR |= (2<<0)|(2<<2)|(2<<4)|(2<<8)|(2<<10)|(2<<12);//PE0,PE1,PE2,PE4,PE5,PE6

//set initial values as HIGH (common cathode)
	GPIOA->ODR &= 0x00;//PA4,PA6
	GPIOB->ODR &=0x00;//PB6,PB7
	GPIOC->ODR |= 0xFF;//PC6 and PC7
	GPIOE->ODR |= 0xFF;//PE0,PE1,PE2,PE4,PE5,PE6
}

void SSDisplay(unsigned char val)
{
	//A
		if(val & 0x01)
			GPIOC->ODR |= (1<<6);
		else
			GPIOC->ODR &= ~(1<<6);

		//B
		if(val & 0x02)
			GPIOC->ODR |= (1<<7);
		else
			GPIOC->ODR &= ~(1<<7);

		//C
		if(val & 0x04)
			GPIOE->ODR |= (1<<0);
		else
			GPIOE->ODR &= ~(1<<0);

		//D
		if(val & 0x08)
			GPIOE->ODR |= (1<<1);
		else
			GPIOE->ODR &= ~(1<<1);

		//E
		if(val & 0x10)
			GPIOE->ODR |= (1<<2);
		else
			GPIOE->ODR &= ~(1<<2);

		//F
		if(val & 0x20)
			GPIOE->ODR |= (1<<4);
		else
			GPIOE->ODR &= ~(1<<4);

		//G
		if(val & 0x40)
			GPIOE->ODR |= (1<<5);
		else
			GPIOE->ODR &= ~(1<<5);

		//DP
		if(val & 0x80)
			GPIOE->ODR |= (1<<6);
		else
			GPIOE->ODR &= ~(1<<6);
}

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/*
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
unsigned char ssCode[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
unsigned int i;

/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();
  /* Configure the system clock */
  SystemClock_Config();
  SSInit();
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    GPIOA->ODR |= (1<<4); //enable segment 1

	  for(i=0;i<10;i++)
	  {
		  SSDisplay(ssCode[i]);
		  HAL_Delay(1000);
	  }
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
void assert_failed(uint8_t *file, uint32_t line)
{
    /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

