/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    can.h
  * @brief   This file contains all the function prototypes for
  *          the can.c file
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
#ifndef __CAN_H__
#define __CAN_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern CAN_HandleTypeDef hcan;

/* USER CODE BEGIN Private defines */
#define MODULE_TYPE_MKIP                             0x15	// Код типа модуля - МКИП
#define MSG_TYPE_A0                                  0x000 // 000000
#define MSG_TYPE_A1                                  0x001 // 000001
#define MSG_TYPE_A2                                  0x002 // 000010
#define MSG_TYPE_A3                                  0x003 // 000011
#define MSG_TYPE_B                                   0x008 // 001000
#define MSG_TYPE_C                                   0x010 // 010000
#define MSG_TYPE_D                                   0x020 // 100000

#define MAKE_FRAME_ID( msg_type_id, board_addr) ((((uint32_t)msg_type_id) << 5) | (board_addr))
/* USER CODE END Private defines */

void MX_CAN_Init(void);

/* USER CODE BEGIN Prototypes */
uint32_t Send_Message_C2 (void);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __CAN_H__ */

