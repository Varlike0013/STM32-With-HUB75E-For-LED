/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include <stdio.h>

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
//led_io口定义（R:PB0-G:PB1-B:PA3）
//key_io口定义（KEY1:PA0-KEY2:PC13）
//usart1_io(debug_output)口定义（RX:PA10	TX:PA0）
#define LED_RED_Pin GPIO_PIN_0
#define LED_RED_GPIO_Port GPIOB

#define BROAD_OE_Pin GPIO_PIN_3//OE->PK3
#define BROAD_OE_GPIO_Port GPIOK
#define BROAD_LAT_Pin GPIO_PIN_14//LAT->PJ14
#define BROAD_LAT_GPIO_Port GPIOJ

#define BROAD_CLK_Pin GPIO_PIN_12//CLK->PJ12
#define BROAD_CLK_GPIO_Port GPIOJ
#define BROAD_E_Pin GPIO_PIN_5//E->PJ5
#define BROAD_E_GPIO_Port GPIOJ
#define BROAD_D_Pin GPIO_PIN_1//D->PK1
#define BROAD_D_GPIO_Port GPIOK
#define BROAD_C_Pin GPIO_PIN_11//C->PJ11
#define BROAD_C_GPIO_Port GPIOJ
#define BROAD_B_Pin GPIO_PIN_9//B->PJ9
#define BROAD_B_GPIO_Port GPIOJ
#define BROAD_A_Pin GPIO_PIN_7//A->PJ7
#define BROAD_A_GPIO_Port GPIOJ
#define BROAD_B2_Pin GPIO_PIN_3//B2->PJ3
#define BROAD_B2_GPIO_Port GPIOJ
#define BROAD_G2_Pin GPIO_PIN_1//G2->PJ1
#define BROAD_G2_GPIO_Port GPIOJ
#define BROAD_R2_Pin GPIO_PIN_15 //R2->PI15
#define BROAD_R2_GPIO_Port GPIOI
#define BROAD_B1_Pin GPIO_PIN_7//B1->PA7
#define BROAD_B1_GPIO_Port GPIOA
#define BROAD_G1_Pin GPIO_PIN_12 //G1->PG12
#define BROAD_G1_GPIO_Port GPIOG
#define BROAD_R1_Pin GPIO_PIN_13//R1->PG13
#define BROAD_R1_GPIO_Port GPIOG
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
