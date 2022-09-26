

#include "GPIO.h"

void BunchPins_Write(uint8* arr,uint8 N,enum_PinValue_t type)
{
	uint8 i;
	for (i=0;i<N;i++)
	{
		digitalWrite(arr[i],type);
	}
}

void gpio_uart_cng()
{
	SetPinDirection(D0,SET_PIN_IN); // uart RX
	SetPinDirection(D1,SET_PIN_OUT); // uart TX
}

void gpio_spi_cng_master()
{
	SetPinDirection(B4,SET_PIN_OUT);     //SS
	SetPinDirection(B5,SET_PIN_OUT);     //MOSi
	SetPinDirection(B6,SET_PIN_IN);		 //MISO
	SetPinDirection(B7,SET_PIN_OUT);	 //SCK
}
