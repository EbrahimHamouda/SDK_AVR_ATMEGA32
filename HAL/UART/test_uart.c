/*
 * uart_test.c
 *
 * Created: 8/5/2018 12:43:20 PM
 * Author : ebrah
 */ 


#include "USART.h"
#include <util/delay.h>
#include <avr/interrupt.h>
static uint8 i=65;

void my_fun()
{
	Uart_SendByte(i++);
}

void my_fun2()
{
	PORTB = Uart_ReadByte();  
}

int main(void)
{
	DDRB=0xff;
	DDRD |= 1<<1;
	sei();
    Uart_init();
	Uart_RxInterruptEnable(my_fun2);
	Uart_TxInterruptEnable(my_fun);
	
    while (1) 
    {
		CLEAR_BIT(0x5f,7);   // DISABLE GLOBAL INTERRUPT 
		_delay_ms(100);      // ENABLE GLOBAL INTERRUPT 
		SET_BIT(0x5f,7);
    }
}

