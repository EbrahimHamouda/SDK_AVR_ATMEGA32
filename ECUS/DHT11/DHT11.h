/*
* DHT11.h
*
* Created: 4/27/2019 8:42:31 PM
*  Author: ebrah
*/


#ifndef DHT11_H_
#define DHT11_H_

#include "F:\embedded\Work_space\2_Drivers_atmega32\SDK_AVR_ATMEGA32\HAL\GPIO\GPIO.h"
#include <common\ebra_common.h>
#include <avr/io.h>

#define DHT11_PIN   (0)
#define D_PORT      DDRB
#define O_PORT		PORTB
#define I_PORT      PINB

typedef struct
{
	uint8 I_RH;
	uint8 D_RH;
	uint8 I_Temp;
	uint8 D_Temp;
	uint8 CheckSum;
} DHT11_t;

void DHT11_RequestData();
void DHT11_GetResponse();
void DHT11_ReceiveData(DHT11_t*);

#endif /* DHT11_H_ */