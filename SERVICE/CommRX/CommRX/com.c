/*
* com.c
*
*  Created on: Aug 4, 2018
*      Author: EbrahimHamouda
*/

#include "com.h"

typedef enum
{
	COMM_UNLOCK_DATA,
	COMM_LOCKE_DDATA,
} Data_LockType;

static uint8		  Rx_FrameBuffer[FRAME__SIZE];
static RX_StateType   RX_State;
static Data_LockType  Rx_DataLock ;
static uint16		  RX_Buffer_Index;
static bool_t		  RX_FlageDataReciving ;
static uint8*		  ptr_header;
static void (*RX_CallBack_ReciveComplete)(uint8* Rx_data);

void RX_CommFree(void)
{
	Rx_DataLock = COMM_UNLOCK_DATA;
	RX_State = IDLE;
	RX_Buffer_Index = 0;
	RX_FlageDataReciving =0;
	ptr_header=NULL;
}

static bool_t RX_check_header()
{
	uint8 i,ret_val=1;
	uint8* temp_ptr=(((RX_FrameStruct*)Rx_FrameBuffer)->header);
	for (i=0;i<HEADER_SIZE;i++)
	{	
		if (*ptr_header++ !=  *temp_ptr++ )
		{
			ret_val = 0;
			break;
		}
	}
	return ret_val;
}


static void HardWare_CallBack()
{
	RX_FlageDataReciving  = 1;								    //set flage to notify the comm  

	if ((!Rx_DataLock) && RX_Buffer_Index < FRAME__SIZE)			//check lock and size 
	{
		Rx_FrameBuffer[RX_Buffer_Index++] = Uart_ReadByte();		//store in buffer
	}
}

void Comm_RxInit(void (*ptr_Fu_ProcessDataRX)(uint8* Rx_data),uint8 User_header[HEADER_SIZE])
{
	RX_CommFree();
	Uart_init();
	Uart_RxInterruptEnable(HardWare_CallBack);
	RX_CallBack_ReciveComplete = ptr_Fu_ProcessDataRX;
	ptr_header = User_header;
}

void RX_com_dispatch() 
{
	if (RX_FlageDataReciving )
	{
		switch (RX_State)
		{
			case IDLE:
			{
				if (RX_Buffer_Index > HEADER_SIZE)
				{
					RX_State = CHEACK_HEADER;		
				}
				break;
			}
			case CHEACK_HEADER: 
			{
				if (RX_check_header()) 
				{	
					RX_State = RECEIVE_BYTE;
				}
				else
				{
					//ERROR 
					RX_State = IDLE;
				}
				break;
			}
			case RECEIVE_BYTE: 
			{
				if (RX_Buffer_Index < FRAME__SIZE) 
				{ 
					RX_State = RECEIVE_BYTE;
				}
				else if (RX_Buffer_Index == FRAME__SIZE)
				{
					RX_State = RECEIVE_COMPLETE;
				}
				break;
			}
			case RECEIVE_COMPLETE: 
			{
				Rx_DataLock = COMM_LOCKE_DDATA;							//Lokk data 
				RX_CallBack_ReciveComplete((((RX_FrameStruct*)Rx_FrameBuffer)->data));
				break;
			}
			default:
			{
				break;
			}
		}
	}
}

