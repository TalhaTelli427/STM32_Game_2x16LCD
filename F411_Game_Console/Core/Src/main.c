/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "liquidcrystal_i2c.h"
#include "stdlib.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;

I2C_HandleTypeDef hi2c1;

TIM_HandleTypeDef htim10;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_I2C1_Init(void);
static void MX_TIM10_Init(void);
static void MX_ADC1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int pause=0;
int test_counter=0;
int nuck_counter=0;
int dead1, dead2, dead3 = 0;
int line, state_detect = 0;
uint32_t ADC_val = 0;
int lock1, lock2, lock3 = 0;
int BDL1 = 1;
int BDL2 = 1;
int BDL3 = 1;
int trigger = 0;
int trigger_cool_down = 0;
int fireball_pos = 0;
int menu_state = 1;
int seleceter1 = 3;
int selecter3 = 1;
int selecter2 = 3;
int dedector1, dedector2, dedector3;
int hatto1, hatto2, hatto3;
int Size_Changer = 1;
int charact_count = 0;
int z = 1;
int k = 0;
int Start = 16;
int stort = 24;
int ktort = 32;
int statues_block = 1;
int point = 0;
char snum[5];
int jump_caunter = 0;
int Speed;
int Time_Counter = 0;
int safety = 0;
int val1, val2, val3;

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc) {
	if (__HAL_ADC_GET_FLAG(&hadc1,ADC_FLAG_EOC) != RESET) {

		ADC_val = HAL_ADC_GetValue(&hadc1);
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	if (htim == &htim10) {
		HAL_ADC_Start_IT(&hadc1);

		if (fireball_pos > 13) {
			fireball_pos = 0;
			trigger = 0;
			lock1 = 1;
			state_detect = 0;

		}
		if ((fireball_pos >= Start) && (trigger_cool_down == 1)
				&& (line == 1)) {
			BDL1 = 0;
			fireball_pos = 0;
			trigger = 0;
			lock1 = 1;
			state_detect = 0;
			//point-=2;
			if (fireball_pos == 0) {
				trigger_cool_down = 0;
			}

		} else if ((fireball_pos >= stort) && (trigger_cool_down == 1)
				&& (line == 0)) {
			BDL2 = 0;
			fireball_pos = 0;
			trigger = 0;
			lock2 = 1;
			state_detect = 0;
			//point-=2;

			if (fireball_pos == 0) {
				trigger_cool_down = 0;
			}}

			else if ((fireball_pos >= ktort) && (trigger_cool_down == 1)
					&& (line ==statues_block )) {
				BDL3 = 0;
				fireball_pos = 0;
				trigger = 0;
				lock3 = 1;
				state_detect = 0;
				//point-=2;

				if (fireball_pos == 0) {
					trigger_cool_down = 0;
				}

			}

			if (trigger_cool_down == 0) {
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, SET);

			} else {
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, RESET);
			}

			if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == 0) {
				test_counter++;
				if (trigger_cool_down == 0) {
					trigger = 1;
					trigger_cool_down = 1;
				}
			}
			if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_0) == 1) {

				if (menu_state == 0) {
					z = 0;
				} else if (menu_state == 1 && ADC_val < 2000) {
					Speed = 75;
					menu_state = 0;
				} else if (menu_state == 1 && ADC_val > 2000) {
					Speed = 150;
					menu_state = 0;
				}
			}
		}
	}

	void character_move(void);
	void Lower_Block_creator(void);
	void Upper_Block_creator(void);
	void Block_creator_Bonus(int pos);
	void shoot(void);
	void Nuck(void);

	void character_move(void) {
		HD44780_Clear();
		HD44780_SetCursor(0, z);
		if (charact_count == 0) {
			HD44780_PrintSpecialChar(2);
			charact_count++;
		} else if (charact_count > 0) {
			HD44780_PrintSpecialChar(3);
			charact_count = 0;
		}
	}
	void Lower_Block_creator(void) {
		if (lock1 == 0) {
			switch (seleceter1) {
			case 1:
				HD44780_SetCursor(Start, 1);
				HD44780_PrintSpecialChar(4);
				break;
			case 2:
				HD44780_SetCursor(Start, 1);
				HD44780_PrintSpecialChar(4);
				HD44780_SetCursor(Start + 1, 1);
				HD44780_PrintSpecialChar(4);

				break;

			case 3:

				HD44780_SetCursor(Start, 1);
				HD44780_PrintSpecialChar(4);
				HD44780_SetCursor(Start + 1, 1);
				HD44780_PrintSpecialChar(4);
				HD44780_SetCursor(Start + 2, 1);
				HD44780_PrintSpecialChar(4);

				break;

			default:
				HD44780_Clear();
			}
		}


		if(lock1==1&& seleceter1==3 ){
			BDL1=1;
			HD44780_SetCursor(Start, 1);
			HD44780_PrintSpecialChar(4);
		}

		if (seleceter1 == 3) {

			dedector1 = -4;
			hatto1 = 22;
		} else if (seleceter1 == 2) {

			dedector1 = -3;
			hatto1 = 23;

		} else if (seleceter1 == 1) {

			dedector1 = -2;
			hatto1 = 24;
		}

		Start--;
		if (Start == dedector1) {
			BDL1 = 1;
			lock1 = 0;

			if (seleceter1 == 1) {
				seleceter1 = 4;
			}

			HD44780_Clear();
			seleceter1--;
			Start = hatto1;
		}

		if ((z == 1 && (Start == 0 || Start + 1 == 0 || Start + 2 == 0))) {

			dead1 = 1;

		} else {
			dead1 = 0;
		}

	}

	void Upper_Block_creator(void) {
		if (lock2 == 0) {
			switch (selecter2) {
			case 1:
				HD44780_SetCursor(stort, 0);
				HD44780_PrintSpecialChar(4);
				break;
			case 2:
				HD44780_SetCursor(stort, 0);
				HD44780_PrintSpecialChar(4);
				HD44780_SetCursor(stort + 1, 0);
				HD44780_PrintSpecialChar(4);

				break;

			case 3:

				HD44780_SetCursor(stort, 0);
				HD44780_PrintSpecialChar(4);
				HD44780_SetCursor(stort + 1, 0);
				HD44780_PrintSpecialChar(4);
				HD44780_SetCursor(stort + 2, 0);
				HD44780_PrintSpecialChar(4);

				break;

			default:
				HD44780_Clear();
			}
		}
		if(lock2==1&& selecter2==3 ){
			BDL2=1;
			HD44780_SetCursor(stort, 0);
			HD44780_PrintSpecialChar(4);
		}

		if (selecter2 == 3) {

			dedector2 = -4;
			hatto2 = 22;
		} else if (selecter2 == 2) {

			dedector2 = -3;
			hatto2 = 23;

		} else if (selecter2 == 1) {

			dedector2 = -2;
			hatto2 = 24;
		}

		stort--;
		if (stort == dedector2) {
			BDL2 = 1;
			lock2 = 0;

			if (selecter2 == 1) {
				selecter2 = 4;
			}

			HD44780_Clear();
			selecter2--;
			stort = hatto2;
		}

		if ((z == 0 && (stort == 0 || stort + 1 == 0 || stort + 2 == 0))) {

			dead2 = 1;

		} else {
			dead2 = 0;
		}

	}
	void Block_creator_Bonus(int pos) {
		if (lock3 == 0) {

		switch (selecter3) {
		case 1:
			HD44780_SetCursor(ktort, pos);
			HD44780_PrintSpecialChar(4);

			break;
		case 2:
			HD44780_SetCursor(ktort, pos);
			HD44780_PrintSpecialChar(4);
			HD44780_SetCursor(ktort + 1, pos);
			HD44780_PrintSpecialChar(4);

			break;

		case 3:

			HD44780_SetCursor(ktort, pos);
			HD44780_PrintSpecialChar(4);
			HD44780_SetCursor(ktort + 1, pos);
			HD44780_PrintSpecialChar(4);
			HD44780_SetCursor(ktort + 2, pos);
			HD44780_PrintSpecialChar(4);

			break;

		default:
			HD44780_Clear();
		}}
		if(lock3==1&& selecter3==3 ){
			BDL3=1;
			HD44780_SetCursor(ktort, pos);
			HD44780_PrintSpecialChar(4);
		}

		if (selecter3 == 3) {

			dedector3 = -4;
			hatto3 = 22;
		} else if (selecter3 == 2) {

			dedector3 = -3;
			hatto3 = 23;

		} else if (selecter3 == 1) {

			dedector3 = -2;
			hatto3 = 24;
		}

		ktort--;
		if (ktort == dedector3) {
			BDL3 = 1;
			lock3 = 0;

			if (selecter3 == 3) {
				selecter3 = 0;
			}
			HD44780_Clear();
			selecter3++;
			ktort = hatto3;

			if (statues_block == 1) {
				statues_block = 0;

			} else {

				statues_block = 1;

			}

		}
		if (((z == 1 && statues_block == 1)
				&& (ktort == 0 || ktort + 1 == 0 || ktort + 2 == 0))
				|| ((z == 0 && statues_block == 0)
						&& (ktort == 0 || ktort + 1 == 0 || ktort + 2 == 0))) {

			dead3 = 1;

		} else {
			dead3 = 0;
		}

	}

	void shoot(void) {
		if (trigger == 1) {
			if (state_detect == 0) {
				state_detect = 1;
				line = z;
			}
			HD44780_SetCursor(fireball_pos, line);
			HD44780_PrintSpecialChar(0);

			fireball_pos++;
		}
	}



	/* USER CODE END 0 */

	/**
	 * @brief  The application entry point.
	 * @retval int
	 */
	int main(void) {
		/* USER CODE BEGIN 1 */

		/* USER CODE END 1 */

		/* MCU Configuration--------------------------------------------------------*/

		/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
		HAL_Init();

		/* USER CODE BEGIN Init */

		/* USER CODE END Init */

		/* Configure the system clock */
		SystemClock_Config();

		/* USER CODE BEGIN SysInit */

		/* USER CODE END SysInit */

		/* Initialize all configured peripherals */
		MX_GPIO_Init();
		MX_USART2_UART_Init();
		MX_I2C1_Init();
		MX_TIM10_Init();
		MX_ADC1_Init();
		/* USER CODE BEGIN 2 */
		HAL_TIM_Base_Start_IT(&htim10);

		HD44780_Init(2);
		/* USER CODE END 2 */

		/* Infinite loop */
		/* USER CODE BEGIN WHILE */
		while (1) {
			/* USER CODE END WHILE */

			/* USER CODE BEGIN 3 */

			while (menu_state) {

				HD44780_Clear();
				HD44780_SetCursor(0, 0);
				HD44780_PrintStr("Difficulty");

				HD44780_SetCursor(1, 1);
				HD44780_PrintStr("Hard");

				HD44780_SetCursor(9, 1);
				HD44780_PrintStr("Easy");

				if (ADC_val < 2000) {

					HD44780_SetCursor(0, 1);
					HD44780_Blink();

				} else if (ADC_val > 2000) {

					HD44780_SetCursor(8, 1);
					HD44780_Blink();

				}

				HAL_Delay(1000);

			}

			if ((dead1 == 1 && BDL1 == 1) || (dead2 == 1 && BDL2 == 1)
					|| (dead3 == 1 &&BDL3 == 1)) {

				HD44780_Clear();
				HD44780_SetCursor(4, 0);
				HD44780_PrintStr("YOU DIED!");
				HD44780_SetCursor(4, 1);
				HD44780_PrintStr("SCORE:");

				itoa(point, snum, 10);
				HD44780_SetCursor(10, 1);
				HD44780_PrintStr(snum);
				HD44780_Blink();
				HAL_Delay(1000);

			}

			else {
				character_move();
				shoot();
				Lower_Block_creator();
				Upper_Block_creator();
				Block_creator_Bonus(statues_block);
				point++;

				if (z == 0) {
					jump_caunter++;
					if (jump_caunter > 3
							&& (Start != 0 || Start + 1 != 0 || Start + 2 != 0
									|| statues_block != 0 || ktort != 0
									|| ktort + 1 != 0 || ktort + 2 != 0)) {
						z = 1;
						jump_caunter = 0;
					}

				}
				HAL_Delay(Speed);

				/* Time_Counter++;
				 if(Time_Counter==5 && safety==0){

				 Time--;
				 Time_Counter=0;
				 }
				 if(Time<100){
				 safety=1;
				 }*/

			}
		}

		/* USER CODE END 3 */
	}

	/**
	 * @brief System Clock Configuration
	 * @retval None
	 */
	void SystemClock_Config(void) {
		RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
		RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

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
		RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
		RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
		RCC_OscInitStruct.PLL.PLLM = 8;
		RCC_OscInitStruct.PLL.PLLN = 100;
		RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
		RCC_OscInitStruct.PLL.PLLQ = 4;
		if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
			Error_Handler();
		}

		/** Initializes the CPU, AHB and APB buses clocks
		 */
		RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
				| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
		RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
		RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
		RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
		RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

		if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3)
				!= HAL_OK) {
			Error_Handler();
		}
	}

	/**
	 * @brief ADC1 Initialization Function
	 * @param None
	 * @retval None
	 */
	static void MX_ADC1_Init(void) {

		/* USER CODE BEGIN ADC1_Init 0 */

		/* USER CODE END ADC1_Init 0 */

		ADC_ChannelConfTypeDef sConfig = { 0 };

		/* USER CODE BEGIN ADC1_Init 1 */

		/* USER CODE END ADC1_Init 1 */

		/** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
		 */
		hadc1.Instance = ADC1;
		hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
		hadc1.Init.Resolution = ADC_RESOLUTION_12B;
		hadc1.Init.ScanConvMode = DISABLE;
		hadc1.Init.ContinuousConvMode = ENABLE;
		hadc1.Init.DiscontinuousConvMode = DISABLE;
		hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
		hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
		hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
		hadc1.Init.NbrOfConversion = 1;
		hadc1.Init.DMAContinuousRequests = DISABLE;
		hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
		if (HAL_ADC_Init(&hadc1) != HAL_OK) {
			Error_Handler();
		}

		/** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
		 */
		sConfig.Channel = ADC_CHANNEL_6;
		sConfig.Rank = 1;
		sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
		if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK) {
			Error_Handler();
		}
		/* USER CODE BEGIN ADC1_Init 2 */

		/* USER CODE END ADC1_Init 2 */

	}

	/**
	 * @brief I2C1 Initialization Function
	 * @param None
	 * @retval None
	 */
	static void MX_I2C1_Init(void) {

		/* USER CODE BEGIN I2C1_Init 0 */

		/* USER CODE END I2C1_Init 0 */

		/* USER CODE BEGIN I2C1_Init 1 */

		/* USER CODE END I2C1_Init 1 */
		hi2c1.Instance = I2C1;
		hi2c1.Init.ClockSpeed = 400000;
		hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
		hi2c1.Init.OwnAddress1 = 0;
		hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
		hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
		hi2c1.Init.OwnAddress2 = 0;
		hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
		hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
		if (HAL_I2C_Init(&hi2c1) != HAL_OK) {
			Error_Handler();
		}
		/* USER CODE BEGIN I2C1_Init 2 */

		/* USER CODE END I2C1_Init 2 */

	}

	/**
	 * @brief TIM10 Initialization Function
	 * @param None
	 * @retval None
	 */
	static void MX_TIM10_Init(void) {

		/* USER CODE BEGIN TIM10_Init 0 */

		/* USER CODE END TIM10_Init 0 */

		/* USER CODE BEGIN TIM10_Init 1 */

		/* USER CODE END TIM10_Init 1 */
		htim10.Instance = TIM10;
		htim10.Init.Prescaler = 420 - 1;
		htim10.Init.CounterMode = TIM_COUNTERMODE_UP;
		htim10.Init.Period = 1000;
		htim10.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
		htim10.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
		if (HAL_TIM_Base_Init(&htim10) != HAL_OK) {
			Error_Handler();
		}
		/* USER CODE BEGIN TIM10_Init 2 */

		/* USER CODE END TIM10_Init 2 */

	}

	/**
	 * @brief USART2 Initialization Function
	 * @param None
	 * @retval None
	 */
	static void MX_USART2_UART_Init(void) {

		/* USER CODE BEGIN USART2_Init 0 */

		/* USER CODE END USART2_Init 0 */

		/* USER CODE BEGIN USART2_Init 1 */

		/* USER CODE END USART2_Init 1 */
		huart2.Instance = USART2;
		huart2.Init.BaudRate = 115200;
		huart2.Init.WordLength = UART_WORDLENGTH_8B;
		huart2.Init.StopBits = UART_STOPBITS_1;
		huart2.Init.Parity = UART_PARITY_NONE;
		huart2.Init.Mode = UART_MODE_TX_RX;
		huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
		huart2.Init.OverSampling = UART_OVERSAMPLING_16;
		if (HAL_UART_Init(&huart2) != HAL_OK) {
			Error_Handler();
		}
		/* USER CODE BEGIN USART2_Init 2 */

		/* USER CODE END USART2_Init 2 */

	}

	/**
	 * @brief GPIO Initialization Function
	 * @param None
	 * @retval None
	 */
	static void MX_GPIO_Init(void) {
		GPIO_InitTypeDef GPIO_InitStruct = { 0 };
		/* USER CODE BEGIN MX_GPIO_Init_1 */
		/* USER CODE END MX_GPIO_Init_1 */

		/* GPIO Ports Clock Enable */
		__HAL_RCC_GPIOC_CLK_ENABLE();
		__HAL_RCC_GPIOH_CLK_ENABLE();
		__HAL_RCC_GPIOA_CLK_ENABLE();
		__HAL_RCC_GPIOB_CLK_ENABLE();

		/*Configure GPIO pin Output Level */
		HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

		/*Configure GPIO pin : B1_Pin */
		GPIO_InitStruct.Pin = B1_Pin;
		GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

		/*Configure GPIO pin : PC0 */
		GPIO_InitStruct.Pin = GPIO_PIN_0;
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

		/*Configure GPIO pin : LD2_Pin */
		GPIO_InitStruct.Pin = LD2_Pin;
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

		/* EXTI interrupt init*/
		HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
		HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

		/* USER CODE BEGIN MX_GPIO_Init_2 */
		/* USER CODE END MX_GPIO_Init_2 */
	}

	/* USER CODE BEGIN 4 */

	/* USER CODE END 4 */

	/**
	 * @brief  This function is executed in case of error occurrence.
	 * @retval None
	 */
	void Error_Handler(void) {
		/* USER CODE BEGIN Error_Handler_Debug */
		/* User can add his own implementation to report the HAL error return state */
		__disable_irq();
		while (1) {
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
