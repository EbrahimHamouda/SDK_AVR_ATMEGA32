/*
* DHT11.c
*
* Created: 4/27/2019 8:45:33 PM
*  Author: ebrah
*/
#include "DHT11.h"
#include <util/delay.h>


void DHT11_RequestData()				/* Microcontroller send start pulse/DHT11_RequestData */
{
	D_PORT |= (1<<DHT11_PIN);
	O_PORT &= ~(1<<DHT11_PIN);	/* set to low pin */
	_delay_ms(20);			/* wait for 20ms */
	O_PORT |= (1<<DHT11_PIN);	/* set to high pin */
}

void DHT11_GetResponse()				/* receive DHT11_GetResponse from DHT11 */
{
	D_PORT &= ~(1<<DHT11_PIN);
	while(I_PORT & (1<<DHT11_PIN));
	while((I_PORT & (1<<DHT11_PIN))==0);
	while(I_PORT & (1<<DHT11_PIN));
}

static uint8_t _ReceiveData()			/* receive data */
{
	uint8 c;
	for (int q=0; q<8; q++)
	{
		while((I_PORT & (1<<DHT11_PIN)) == 0);  /* check received bit 0 or 1 */
		_delay_us(30);
		if(I_PORT & (1<<DHT11_PIN))/* if high pulse is greater than 30ms */
		c = (c<<1)|(0x01);	/* then its logic HIGH */
		else			/* otherwise its logic LOW */
		c = (c<<1);
		while(I_PORT & (1<<DHT11_PIN));
	}
	return c;
}

void DHT11_ReceiveData(DHT11_t* ptr_DHT11)
{
	ptr_DHT11->I_RH=_ReceiveData();
	ptr_DHT11->D_RH=_ReceiveData();
	ptr_DHT11->I_Temp=_ReceiveData();
	ptr_DHT11->D_Temp=_ReceiveData();
	ptr_DHT11->CheckSum=_ReceiveData();
}