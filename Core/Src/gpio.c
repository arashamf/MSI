/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
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
#include "gpio.h"

/* USER CODE BEGIN 0 */
#include "typedef.h"
// Variables -------------------------------------------------------------------//
const TPortPin check_pins[] = 
{
	{	OS1_GPIO_Port, 	OS1_Pin 	},
	{	OS2_GPIO_Port, 	OS2_Pin 	},
	{	OS3_GPIO_Port, 	OS3_Pin  	},
	{	OS4_GPIO_Port, 	OS4_Pin  	},
};

//------------------------------------------------------------------------------//
const TPortPin addr_pins[] = 		
{
	{ ADDR0_GPIO_Port, ADDR0_Pin },
	{ ADDR1_GPIO_Port, ADDR1_Pin },
	{	ADDR2_GPIO_Port, ADDR2_Pin },
	{ ADDR3_GPIO_Port, ADDR3_Pin },
	{	ADDR4_GPIO_Port, ADDR4_Pin }
};

uint8_t number_check_pins = sizeof(check_pins)/sizeof (check_pins[0]); //количество проверяемых каналов
uint8_t number_addr_pins = sizeof(addr_pins)/sizeof (addr_pins[0]); //количество проверяемых каналов
/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOD);
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA);
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOB);

  /**/
  LL_GPIO_ResetOutputPin(GPIOB, OPT1_Pin|LED2_Pin|LED1_Pin|OPT2_Pin
                          |OPT3_Pin|OPT4_Pin);

  /**/
  LL_GPIO_ResetOutputPin(GPIOA, RELAY1_Pin|RELAY2_Pin|RELAY3_Pin|RELAY4_Pin);

  /**/
  GPIO_InitStruct.Pin = ADDR0_Pin|ADDR1_Pin|ADDR2_Pin|ADDR3_Pin
                          |ADDR4_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = OPT1_Pin|LED2_Pin|LED1_Pin|OPT2_Pin
                          |OPT3_Pin|OPT4_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = OS1_Pin|OS2_Pin|OS3_Pin|OS4_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_FLOATING;
  LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = RELAY1_Pin|RELAY2_Pin|RELAY3_Pin|RELAY4_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 2 */
//-----------------------------------------------------------------------------------//
int8_t Get_Status_Pins(void)
{
	uint8_t count = 0;
	int8_t addr = 0;
	uint8_t number_pins = 0;
	

	for(count = 0 ; count < number_pins; count++ )
	{
		addr |= ((LL_GPIO_IsInputPinSet(check_pins[count].PORTx, check_pins[count].PINx )) << count); 
	}
	#ifdef __USE_DBG
		printf ("pins_OS=%d\r\n", addr);
	#endif		 	 
	
return addr;
}

//-----------------------------------------------------------------------------------------------------//
uint32_t Get_Module_Address( void )
{
  uint8_t count;
  uint32_t result = 0;

	for( count = 0 ; count < number_addr_pins; count++ ) //cчитывание состояния пинов на кросс плате
	{
		result |= (!(LL_GPIO_IsInputPinSet (addr_pins[count].PORTx, addr_pins[count].PINx)) << count); //инверсия
		
		/*if ((!LL_GPIO_IsInputPinSet(addr_pins[count].PORTx, addr_pins[count].PINx)) == 1)
			printf ("addr_pins[%u]=1\r\n", count);
		else
			printf ("addr_pins[%u]=0\r\n", count);*/
	}

	#ifdef __USE_DBG
		printf ("ModuleAddr=%u\r\n", result);
	#endif
	
	return result;
}
/* USER CODE END 2 */
