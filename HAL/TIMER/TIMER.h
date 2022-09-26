/*
* TIMER.h
*
* Created: 7/30/2018 3:00:18 PM
*  Author: EbrahimHamouda
*/


#ifndef TIMER_H_
#define TIMER_H_
#include "ebra_common.h"
#include "hw_timer.h"
#define F_CPU_MHZ 40
//time delay = time_tick * num_ticks;
typedef enum timnum{
	TIMER0 = TCC0,
	TIMER1 = TCC1,
	TIMER2 = TCC2,
} Timer_NumType;

typedef enum
{
	TICK_MS,
	TICK_256US,
	TICK_100MS,
	TICK_100US,	
} Time_tick_t;


void Timer_init(Timer_NumType timer,volatile Time_tick_t time_tick);
void Timer_trigger(Timer_NumType timer,uint16 Num_Tikes);
void Timer_triggerInterrupt(Timer_NumType timer,uint16 Num_Tikes,void (*call_back)(void));
#endif /* TIMER_H_ */
