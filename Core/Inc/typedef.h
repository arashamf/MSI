
#ifndef __TYPEDEF_H__
#define __TYPEDEF_H__

#ifdef __cplusplus
extern "C" {
#endif

// Includes ----------------------------------------------------------------------//
#include "main.h"

// Exported types ---------------------------------------------------------------//

typedef struct 
{
	GPIO_TypeDef * PORTx;
	uint32_t PINx;		
}	TPortPin;

//--------------------------------------------------------------------
typedef enum { RX_NONE = 0, RX_A1, RX_C1, RX_OWN_C2, RX_UNKNOWN}  TRxResult; //������� ���������� ��������� CAN

//--------------------------------------------------------------------
typedef union 
{
	struct
	{
		unsigned int data_type		: 3; 
		unsigned int module_type	: 5; //��� ������ �����������
		unsigned int 							: 4;
		unsigned int 							: 4; 
	};

	uint8_t bytes[ 8 ];

}	MESSAGE_C2_t; //��������� ��������� ���� �

//------------------------------------------------------------------
//#pragma scalar_storage_order big-endian //��������� ������� big endian
#pragma pack(1) //pack ����� ��������� ����� pragma ��������� ������������� ������, 1 - ������������ �� �����
typedef union
{
	uint8_t RAW[8];
	struct
	{
			uint8_t data_type			: 3;
			uint8_t module_type		: 5;
			union
			{
				struct 
				{
					uint8_t time2k_0   	 	: 8;
					uint8_t time2k_1   	 	: 8;
					uint8_t time2k_2    	: 8;
					uint8_t time2k_3    	: 8;
				};
				unsigned time2k;
			};
			int8_t ls_tai					: 8; 	// TAI leap seconds (TAI-UTC)
			uint8_t moscow_tz			: 3;	// � �����
			uint8_t 							: 3;
			uint8_t ls_59					: 1;
			uint8_t ls_61					: 1;				
			int8_t local_tz				: 8;	// � 15 ��� ����������
	}Type1;
}MESSAGE_A_t;
#pragma pack()
//--------------------------------------------------------------------
typedef union _MY_FLAGS
{
	uint32_t Value;
	struct 
	{
		unsigned CAN_Fail					: 1;	//��� unsigned, ����� ���� 1 ���, ������ CAN	( ��� ������ ����������� ��������� C2 )
		unsigned time_error				: 1; //��� unsigned, ����� ���� 4 ����, ������ RS-232
	};
}TMyFlags;

// Defines ----------------------------------------------------------------------//


// Private variables -----------------------------------------------------------//

#ifdef __cplusplus
}
#endif

#endif 

