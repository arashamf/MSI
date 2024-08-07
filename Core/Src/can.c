/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    can.c
  * @brief   This file provides code for the configuration
  *          of the CAN instances.
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
/* Includes ------------------------------------------------------------------*/
#include "can.h"

/* USER CODE BEGIN 0 */
#include "typedef.h"
#include "gpio.h"
#include "protocol.h"

#define CAN_OK 			0
#define CAN_ERROR 	1

// Private functions prototypes -----------------------------------------------------------------------//
static TRxResult ReadMsgCAN(void);
static void Task_ProcCANRequests_And_CheckCANCondition( void );
static uint32_t CAN1_Send_Message (CAN_TxHeaderTypeDef * , uint8_t * );

//Private variables -----------------------------------------------------------------------------------//
static CAN_TxHeaderTypeDef CAN_TxHeader; //структура для отправки кадров CAN1 
static CAN_RxHeaderTypeDef CAN_RxHeader; //структура для приёма кадров CAN1

//static CAN_RX_msg CAN1_RX; //структура для принятых данных CAN1
static MESSAGE_C2_t MESSAGE_C2 = {0}; //объявление структуры для отправки данных сообщения типа С2
MESSAGE_A_t MESSAGE_A = {0};

uint8_t CAN_flag_RX = RX_NONE;
static uint32_t ID_C2 = 0; 					//CAN заголовок сообщения типа С2
static uint32_t ModuleAddress = 0;	// адрес в кроссе

static uint8_t * buf_RX = MESSAGE_A.RAW;
//uint8_t numb = sizeof(buf_RX)/sizeof(buf_RX[0]);
/* USER CODE END 0 */

CAN_HandleTypeDef hcan;

