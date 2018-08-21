/*
* timer0.c
*
* Created: 7/16/2018 4:16:06 PM
*  Author: EbrahimHamouda
*/

#include "TIMER.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <math.h>
/*
* array of pointers to functions called to notify the user that timer
* has been finished
*/

static  void (*temp_CallBackFunc[3])(void) ;
static uint16 counters[3];

ISR(TIMER0_OVF_vect)
{
	if (counters[0])
	{
		counters[0]--;
	}
	else
	{
		//CLEAR_BIT(MASK_R,MTIMER0);
		(*temp_CallBackFunc[0])();
	}
}

ISR(TIMER1_OVF_vect)
{
	if (counters[1])
	{
		counters[1]--;
	}
	else
	{									//disable this interrupt
		(*temp_CallBackFunc[1])();
	}
}
ISR(TIMER2_OVF_vect)
{
	if (counters[1])
	{
		counters[1]--;
	}
	else
	{												//disable this interrupt
		(*temp_CallBackFunc[1])();
	}
}



void Timer_init(Timer_NumType timer,volatile Time_tick_t time_tick)
{
	volatile uint8 pre_scale;
	switch (time_tick)
	{
		case TICK_MS :
		{
			pre_scale =1;break;
		}
		case TICK_256US :
		{
			pre_scale =1;break;
		}
		case TICK_100MS :
		{
			pre_scale =1;break;
		}
		case TICK_100US :
		{
			pre_scale =1;break;
		}
		default :
		{
			//error
		}
	}
	ACCESS_REG_8BIT((timer+TCCBASE)) |= (pre_scale)<<0;
	pre_scale++;
}
void Timer_trigger(Timer_NumType timer,uint16 Num_Tikes)
{
	switch(timer)
	{
		case  TIMER0:
		{		// check if timer initialized
			while(Num_Tikes)
			{
				// timer should start from zero
				if (BIT_IS_SET(FLAG_R,FTIMER0))						// check flage according to timer
				{
					Num_Tikes--;
					SET_BIT(FLAG_R,FTIMER0);
				}
			}
			break;
		}
		case  TIMER1:
		{
			while(Num_Tikes)
			{
				if (BIT_IS_SET(FLAG_R,FTIMER1))						// check flage according to timer
				{
					Num_Tikes--;
					SET_BIT(FLAG_R,FTIMER1);
				}
			}
			break;
		}
		case  TIMER2:
		{
			while(Num_Tikes)
			{
				if (BIT_IS_SET(FLAG_R,FTIMER2))						// check flage according to timer
				{
					Num_Tikes--;
					SET_BIT(FLAG_R,FTIMER2);
				}
			}
			break;
		}
		default:
		{
			//errot
		}
	}
}

void Timer_triggerInterrupt(Timer_NumType timer,uint16 Num_Tikes,void (*call_back)(void))
{
	switch(timer)
	{
		case TIMER0 :
		{
			temp_CallBackFunc[0] = call_back;
			counters[0]          = Num_Tikes;
			SET_BIT(MASK_R,MTIMER0);break;
		}
		case TIMER1 :
		{
			temp_CallBackFunc[1] = call_back;
			counters[1]          = Num_Tikes;
			SET_BIT(MASK_R,MTIMER1);break;
		}
		case TIMER2 :
		{
			temp_CallBackFunc[2] = call_back;
			counters[2]          = Num_Tikes;
			SET_BIT(MASK_R,MTIMER2);break;
		}
		default:
		{
			//error
		}
	}
	
}



