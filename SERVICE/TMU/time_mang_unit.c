/*
* time_mang_unit.c
*
* Created: 7/14/2018 11:19:59 AM
*  Author: ebrah
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include "time_mang_unit.h"


static Struct_EventConfg_t Event_ConfgBuffer[MAX_EVENTS] ;
static uint32 Event_Remainder[MAX_EVENTS];
static uint8 S_handler=0;

ISR(TIMER0_OVF_vect)
{
	volatile uint8 i;
	
	for(i=0;i<MAX_EVENTS;i++)
	{
		if ((Event_ConfgBuffer[i].Event_Stutes)&&(Event_Remainder[i]!=0))
		{
			(Event_Remainder[i])--;
		}
	}
	TCNT0=249;
}

void TMU_init(Enum_TimrNum_t timr_x ,Enum_EventResloution_t resolution)
{
	// i will work with only this confg
	// to do switch for timer and resolution
	TIMSK |= 1<<0;	//enable interrupt for timer
	TCCR0 |= 3<<0;	// TCCR0 for edjust the resolution
	TCNT0 =249;
	S_handler=1;
}

void Creat_NewEvent(Struct_EventConfg_t* P_Event,uint8* P_Userhandler) // ptr _confg of TMU to store confg
{
	Event_ConfgBuffer[S_handler].peroid				   = P_Event->peroid;
	Event_ConfgBuffer[S_handler].Event_Stutes		   = P_Event->Event_Stutes;										    // to store period to be reloaded into event_remainder
	Event_Remainder[S_handler]						   = P_Event->peroid;											// initalize remainder with period
	Event_ConfgBuffer[S_handler].event_type            = P_Event->event_type;						    // store event type
	Event_ConfgBuffer[S_handler].Event_TriggerFunction =P_Event->Event_TriggerFunction;   	//store call back fun to trigger user_event
	*P_Userhandler = S_handler++;															// increament handler and change user handler with pervious value
}

void creat_oneHandlerEvent(Struct_EventConfg_t* P_Event)
{
	Event_ConfgBuffer[0].peroid				   = P_Event->peroid;
	Event_ConfgBuffer[0].Event_Stutes		   = P_Event->Event_Stutes;			    // to store period to be reloaded into event_remainder
	Event_Remainder[0]						   = P_Event->peroid;				    // initalize remainder with period
	Event_ConfgBuffer[0].event_type            = P_Event->event_type;				// store event type
	Event_ConfgBuffer[0].Event_TriggerFunction =P_Event->Event_TriggerFunction;   	//store call back fun to trigger user_event
}
void end_event(uint8 handler)
{
	Event_ConfgBuffer[handler].Event_Stutes = 0 ;
}

void TMU_Disable()
{
	TIMSK &= ~(1<<0);	//disable interrupt for timer
}

void TMU_Enable()
{
	TIMSK |= (1<<0);	//Enable interrupt for timer
}

void TMU_Dispatcher()
{
	uint8 i;
	for(i=0;i<MAX_EVENTS;i++) // loop for to check events time
	{
		if (Event_ConfgBuffer[i].Event_Stutes == 1) // check if event working or ended
		{
			if (Event_Remainder[i]== 0) // check the remainder if reach zero
			{
				(Event_ConfgBuffer[i].Event_TriggerFunction)();
				if (Event_ConfgBuffer[i].event_type ==ONE_SHOOT)
				{
					end_event(i);
				}
				Event_Remainder[i] = Event_ConfgBuffer[i].peroid; // reload the period in remainder again
			}
		}
	}
}
