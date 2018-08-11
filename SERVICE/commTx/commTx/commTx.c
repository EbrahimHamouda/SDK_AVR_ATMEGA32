/*
* commTx.c
*
* Created: 8/9/2018 1:19:32 PM
*  Author: ebrahim
*/

#include "commTx.h"

static void (*SCall_back_commtx_compelete)();
static uint8			*Sptr_Data2Sent;
static uint16			SN_Byte2Sent;
static uint16			Scounter;
static bool_t			flage_Tx_Sending;


static void HardWare_CallBack()
{
	if (Scounter < SN_Byte2Sent)
	{
		Uart_SendByte(Sptr_Data2Sent[Scounter]);
		Scounter++;
	}
}

static void comm_TxSendCompelete()
{
	flage_Tx_Sending = 0;
	SCall_back_commtx_compelete();
}

void comm_TxRest()
{
	Scounter			= 0;
	flage_Tx_Sending    = 0;
}

void comm_TxInit(CommTx_DataCfgType* ptr_struct)
{
	comm_TxRest();													// rest static variables
	Uart_init();													// init the state
	Uart_TxInterruptEnable(HardWare_CallBack);
	
	SCall_back_commtx_compelete = ptr_struct->Call_back_commtx_compelete;  //save Data in the static variables
	Sptr_Data2Sent			    = ptr_struct->ptr_Data2Sent;
	SN_Byte2Sent				= ptr_struct->N_Byte2Sent;
	
	flage_Tx_Sending =1;												// set flage to work dispatch 
}

void comm_TxDisspatch()
{
	if (flage_Tx_Sending)
	{
		if (Scounter == SN_Byte2Sent)
		{
			comm_TxSendCompelete();
		}
	}
}