/* CAN init function */
void MX_CAN_Init(void)
{

  /* USER CODE BEGIN CAN_Init 0 */

  /* USER CODE END CAN_Init 0 */

  /* USER CODE BEGIN CAN_Init 1 */

  /* USER CODE END CAN_Init 1 */
  hcan.Instance = CAN1;
  hcan.Init.Prescaler = 18;
  //hcan.Init.Mode = CAN_MODE_SILENT_LOOPBACK;
//	hcan.Init.Mode = CAN_MODE_SILENT;
	hcan.Init.Mode = CAN_MODE_NORMAL;
  hcan.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan.Init.TimeSeg1 = CAN_BS1_13TQ;
  hcan.Init.TimeSeg2 = CAN_BS2_2TQ;
  hcan.Init.TimeTriggeredMode = DISABLE;
  hcan.Init.AutoBusOff = ENABLE;
  hcan.Init.AutoWakeUp = ENABLE;
  hcan.Init.AutoRetransmission = DISABLE;
  hcan.Init.ReceiveFifoLocked = DISABLE;
  hcan.Init.TransmitFifoPriority = ENABLE;
  if (HAL_CAN_Init(&hcan) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN_Init 2 */
	ModuleAddress = Get_Module_Address(); //получение адреса в кросс-плате
	ID_C2 = MAKE_FRAME_ID(MSG_TYPE_C, (uint8_t)ModuleAddress); //формирование и сохранение ID CAN-сообщения
	
	//---------------------------------------настройка фильтра для FIFO0--------------------------------------//
	CAN_FilterTypeDef can_FIFO_filter;
	
	#ifdef __USE_DBG
		printf ((char *)"FRAME_ID=%x\r\n", ID_C2);
	#endif
	
	//---------------------------------------настройка фильтра для FIFO0--------------------------------------//
	can_FIFO_filter.FilterBank = 0; //номер фильтра
	//can_FIFO_filter.FilterIdHigh =(ID_C2<<5); // старшая часть первого регистра фильтра
	can_FIFO_filter.FilterIdHigh =0x0000;
	can_FIFO_filter.FilterIdLow = 0x0000; //младшая часть первого регистра фильтра
	//can_FIFO_filter.FilterMaskIdHigh = (0x7FF << 5); //старшая часть маски фильтра равна 0b11111111111 (приём только сообщений типа С)
	can_FIFO_filter.FilterMaskIdHigh = 0x0000;
	can_FIFO_filter.FilterMaskIdLow = 0x0000; //младшая часть маски фильтра
	can_FIFO_filter.FilterFIFOAssignment = CAN_RX_FIFO0; //настройка фильтра для приёмного буфера CAN_RX_FIFO0
	can_FIFO_filter.FilterMode = CAN_FILTERMODE_IDMASK; //режим работы фильтра
	can_FIFO_filter.FilterScale =  CAN_FILTERSCALE_32BIT; //размерность фильтра, 32 бита - фильтроваться могут либо стандартные (11 бит) идентификаторы, либо расширенные (29 бит)
	can_FIFO_filter.FilterActivation = ENABLE;
	can_FIFO_filter.SlaveStartFilterBank  = 15;
	if(HAL_CAN_ConfigFilter(&hcan, &can_FIFO_filter) != HAL_OK)
		{Error_Handler();}
		
	//---------------------------------------настройка фильтра для FIFO1--------------------------------------//
	can_FIFO_filter.FilterBank = 16; //номер фильтра
	can_FIFO_filter.FilterIdHigh =0x0000;
	can_FIFO_filter.FilterIdLow = 0x0000; //младшая часть первого регистра фильтра
	can_FIFO_filter.FilterMaskIdHigh = 0x0000; // старшая часть маски фильтра
	can_FIFO_filter.FilterMaskIdLow = 0x0000; //младшая часть маски фильтра
	can_FIFO_filter.FilterFIFOAssignment = CAN_RX_FIFO1; //настройка фильтра для приёмного буфера CAN_RX_FIFO1
	can_FIFO_filter.FilterMode = CAN_FILTERMODE_IDMASK; //режим работы фильтра
	can_FIFO_filter.FilterScale =  CAN_FILTERSCALE_32BIT; //размерность фильтра, 32 бита - фильтроваться могут либо стандартные (11 бит) идентификаторы, либо расширенные (29 бит)
	can_FIFO_filter.FilterActivation = ENABLE;
	
	if(HAL_CAN_ConfigFilter(&hcan, &can_FIFO_filter) != HAL_OK)
		{Error_Handler();}

		
	HAL_CAN_Start(&hcan); 
		
	HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING | CAN_IT_RX_FIFO1_MSG_PENDING 
	| CAN_IT_ERROR | CAN_IT_BUSOFF | CAN_IT_LAST_ERROR_CODE | CAN_IT_ERROR_PASSIVE); 
  /* USER CODE END CAN_Init 2 */

}

