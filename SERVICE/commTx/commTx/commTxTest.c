/*
* commTx.c
*
* Created: 8/9/2018 12:57:13 PM
* Author : ebrahim
*/


#include <avr/io.h>
#include <avr/interrupt.h>
#include "commTx.h"

#define N_Data 1500

void send_CompeletNotifyme()
{
	Uart_SendByte('o');
	Uart_SendByte('k');
}


static uint8  Ascii[N_Data];

int main(void)
{
	uint16 i;
	for (i=0;i<N_Data;i++)
	{
		Ascii[i]=i;
	}

	CommTx_DataCfgType test_Data={send_CompeletNotifyme,Ascii,N_Data};
	
	sei();
	DDRD |= 1<<1;
	comm_TxInit(&test_Data);
	
	while (1)
	{
		comm_TxDisspatch();
	}
	
}

