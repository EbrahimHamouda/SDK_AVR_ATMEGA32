/*
* Adc.c
*
* Created: 8/14/2018 2:16:53 PM
* Author : ebrahim
*/

#include <avr/io.h>
#define F_CPU 1000000UL
#include "ADC.h"
#include "lcd.h"
#include "GPIO.h"
#include <util/delay.h>	
#include <avr/interrupt.h>

void my_fun(uint16 val)
{
	PORTC = (val/2.5)*1023;
	
}

int main(void)
{
	DDRA = 0;
	DDRC = 0xff;
	DDRD = 0xff;
	sei();
	adc_init(INTERNAL_VREF,FREE_RUNNING_MODE,CLK_ADC_DIV_128);
	
	while (1)
	{
		adc_IntEnable(my_fun,CHANNEL0);
	}
}

