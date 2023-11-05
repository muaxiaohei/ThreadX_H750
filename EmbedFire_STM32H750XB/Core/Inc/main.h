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
#include "stm32h7xx_hal.h"

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
extern __attribute__((aligned(32), section(".SDRAM_LTDC"))) unsigned long _ac1696356583[];
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define USR_KEY_SW2_Pin GPIO_PIN_13
#define USR_KEY_SW2_GPIO_Port GPIOC
#define TS_RST_Pin GPIO_PIN_7
#define TS_RST_GPIO_Port GPIOG
#define TS_IIC_INT_Pin GPIO_PIN_3
#define TS_IIC_INT_GPIO_Port GPIOG
#define WL_REG_ON_Pin GPIO_PIN_2
#define WL_REG_ON_GPIO_Port GPIOC
#define USR_KEY_SW1_Pin GPIO_PIN_0
#define USR_KEY_SW1_GPIO_Port GPIOA
#define LED_G_Pin GPIO_PIN_1
#define LED_G_GPIO_Port GPIOB
#define LED_B_Pin GPIO_PIN_3
#define LED_B_GPIO_Port GPIOA
#define LED_R_Pin GPIO_PIN_0
#define LED_R_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
#define USR_KEY_SW2_READ()	HAL_GPIO_ReadPin(USR_KEY_SW2_GPIO_Port, USR_KEY_SW2_Pin)
#define USR_KEY_SW1_READ()	HAL_GPIO_ReadPin(USR_KEY_SW1_GPIO_Port, USR_KEY_SW1_Pin)

#define LED_G_ON()		HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, GPIO_PIN_RESET)
#define LED_G_OFF()		HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, GPIO_PIN_SET)

#define LED_B_ON()		HAL_GPIO_WritePin(LED_B_GPIO_Port, LED_B_Pin, GPIO_PIN_RESET)
#define LED_B_OFF()		HAL_GPIO_WritePin(LED_B_GPIO_Port, LED_B_Pin, GPIO_PIN_SET)

#define LED_R_ON()		HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, GPIO_PIN_RESET)
#define LED_R_OFF()		HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, GPIO_PIN_SET)

//#define LCD_BL_ON()		HAL_GPIO_WritePin(LCD_BL_GPIO_Port, LCD_BL_Pin, GPIO_PIN_SET)
//#define LCD_BL_OFF()	HAL_GPIO_WritePin(LCD_BL_GPIO_Port, LCD_BL_Pin, GPIO_PIN_RESET)
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
