/*
 * ultraSonicSensor.h
 *
 * Created: 4/27/2019 10:18:09 AM
 *  Author: ebrah
 */ 


#ifndef ULTRASONICSENSOR_H_
#define ULTRASONICSENSOR_H_
#include "F:\embedded\Work_space\2_Drivers_atmega32\SDK_AVR_ATMEGA32\HAL\GPIO\GPIO.h"
#include "F:\embedded\Work_space\2_Drivers_atmega32\SDK_AVR_ATMEGA32\HAL\GPIO\external_interrupt.h"
#include <util\delay.h>
#include <common\ebra_common.h>

typedef struct
{
	enum_PinsNum_t Trigger;
	enum_PinsNum_t Echo;
} UltraSonic_t;

void UltraSonic_Init(UltraSonic_t* ptr_USconfg);
uint16 ultraSonic_Read(UltraSonic_t* ptr_USconfg);

#endif /* ULTRASONICSENSOR_H_ */