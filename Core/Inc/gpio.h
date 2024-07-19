/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.h
  * @brief   This file contains all the function prototypes for
  *          the gpio.c file
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
#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */
#define LED_GREEN(x) ((x)? (LL_GPIO_SetOutputPin(LED1_GPIO_Port, LED1_Pin)) : (LL_GPIO_ResetOutputPin(LED1_GPIO_Port, LED1_Pin)))
#define LED_RED(x) ((x)? (LL_GPIO_SetOutputPin(LED2_GPIO_Port, LED2_Pin)) : (LL_GPIO_ResetOutputPin(LED2_GPIO_Port, LED2_Pin)))

#define TOOGLE_GREEN_LED() (LED_GREEN(!(LL_GPIO_IsOutputPinSet(LED1_GPIO_Port, LED1_Pin))))
#define TOOGLE_RED_LED() (LED_RED(!(LL_GPIO_IsOutputPinSet(LED2_GPIO_Port, LED2_Pin))))

#define SWITCH_RELAY1(x) ((x)? (LL_GPIO_SetOutputPin(RELAY1_GPIO_Port, RELAY1_Pin)) : (LL_GPIO_ResetOutputPin(RELAY1_GPIO_Port, RELAY1_Pin)))
#define SWITCH_RELAY2(x) ((x)? (LL_GPIO_SetOutputPin(RELAY2_GPIO_Port, RELAY2_Pin)) : (LL_GPIO_ResetOutputPin(RELAY2_GPIO_Port, RELAY2_Pin)))
#define SWITCH_RELAY3(x) ((x)? (LL_GPIO_SetOutputPin(RELAY3_GPIO_Port, RELAY3_Pin)) : (LL_GPIO_ResetOutputPin(RELAY3_GPIO_Port, RELAY3_Pin)))
#define SWITCH_RELAY4(x) ((x)? (LL_GPIO_SetOutputPin(RELAY4_GPIO_Port, RELAY4_Pin)) : (LL_GPIO_ResetOutputPin(RELAY4_GPIO_Port, RELAY4_Pin)))

#define SWITCH_OPT1(x) ((x)? (LL_GPIO_SetOutputPin(OPT1_GPIO_Port, OPT1_Pin)) : (LL_GPIO_ResetOutputPin(OPT1_GPIO_Port, OPT1_Pin)))
#define SWITCH_OPT2(x) ((x)? (LL_GPIO_SetOutputPin(OPT2_GPIO_Port, OPT2_Pin)) : (LL_GPIO_ResetOutputPin(OPT2_GPIO_Port, OPT2_Pin)))
#define SWITCH_OPT3(x) ((x)? (LL_GPIO_SetOutputPin(OPT3_GPIO_Port, OPT3_Pin)) : (LL_GPIO_ResetOutputPin(OPT3_GPIO_Port, OPT3_Pin)))
#define SWITCH_OPT4(x) ((x)? (LL_GPIO_SetOutputPin(OPT4_GPIO_Port, OPT4_Pin)) : (LL_GPIO_ResetOutputPin(OPT4_GPIO_Port, OPT4_Pin)))
/* USER CODE END Private defines */

void MX_GPIO_Init(void);

/* USER CODE BEGIN Prototypes */
int8_t Get_Status_Pins(void);
uint32_t Get_Module_Address( void );
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */

