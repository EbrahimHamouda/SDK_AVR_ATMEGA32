/*
* external_interrupt.c
*
* Created: 7/8/2018 5:01:14 PM
*  Author: ebrahim
*/

#include "external_interrupt.h"
#include <avr/interrupt.h>
// SOLID DATA
#define GLOBAL_INT_ENABLE sei()
#define EXT_INT_ENABLE(X) (GICR |=(1 << X))
#define EXT_INT_DISABLE(X) (GICR &=(~(1 << X)))


static void (*Call_backFromExtISR[3]) (void); // arry of pointers to funcation 


ISR(INT0_vect)//interrupt service routine when there is a change in logic level
{
	Call_backFromExtISR[0]();
}

ISR(INT1_vect)//interrupt service routine when there is a change in logic level
{
	Call_backFromExtISR[1]();
}

ISR(INT2_vect)//interrupt service routine when there is a change in logic level
{
	Call_backFromExtISR[2]();
}


void extrnal_int_init(enum_extenal_int_n_t X,enum_external_int_type_t int_type,void (*NotifyWhenISR)())
{
	switch (X)
	{
		case EXT_INT0 :
		{
			DDRD  &= ~(1<<2);
			MCUCR &= 0b11111100 ;
			MCUCR |= int_type << 0;
			Call_backFromExtISR[0]=NotifyWhenISR;
			break;
		}
		case EXT_INT1 :
		{
			DDRD  &= ~(1<<3);
			MCUCR &= 0b11110011;
			MCUCR |= int_type<<2;
			Call_backFromExtISR[1]=NotifyWhenISR;
			break;
		}
		case EXT_INT2 :
		{
			DDRB &= ~(1<<2);
			if(int_type==INT_FALLING_EDGE)
			{
				MCUCSR &= ~(1<<6);
			}
			else if(int_type==INT_RISING_EDGE)
			{
				MCUCSR |= (1<<6);
			}
			else
			{
				//error
			}
			Call_backFromExtISR[2]=NotifyWhenISR;
			break;
		}
	}	
}

void Enable_EXT_INT(uint8 X)
{
	EXT_INT_ENABLE(X);
}

void Disable_EXT_INT(uint8 X)
{
	EXT_INT_DISABLE(X);
}
