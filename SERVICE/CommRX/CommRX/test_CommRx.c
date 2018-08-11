/*
 * uart_test.c
 *
 * Created: 8/5/2018 12:43:20 PM
 * Author : ebrahim
 */ 


#include "com.h"
#define F_CPU 1000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include "avr/iom32.h"

static uint8 myheader[3]={1,2,3};
	
void my_fun(uint8* mydata)
{
	uint8 i;
	for (i=0;i<RX_DATA_MAX_SIZE;i++)
	{
		Uart_SendByte(mydata[i]);
	}
	 RX_CommFree();
}

int main(void)
{
	DDRB=0xff;
	DDRD |= 1<<1;
	sei();
    Comm_RxInit(my_fun,myheader);
    while (1) 
    {
		RX_com_dispatch();
    }
}

