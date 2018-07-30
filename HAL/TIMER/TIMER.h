/*
 * TIMER.h
 *
 * Created: 7/30/2018 3:00:18 PM
 *  Author: ahmed
 */ 


#ifndef TIMER_H_
#define TIMER_H_

typedef unsigned int Time_t;

typedef enum timnum{
	TIMER0,
	TIMER1,
	TIMER2,	
}Timer_Num_t;

/*
	Add your APIs.
*/

void Timer_init(Timer_Num_t timer,Time_t time);

#endif /* TIMER_H_ */