/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define PWMA_Pin GPIO_PIN_5
#define PWMA_GPIO_Port GPIOA
#define E1A_Pin GPIO_PIN_6
#define E1A_GPIO_Port GPIOA
#define E1B_Pin GPIO_PIN_7
#define E1B_GPIO_Port GPIOA
#define BIN2_Pin GPIO_PIN_7
#define BIN2_GPIO_Port GPIOE
#define BIN1_Pin GPIO_PIN_8
#define BIN1_GPIO_Port GPIOE
#define AIN1_Pin GPIO_PIN_9
#define AIN1_GPIO_Port GPIOE
#define AIN2_Pin GPIO_PIN_10
#define AIN2_GPIO_Port GPIOE
#define KEY1_Pin GPIO_PIN_11
#define KEY1_GPIO_Port GPIOE
#define KEY2_Pin GPIO_PIN_12
#define KEY2_GPIO_Port GPIOE
#define KEY3_Pin GPIO_PIN_13
#define KEY3_GPIO_Port GPIOE
#define KEY4_Pin GPIO_PIN_14
#define KEY4_GPIO_Port GPIOE
#define KEY5_Pin GPIO_PIN_15
#define KEY5_GPIO_Port GPIOE
#define E2A_Pin GPIO_PIN_12
#define E2A_GPIO_Port GPIOD
#define E2B_Pin GPIO_PIN_13
#define E2B_GPIO_Port GPIOD
#define GRAY8_Pin GPIO_PIN_15
#define GRAY8_GPIO_Port GPIOD
#define GRAY7_Pin GPIO_PIN_6
#define GRAY7_GPIO_Port GPIOC
#define GRAY6_Pin GPIO_PIN_7
#define GRAY6_GPIO_Port GPIOC
#define GRAY5_Pin GPIO_PIN_8
#define GRAY5_GPIO_Port GPIOC
#define GRAY4_Pin GPIO_PIN_9
#define GRAY4_GPIO_Port GPIOC
#define GRAY3_Pin GPIO_PIN_8
#define GRAY3_GPIO_Port GPIOA
#define GARY2_Pin GPIO_PIN_11
#define GARY2_GPIO_Port GPIOA
#define GRAY1_Pin GPIO_PIN_12
#define GRAY1_GPIO_Port GPIOA
#define PWMB_Pin GPIO_PIN_3
#define PWMB_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
