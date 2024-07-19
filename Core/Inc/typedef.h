
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
typedef enum { RX_NONE = 0, RX_C1, RX_OWN_C2, RX_UNKNOWN}  TRxResult; //������� ���������� ��������� CAN

//--------------------------------------------------------------------
typedef union 
{
	struct
	{
		unsigned int data_type		: 3; 
		unsigned int module_type	: 5; //��� ������ �����������
		unsigned int 							: 4;
		unsigned int state				: 4; 
	};

	uint8_t bytes[ 8 ];

}	CAN_MSG_TYPE_C ; //��������� ��������� ���� �

//--------------------------------------------------------------------
typedef struct
{
	uint8_t flag_RX;
	uint8_t RxData[8];
}
CAN_RX_msg; //��������� � ������� ��������� ����� CAN

//--------------------------------------------------------------------
typedef union _MY_FLAGS
{
	unsigned int Value;
	struct //������� ����
	{
		unsigned CAN_Fail				: 1;	//��� unsigned, ����� ���� 1 ���, ������ CAN	( ��� ������ ����������� ��������� C2 )
		unsigned UPS_state				: 4; //��� unsigned, ����� ���� 4 ����, ������ RS-232
	};
}TMyFlags;

// Defines ----------------------------------------------------------------------//

// Private variables -----------------------------------------------------------//
	
#ifdef __cplusplus
}
#endif

#endif 

