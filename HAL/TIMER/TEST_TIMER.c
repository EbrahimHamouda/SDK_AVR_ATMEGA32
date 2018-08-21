/*
* timer_Device_Driver.c
*
* Created: 7/15/2018 10:03:00 AM
* Author : EbrahimHamouda
*/

#include <avr/io.h>
#include "TIMER.h"
#include <avr/interrupt.h>
void my_fi()
{
	PORTB ^= (1<<0);
}

int main(void)
{
	volatile uint8 x=0;
	Timer_init(TIMER0,TICK_256US);
	DDRB |= 1<<0;
	Timer_triggerInterrupt(TIMER0,1000,my_fi);
	sei();
	while (1)
	{
		x++;
	}
}

