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
#define MAKE_FRAME_ID( msg_type_id, board_addr) ((((uint32_t)msg_type_id) << 5) | (board_addr))
#define GET_MODULE_ADDR( frame_id) ((frame_id) & 0x1F) //получение адреса модуля
#define GET_MSG_TYPE( frame_id) (((frame_id) >> 5) & 0x3F) //получение типа сообщения

#define MAKE_MSG_DATA0(module_id, data_type) ( (module_id << 3 ) | data_type)
#define GET_MODULE_ID(data0) (((data0) >> 3)  & 0x1F) //получение типа модуля-отправителя
#define GET_TYPE_DATA(data0) ((data0) & 0x07) //получение кода вида данных
/* USER CODE END Private defines */

void MX_CAN_Init(void);

/* USER CODE BEGIN Prototypes */
uint32_t Send_Message_C2 (void);

extern MESSAGE_A_t MESSAGE_A;
extern uint8_t CAN_flag_RX;
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __CAN_H__ */

