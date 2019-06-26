/*
 * time_mang_unit.h
 *
 * Created: 7/14/2018 8:08:13 AM
 *  Author: ebrah
 */ 

#ifndef TIME_MANG_UNIT_H_
#define TIME_MANG_UNIT_H_

#include <common/ebra_common.h>
#define  MAX_EVENTS 3

typedef void (*CallBack_t)(void);	// call back to fun take Nothing return Noting

typedef enum
{
	ONE_SHOOT,
	PEROIDEC,
} Enum_EventType_t ;

typedef struct 
{
	uint32 peroid; // if it happen always so how much between event occur to next 
	Enum_EventType_t event_type; // the type of event happen one time or always
	bool_t Event_Stutes;
	CallBack_t Event_TriggerFunction; // the call back assigned 
} Struct_EventConfg_t;

// Give user avaliablity to change timer and resolution in run time 
typedef enum
{
	_1MS,  
// to add in future more resolution 
} Enum_EventResloution_t;

typedef enum
{
	TMR0,
// to add in future more hardware timer 
} Enum_TimrNum_t;

// to init the hardware "timer and clk"
void TMU_init(Enum_TimrNum_t timr_x ,Enum_EventResloution_t resolution);

//to creat new event and take pointer to struct 
void Creat_NewEvent(Struct_EventConfg_t* P_Event,uint8* P_Userhandler);

//to terminate an event 
void end_event(uint8 handler);

// called in inifinty loop to check if time to fire event or not 
void TMU_Dispatcher();

//called to disable ISR from hardware
void TMU_Disable();

//called to Enable ISR from hardware
void TMU_Enable();

// create spechial event which it's handler is 0 and can't be periodic  
void creat_oneHandlerEvent(Struct_EventConfg_t* P_Event);

#endif /* TIME_MANG_UNIT_H_ */