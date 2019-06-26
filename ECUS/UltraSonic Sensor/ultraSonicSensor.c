/*
* ultraSonicSensor.c
*
* Created: 4/27/2019 10:17:34 AM
*  Author: ebrah
*/

#include <avr/interrupt.h>
#include "ultraSonicSensor.h"

// use timer 1 to capture the duration .

static volatile uint16 pulse = 0;//interger  to access all though the program
static volatile uint8 i = 0;// interger  to access all though the program
static volatile bool_t flag=0;

void Call_meFromISR(void)
{
	if (i==1)//when logic from HIGH to LOW
	{
		pulse=TCNT1;//count memory is updated to integer
		flag=1;
	}
	if (i==0)//when logic change from LOW to HIGH
	{
		i=1;
		TCNT1=0;
	}
}

void UltraSonic_Init(UltraSonic_t* ptr_USconfg)
{
	// confg Timer INT0
	// no need confg we use the dafult no presclare ...

	SetPinDirection((ptr_USconfg->Trigger),OUTPUT);
	extrnal_int_init(ptr_USconfg->Echo,INT_ANY_LOGIC_CHANGE,Call_meFromISR);
}

uint16 ultraSonic_Read(UltraSonic_t* ptr_USconfg)
{
	i=0;
	TCCR1B|=(1<<CS10);//enabling counter
	Enable_EXT_INT(ptr_USconfg->Echo);
	digitalWrite((ptr_USconfg->Trigger),SET_VALUE_HIGH);
	_delay_us(15);///triggering the sensor for 15usec
	digitalWrite((ptr_USconfg->Trigger),SET_VALUE_LOW);
	while(!flag); // stay until finish
	flag=0;
	Disable_EXT_INT(ptr_USconfg->Echo);
	TCCR1B=0;
	return (pulse/58);  //getting the distance based on formula on introduction
}