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
#include "stm32f1xx_hal.h"

#include "stm32f1xx_ll_tim.h"
#include "stm32f1xx_ll_system.h"
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_exti.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_cortex.h"
#include "stm32f1xx_ll_rcc.h"
#include "stm32f1xx_ll_utils.h"
#include "stm32f1xx_ll_pwr.h"
#include "stm32f1xx_ll_dma.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include "typedef.h"
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
extern TMyFlags g_MyFlags ; 
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define ADDR0_Pin LL_GPIO_PIN_0
#define ADDR0_GPIO_Port GPIOA
#define ADDR1_Pin LL_GPIO_PIN_1
#define ADDR1_GPIO_Port GPIOA
#define ADDR2_Pin LL_GPIO_PIN_2
#define ADDR2_GPIO_Port GPIOA
#define ADDR3_Pin LL_GPIO_PIN_3
#define ADDR3_GPIO_Port GPIOA
#define ADDR4_Pin LL_GPIO_PIN_4
#define ADDR4_GPIO_Port GPIOA
#define OPT1_Pin LL_GPIO_PIN_0
#define OPT1_GPIO_Port GPIOB
#define LED2_Pin LL_GPIO_PIN_10
#define LED2_GPIO_Port GPIOB
#define LED1_Pin LL_GPIO_PIN_11
#define LED1_GPIO_Port GPIOB
#define OS1_Pin LL_GPIO_PIN_12
#define OS1_GPIO_Port GPIOB
#define OS2_Pin LL_GPIO_PIN_13
#define OS2_GPIO_Port GPIOB
#define OS3_Pin LL_GPIO_PIN_14
#define OS3_GPIO_Port GPIOB
#define OS4_Pin LL_GPIO_PIN_15
#define OS4_GPIO_Port GPIOB
#define RELAY1_Pin LL_GPIO_PIN_8
#define RELAY1_GPIO_Port GPIOA
#define RELAY2_Pin LL_GPIO_PIN_9
#define RELAY2_GPIO_Port GPIOA
#define RELAY3_Pin LL_GPIO_PIN_10
#define RELAY3_GPIO_Port GPIOA
#define RELAY4_Pin LL_GPIO_PIN_11
#define RELAY4_GPIO_Port GPIOA
#define OPT2_Pin LL_GPIO_PIN_5
#define OPT2_GPIO_Port GPIOB
#define OPT3_Pin LL_GPIO_PIN_6
#define OPT3_GPIO_Port GPIOB
#define OPT4_Pin LL_GPIO_PIN_7
#define OPT4_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */
#define __USE_DBG
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
