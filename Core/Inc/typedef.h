
#ifndef __TYPEDEF_H__
#define __TYPEDEF_H__

#ifdef __cplusplus
extern "C" {
#endif

// Includes ----------------------------------------------------------------------//"
#include "main.h"

// Exported types ---------------------------------------------------------------/
typedef struct 
{
	GPIO_TypeDef * PORTx;
	uint32_t PINx;		
}	TPortPin;

//--------------------------------------------------------------------
typedef enum { RX_NONE = 0, RX_C1, RX_OWN_C2, RX_UNKNOWN}  TRxResult; //статусы полученных сообщений CAN

//--------------------------------------------------------------------
typedef union 
{
	struct
	{
		unsigned int data_type		: 3; 
		unsigned int module_type	: 5; //тип модуля отправителя
		unsigned int 							: 4;
		unsigned int state				: 4; 
	};

	uint8_t bytes[ 8 ];

}	CAN_MSG_TYPE_C ; //структура сообщения типа С

//--------------------------------------------------------------------
typedef struct
{
	uint8_t flag_RX;
	uint8_t RxData[8];
}
CAN_RX_msg; //структура с данными принятого кадра CAN

//--------------------------------------------------------------------
typedef union _MY_FLAGS
{
	unsigned int Value;
	struct //Битовые поля
	{
		unsigned CAN_Fail				: 1;	//тип unsigned, длина поля 1 бит, статус CAN	( нет приема собственных сообщений C2 )
		unsigned UPS_state				: 4; //тип unsigned, длина поля 4 бита, статус RS-232
	};
}TMyFlags;

// Defines ----------------------------------------------------------------------//

// Private variables -----------------------------------------------------------//
	
#ifdef __cplusplus
}
#endif

#endif 

