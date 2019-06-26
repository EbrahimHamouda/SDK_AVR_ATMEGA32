/*
 * RTCDS1307.h
 *
 * Created: 4/29/2019 4:51:39 PM
 *  Author: ebrah
 */ 


#ifndef RTCDS1307_H_
#define RTCDS1307_H_
#include "F:\embedded\Work_space\2_Drivers_atmega32\SDK_AVR_ATMEGA32\HAL\I2C\I2C.h"
#include <common\ebra_common.h>

typedef struct
{
	uint8_t sec;
	uint8_t min;
	uint8_t hour;
	uint8_t weekDay;
	uint8_t date;
	uint8_t month;
	uint8_t year;
} rtc_t;

void RTC_Init(void);
void RTC_SetDateTime(rtc_t *rtc);
void RTC_GetDateTime(rtc_t *rtc);

#endif /* RTCDS1307_H_ */