void HAL_CAN_MspInit(CAN_HandleTypeDef* canHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspInit 0 */

  /* USER CODE END CAN1_MspInit 0 */
    /* CAN1 clock enable */
    __HAL_RCC_CAN1_CLK_ENABLE();

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**CAN GPIO Configuration
    PB8     ------> CAN_RX
    PB9     ------> CAN_TX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_8;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    __HAL_AFIO_REMAP_CAN1_2();

    /* CAN1 interrupt Init */
    HAL_NVIC_SetPriority(USB_LP_CAN1_RX0_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USB_LP_CAN1_RX0_IRQn);
    HAL_NVIC_SetPriority(CAN1_RX1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(CAN1_RX1_IRQn);
    HAL_NVIC_SetPriority(CAN1_SCE_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(CAN1_SCE_IRQn);
  /* USER CODE BEGIN CAN1_MspInit 1 */
		//---CAN1 interrupt Init 
    HAL_NVIC_SetPriority(USB_LP_CAN1_RX0_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USB_LP_CAN1_RX0_IRQn); //включение прервания по приёму в буффер FIFO0
    HAL_NVIC_SetPriority(CAN1_SCE_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(CAN1_SCE_IRQn); //включение прервания для ошибок  
  /* USER CODE END CAN1_MspInit 1 */
  }
}

void HAL_CAN_MspDeInit(CAN_HandleTypeDef* canHandle)
{

  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspDeInit 0 */

  /* USER CODE END CAN1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_CAN1_CLK_DISABLE();

    /**CAN GPIO Configuration
    PB8     ------> CAN_RX
    PB9     ------> CAN_TX
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_8|GPIO_PIN_9);

    /* CAN1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USB_LP_CAN1_RX0_IRQn);
    HAL_NVIC_DisableIRQ(CAN1_RX1_IRQn);
    HAL_NVIC_DisableIRQ(CAN1_SCE_IRQn);
  /* USER CODE BEGIN CAN1_MspDeInit 1 */

  /* USER CODE END CAN1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
//--------------------------------------коллбэк для буфера приёма FIFO №0--------------------------------------//
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan) 
{
	if(HAL_CAN_GetRxMessage (hcan, CAN_RX_FIFO0, &CAN_RxHeader, buf_RX) == HAL_OK) //если пришло прерывание получения пакета в буфер FIFO0 CAN0
	{
		CAN_flag_RX = RX_UNKNOWN; //установка статуса приёма CAN: принято неиндентифицированное сообщение 
		#ifdef __USE_DBG		
		if ((GET_MSG_TYPE(CAN_RxHeader.StdId) == MSG_TYPE_A1) && (MESSAGE_A.Type1.data_type == MSG_A_DATA_TYPE_TIME1))
		{
			printf ((char *)"FIFO0_id=%u,t0=%u,t1=%u,t2=%u,t3=%u\r\n", CAN_RxHeader.StdId, MESSAGE_A.Type1.time2k_0,
			MESSAGE_A.Type1.time2k_1,MESSAGE_A.Type1.time2k_2,MESSAGE_A.Type1.time2k_3); 
			printf ((char *)"FIFO0_id=%u,time=%u\r\n", CAN_RxHeader.StdId, MESSAGE_A.Type1.time2k);
			printf ((char *)"0b=%u,1b=%u,2b=%u,3b=%u,4b=%u,5b=%u,6b=%u,7b=%u\r\n", MESSAGE_A.RAW[0], MESSAGE_A.RAW[1],  
			MESSAGE_A.RAW[2],MESSAGE_A.RAW[3],MESSAGE_A.RAW[4],MESSAGE_A.RAW[5],MESSAGE_A.RAW[6],MESSAGE_A.RAW[7]);
			CAN_flag_RX = RX_A1;
		}
		#endif
	}	
}

//---------------------------------коллбек ошибки по переполнению Fifo0---------------------------------//
void HAL_CAN_RxFifo0FullCallback(CAN_HandleTypeDef *hcan)
{
	g_MyFlags.CAN_Fail = CAN_ERROR;
	#ifdef __USE_DBG
		printf ((char *)"CAN_FIFO0_Full");
	#endif
}


//--------------------------------------коллбэк для буфера приёма FIFO №1--------------------------------------//
void HAL_CAN_RxFifo1MsgPendingCallback(CAN_HandleTypeDef *hcan) 
{
	if(HAL_CAN_GetRxMessage (hcan, CAN_RX_FIFO1, &CAN_RxHeader, buf_RX) == HAL_OK) //если пришло прерывание получения пакета в буфер FIFO0 CAN0
	{
		CAN_flag_RX = RX_UNKNOWN; //установка статуса приёма CAN: принято неиндентифицированное сообщение 
		if ((GET_MSG_TYPE(CAN_RxHeader.StdId) == MSG_TYPE_A1) && (MESSAGE_A.Type1.data_type==MSG_A_DATA_TYPE_TIME1))
		{	
			//printf ((char *)"FIFO1_id=%u,t0=%u,t1=%u,t2=%u,t3=%u\r\n", CAN_RxHeader.StdId, MESSAGE_A.Type1.time2k_0,
			//MESSAGE_A.Type1.time2k_1,MESSAGE_A.Type1.time2k_2,MESSAGE_A.Type1.time2k_3); 
			printf ((char *)"0b=%u,1b=%u,2b=%u,3b=%u,4b=%u,5b=%u,6b=%u,7b=%u\r\n", MESSAGE_A.RAW[0], MESSAGE_A.RAW[1],  
			MESSAGE_A.RAW[2],MESSAGE_A.RAW[3],MESSAGE_A.RAW[4],MESSAGE_A.RAW[5],MESSAGE_A.RAW[6],MESSAGE_A.RAW[7]);
			CAN_flag_RX = RX_A1;
		}
	}	
}

//---------------------------------коллбек ошибки по переполнению Fifo1---------------------------------//
void HAL_CAN_RxFifo1FullCallback(CAN_HandleTypeDef *hcan)
{
	g_MyFlags.CAN_Fail = CAN_ERROR;
	#ifdef __USE_DBG
		printf ((char *)"CAN_FIFO1_Full");
	#endif
}

//------------------------------------------коллбек ошибок CAN------------------------------------------//
void HAL_CAN_ErrorCallback(CAN_HandleTypeDef *hcan)
{
	uint32_t errorcode = 0;
	if ((errorcode = HAL_CAN_GetError(hcan)) != HAL_OK)
	{
		g_MyFlags.CAN_Fail = CAN_ERROR;
		#ifdef __USE_DBG
			printf ((char *)"CAN1_ERROR=%u\r\n", errorcode);
		#endif
		if ((errorcode == HAL_CAN_ERROR_EPV ) || (errorcode == HAL_CAN_ERROR_BOF )) //есди счётчик ошибок CAN > 128 или установлен флаг BUSOFF
		{
			#ifdef __USE_DBG
				printf ((char *)"CAN1_ERROR > 128\r\n");
			#endif
		}
	}
}	

//--------------------------------------------отправка сообщения С2--------------------------------------------//
uint32_t Send_Message_C2 (void)
{
	uint32_t errorcode; //код ошибки CAN
	
	//my_can_msg = {0, 0};
	MESSAGE_C2.data_type = 0; //младшие 3 бита 1 байта сообщения С2 равны 0
	MESSAGE_C2.module_type = MODULE_TYPE_MKIP; //запись в первый байт сообщения типа модуля-отправителя - МКИП (0х15)
	
	//формирование CAN - заголовка
	CAN_TxHeader.StdId = ID_C2; //ID - стандартный заголовок, тип сообщения С2
	CAN_TxHeader.ExtId = 0;
	CAN_TxHeader.RTR = CAN_RTR_DATA; //тип сообщения (CAN_RTR_Data - передача данных)
	CAN_TxHeader.IDE = CAN_ID_STD;   //формат кадра Standard
	CAN_TxHeader.DLC = 8; //количество байт в сообщении
	CAN_TxHeader.TransmitGlobalTime = 0;
	
	return (errorcode = CAN1_Send_Message (&CAN_TxHeader, MESSAGE_C2.bytes)); //отправка сообщения С2
}

//---------------------------------------ф-я отправки сообщения по CAN1---------------------------------------//
static uint32_t CAN1_Send_Message (CAN_TxHeaderTypeDef * TxHeader, uint8_t * CAN_TxData)
{
	uint32_t errorcode; //код ошибки CAN
	uint32_t uwCounter = 0; 
	uint32_t TxMailbox = 0;//номер почтового ящика для отправки 
	
	while ((HAL_CAN_GetTxMailboxesFreeLevel(&hcan) == 0) && (uwCounter != 0xFFFF)) //ожидание освобождения TxMailbox
		{uwCounter++;} 
	
	if (uwCounter == 0xFFFF)	//если TxMailbox не освободились
		{return (errorcode = HAL_TIMEOUT);} //выход по тайм-ауту
	
	if (READ_BIT (CAN1->TSR, CAN_TSR_TME0)) //проверка бита готовности TxMailbox №0
		{TxMailbox = 0;}
	else
	{
		if (READ_BIT (CAN1->TSR, CAN_TSR_TME1)) //проверка бита готовности TxMailbox №1
			{TxMailbox = 1;}
		else
		{
			if (READ_BIT (CAN1->TSR, CAN_TSR_TME2)) //проверка бита готовности TxMailbox №2
				{TxMailbox = 2;}
			else
				{return (errorcode = HAL_BUSY);} 
		}
	}	
	//Добавление сообщений в свободный Mailbox и активация запроса на передачу  
	return (errorcode = HAL_CAN_AddTxMessage(&hcan, TxHeader, CAN_TxData, &TxMailbox)); 
}
/* USER CODE END 1 */
