/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
#define NS_RED       GPIO_PIN_0
#define NS_YELLOW    GPIO_PIN_1
#define NS_GREEN     GPIO_PIN_2

#define EW_RED       GPIO_PIN_3
#define EW_YELLOW    GPIO_PIN_4
#define EW_GREEN     GPIO_PIN_8

#define EX3_ALL_PINS \
    (GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | \
     GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_8)
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
GPIO_TypeDef *clockPorts[12] =
{
    GPIOB,     // 0
    GPIOB,     // 1
    GPIOB,     // 2
    GPIOB,     // 3
    GPIOB,     // 4
    GPIOB,     // 5
    GPIOB,     // 6
    GPIOB,     // 7
    GPIOB,     // 8
    GPIOC,     // 9
    GPIOC,     // 10
    GPIOC      // 11
};

uint16_t clockPins[12] =
{
    GPIO_PIN_7,     // 0  -> 12h
    GPIO_PIN_8,     // 1
    GPIO_PIN_9,     // 2
    GPIO_PIN_10,    // 3
    GPIO_PIN_11,    // 4
    GPIO_PIN_12,    // 5
    GPIO_PIN_13,    // 6
    GPIO_PIN_14,    // 7
    GPIO_PIN_15,    // 8
    GPIO_PIN_13,    // 9  GPIOC
    GPIO_PIN_14,    // 10 GPIOC
    GPIO_PIN_15     // 11 GPIOC
};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void clearAllClock(void)
{
    for (int i = 0; i < 12; i++)
    {
        HAL_GPIO_WritePin(clockPorts[i],
                          clockPins[i],
                          GPIO_PIN_SET);
    }
}
void setNumberOnClock(int num)
{
    if (num < 0 || num > 11)
        return;

    HAL_GPIO_WritePin(clockPorts[num],
                      clockPins[num],
                      GPIO_PIN_RESET);
}
void clearNumberOnClock(int num)
{
    if (num < 0 || num > 11)
        return;

    HAL_GPIO_WritePin(clockPorts[num],
                      clockPins[num],
                      GPIO_PIN_SET);
}
void trafficOffAll(void)
{
	 HAL_GPIO_WritePin(GPIOA,
	                      EX3_ALL_PINS,
	                      GPIO_PIN_SET);
}
void display7SEG(int num)
{


    const uint8_t segmentTable[10] =
    {
        0x3F,   // 0: a b c d e f
        0x06,   // 1: b c
        0x5B,   // 2: a b d e g
        0x4F,   // 3: a b c d g
        0x66,   // 4: b c f g
        0x6D,   // 5: a c d f g
        0x7D,   // 6: a c d e f g
        0x07,   // 7: a b c
        0x7F,   // 8: a b c d e f g
        0x6F    // 9: a b c d f g
    };

    if (num < 0 || num > 9)
    {
        return;
    }

    uint8_t pattern = segmentTable[num];

    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0,
        (pattern & (1 << 0)) ? GPIO_PIN_RESET : GPIO_PIN_SET);

    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1,
        (pattern & (1 << 1)) ? GPIO_PIN_RESET : GPIO_PIN_SET);

    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2,
        (pattern & (1 << 2)) ? GPIO_PIN_RESET : GPIO_PIN_SET);

    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3,
        (pattern & (1 << 3)) ? GPIO_PIN_RESET : GPIO_PIN_SET);

    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4,
        (pattern & (1 << 4)) ? GPIO_PIN_RESET : GPIO_PIN_SET);

    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5,
        (pattern & (1 << 5)) ? GPIO_PIN_RESET : GPIO_PIN_SET);

    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6,
        (pattern & (1 << 6)) ? GPIO_PIN_RESET : GPIO_PIN_SET);
}
void displayCountdownRange(int from, int to)
{
    for (int t = from; t >= to; t--)
    {
        display7SEG(t);
        HAL_Delay(1000);
    }
}
void countdown7SEG(int seconds)
{
    for (int i = seconds; i >= 1; i--)
    {
        display7SEG(i);

        HAL_Delay(1000);
    }
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  HAL_Init();


  SystemClock_Config();




  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */



  int counter = 0;
  int second = 40;
  int minute = 20;
  int hour = 3;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  /*Ex1*/
  /*while (1)
  {
	  HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
	    HAL_GPIO_TogglePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin);

	    HAL_Delay(2000);

  }*/

  /*EX2*/
 /* while (1)
  {

      HAL_GPIO_WritePin(GPIOA,
                        GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7,
                        GPIO_PIN_SET);

      HAL_GPIO_WritePin(GPIOA,
                        GPIO_PIN_5,
                        GPIO_PIN_RESET);

      HAL_Delay(5000);



      HAL_GPIO_WritePin(GPIOA,
                        GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7,
                        GPIO_PIN_SET);

      HAL_GPIO_WritePin(GPIOA,
                        GPIO_PIN_6,
                        GPIO_PIN_RESET);

      HAL_Delay(2000);



      HAL_GPIO_WritePin(GPIOA,
                        GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7,
                        GPIO_PIN_SET);

      HAL_GPIO_WritePin(GPIOA,
                        GPIO_PIN_7,
                        GPIO_PIN_RESET);

      HAL_Delay(3000);
  }*/

  /*EX3*/
  /*while (1)
  {


    HAL_GPIO_WritePin(GPIOA,
                      GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 |
                      GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_8,
                      GPIO_PIN_SET);

    HAL_GPIO_WritePin(GPIOA,
                      GPIO_PIN_2 | GPIO_PIN_3,
                      GPIO_PIN_RESET);

    HAL_Delay(3000);



    HAL_GPIO_WritePin(GPIOA,
                      GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 |
                      GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_8,
                      GPIO_PIN_SET);

    HAL_GPIO_WritePin(GPIOA,
                      GPIO_PIN_1 | GPIO_PIN_3,
                      GPIO_PIN_RESET);

    HAL_Delay(2000);




    HAL_GPIO_WritePin(GPIOA,
                      GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 |
                      GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_8,
                      GPIO_PIN_SET);

    HAL_GPIO_WritePin(GPIOA,
                      GPIO_PIN_0 | GPIO_PIN_8,
                      GPIO_PIN_RESET);

    HAL_Delay(3000);



    HAL_GPIO_WritePin(GPIOA,
                      GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 |
                      GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_8,
                      GPIO_PIN_SET);

    HAL_GPIO_WritePin(GPIOA,
                      GPIO_PIN_0 | GPIO_PIN_4,
                      GPIO_PIN_RESET);

    HAL_Delay(2000);
  }*/

  /*EX4*/
  /*while (1)
  {
      if (counter >= 10)
      {
          counter = 0;
      }

      display7SEG(counter);

      counter++;

      HAL_Delay(1000);
  }
  /* EX5 */
 /* while (1)
  {
    trafficOffAll();

    HAL_GPIO_WritePin(GPIOA,
                      NS_GREEN | EW_RED,
                      GPIO_PIN_RESET);

    displayCountdownRange(3, 1);




    trafficOffAll();

    HAL_GPIO_WritePin(GPIOA,
                      NS_YELLOW | EW_RED,
                      GPIO_PIN_RESET);

    displayCountdownRange(2, 1);



    trafficOffAll();

    HAL_GPIO_WritePin(GPIOA,
                      NS_RED | EW_GREEN,
                      GPIO_PIN_RESET);

    displayCountdownRange(5, 3);




    trafficOffAll();

    HAL_GPIO_WritePin(GPIOA,
                      NS_RED | EW_YELLOW,
                      GPIO_PIN_RESET);

    displayCountdownRange(2, 1);
  }
  /* EX6 */
  /*while (1)
  {
      for (int i = 0; i < 12; i++)
      {
          for (int j = 0; j < 12; j++)
          {
              HAL_GPIO_WritePin(clockPorts[j],
                                clockPins[j],
                                GPIO_PIN_SET);
          }

          HAL_GPIO_WritePin(clockPorts[i],
                            clockPins[i],
                            GPIO_PIN_RESET);

          HAL_Delay(500);
      }
  }*/
  /* EX10 */
  while (1)
  {
      clearAllClock();

      int secondPos = second / 5;
      int minutePos = minute / 5;
      int hourPos   = hour % 12;

      setNumberOnClock(hourPos);
      setNumberOnClock(minutePos);
      setNumberOnClock(secondPos);

      HAL_Delay(100);

      second++;

      if (second >= 60)
      {
          second = 0;
          minute++;
      }

      if (minute >= 60)
      {
          minute = 0;
          hour++;
      }

      if (hour >= 12)
      {
          hour = 0;
      }
  }
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

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

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{

	GPIO_InitTypeDef GPIO_InitStruct = {0};

	    /* =============================================
	       Enable GPIO clocks
	       ============================================= */
	    __HAL_RCC_GPIOA_CLK_ENABLE();
	    __HAL_RCC_GPIOB_CLK_ENABLE();
	    __HAL_RCC_GPIOC_CLK_ENABLE();


	    /* =============================================
	       GPIOA
	       EX2 + EX3
	       PA0 -> PA8
	       ============================================= */

	    /* Active LOW LEDs -> SET means OFF */
	    HAL_GPIO_WritePin(GPIOA,
	                      GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 |
	                      GPIO_PIN_3 | GPIO_PIN_4 |
	                      GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 |
	                      GPIO_PIN_8,
	                      GPIO_PIN_SET);

	    GPIO_InitStruct.Pin =
	                      GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 |
	                      GPIO_PIN_3 | GPIO_PIN_4 |
	                      GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 |
	                      GPIO_PIN_8;

	    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	    GPIO_InitStruct.Pull = GPIO_NOPULL;
	    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

	    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);


	    /* =============================================
	       GPIOB
	       EX4/5: PB0 -> PB6  = 7SEG
	       EX6:   PB7 -> PB15 = CLOCK
	       ============================================= */

	    /* Turn all PB outputs OFF initially */
	    HAL_GPIO_WritePin(GPIOB,
	                      GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 |
	                      GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 |
	                      GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 |
	                      GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 |
	                      GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 |
	                      GPIO_PIN_15,
	                      GPIO_PIN_SET);

	    GPIO_InitStruct.Pin =
	                      GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 |
	                      GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 |
	                      GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 |
	                      GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 |
	                      GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 |
	                      GPIO_PIN_15;

	    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	    GPIO_InitStruct.Pull = GPIO_NOPULL;
	    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

	    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);


	    /* =============================================
	       GPIOC
	       EX6: PC13 -> PC15
	       ============================================= */

	    HAL_GPIO_WritePin(GPIOC,
	                      GPIO_PIN_13 |
	                      GPIO_PIN_14 |
	                      GPIO_PIN_15,
	                      GPIO_PIN_SET);

	    GPIO_InitStruct.Pin =
	                      GPIO_PIN_13 |
	                      GPIO_PIN_14 |
	                      GPIO_PIN_15;

	    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	    GPIO_InitStruct.Pull = GPIO_NOPULL;
	    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

	    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

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
(uint8_t *file, uint32_t line)
{

}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
