/*
* GPIO.c
*
* Created: 
*   Author: EbrahimHamouda
*/

#include "GPIO.h"

void SetPinDirection(enum_PinsNum_t Pin,enum_PinDirection_t Direction)
{
	if(Pin<8)                  //PORTA
	{
		if (Direction==SET_PIN_IN)
		{
			CLEAR_BIT((BASE_A+GPIODIR),(Pin));
		}
		else
		{
			SET_BIT((BASE_A+GPIODIR),(Pin));
		}
	}
	else if((Pin<16)&&(Pin>=8)) //PORTB
	{
		Pin-=8;
		if (Direction==SET_PIN_IN)
		{
			CLEAR_BIT((BASE_B+GPIODIR),(Pin));
		}
		else
		{
			SET_BIT((BASE_B+GPIODIR),(Pin));
		}
	}
	else if ((Pin<24)&&(Pin>=16)) //PORTC
	{
		Pin-=16;
		if (Direction==SET_PIN_IN)
		{
			CLEAR_BIT((BASE_C+GPIODIR),(Pin));
		}
		else
		{
			SET_BIT((BASE_C+GPIODIR),(Pin));
		}
	}
	else if ((Pin<32)&&(Pin>=24)) //PORTD
	{
		Pin-=24;
		if (Direction==SET_PIN_IN)
		{
			CLEAR_BIT((BASE_D+GPIODIR),(Pin));
		}
		else
		{
			SET_BIT((BASE_D+GPIODIR),(Pin));
		}
	}
	else
	{
	 //error	
	}
}

void SetPortDirection(uint8 port,enum_PinValue_t Val)
{
	WRITE_REG_8BIT((port+GPIODIR),Val); 
}

void digitalWrite(enum_PinsNum_t Pin,enum_PinValue_t Val)
{
	if(Pin<8)                  //PORTA
	{
		if (Val==SET_VALUE_LOW)
		{
			CLEAR_BIT((BASE_A+GPIOOUTDATA),(Pin));
		}
		else
		{
			SET_BIT((BASE_A+GPIOOUTDATA),(Pin));
		}
	}
	else if((Pin<16)&&(Pin>=8)) //PORTB
	{
		Pin-=8;
		if (Val==SET_VALUE_LOW)
		{
			CLEAR_BIT((BASE_B+GPIOOUTDATA),(Pin));
		}
		else
		{
			SET_BIT((BASE_B+GPIOOUTDATA),(Pin));
		}
	}
	else if ((Pin<24)&&(Pin>=16)) //PORTC
	{
		Pin-=16;
		if (Val==SET_VALUE_LOW)
		{
			CLEAR_BIT((BASE_C+GPIOOUTDATA),(Pin));
		}
		else
		{
			SET_BIT((BASE_C+GPIOOUTDATA),(Pin));
		}
	}
	else if ((Pin<32)&&(Pin>=24)) //PORTD
	{
		Pin-=24;
		if (Val==SET_VALUE_LOW)
		{
			CLEAR_BIT((BASE_D+GPIOOUTDATA),(Pin));
		}
		else
		{
			SET_BIT((BASE_D+GPIOOUTDATA),(Pin));
		}
	}
	else
	{
		//error
	}
}

enum_PinValue_t digitalRead(enum_PinsNum_t Pin)
{
	enum_PinValue_t ret_val=SET_VALUE_LOW;
	if(Pin<8)                     //PORTA
	{
		if (BIT_IS_SET(BASE_A+GPIOINDATA,Pin))
		{
			ret_val= SET_VALUE_HIGH;
		}
		else
		{
			ret_val = SET_VALUE_LOW;
		}
	}
	else if((Pin<16)&&(Pin>=8)) //PORTB
	{
		Pin-=8;
		if (BIT_IS_SET(BASE_B+GPIOINDATA,Pin))
		{
			ret_val= SET_VALUE_HIGH;
		}
		else
		{
			ret_val = SET_VALUE_LOW;
		}
	}
	else if ((Pin<24)&&(Pin>=16)) //PORTC
	{
		Pin-=16;
		if (BIT_IS_SET(BASE_C+GPIOINDATA,Pin))
		{
			ret_val= SET_VALUE_HIGH;
		}
		else
		{
			ret_val = SET_VALUE_LOW;
		}
	}
	else if ((Pin<32)&&(Pin>=24)) //PORTD
	{
		Pin-=24;
		if (BIT_IS_SET(BASE_D+GPIOINDATA,Pin))
		{
			ret_val= SET_VALUE_HIGH;
		}
		else
		{
			ret_val = SET_VALUE_LOW;
		}
	}
	else
	{
	 //error	
	}
	return ret_val;
}

void Port_Write(uint8 port,enum_PinValue_t Val)
{
	WRITE_REG_8BIT((port+GPIOOUTDATA),Val);
}

enum_PinValue_t Port_Read(uint8 port)
{
	return READ_REG_8BIT((port+GPIOINDATA));	
}

void gpio_spi_cng_master()
{
	SetPinDirection(B4,SET_PIN_OUT);     //SS
	SetPinDirection(B5,SET_PIN_OUT);     //MOSi
	SetPinDirection(B6,SET_PIN_IN);		 //MISO
	SetPinDirection(B7,SET_PIN_OUT);	 //SCK
}

void gpio_spi_cng_slave()
{
	SetPinDirection(B4,SET_PIN_IN);	 //SS
	SetPinDirection(B5,SET_PIN_IN);	 //MOSI
	SetPinDirection(B6,SET_PIN_OUT);    //MISO
	SetPinDirection(B7,SET_PIN_IN);     //SCK
}

void gpio_uart_cng()
{
	SetPinDirection(D0,SET_PIN_IN); // uart RX
	SetPinDirection(D1,SET_PIN_OUT); // uart TX
}

void BunchPins_Write(uint8* arr,uint8 N,enum_PinValue_t type)
{
	uint8 i;
	for (i=0;i<N;i++)
	{
		digitalWrite(arr[i],type);
	}
}

/*
void Bunch_pinRead(str_Pin_Id_t* ptr_arr,ecore_u8 N,ecore_u8* ptr_buffer_arr)
{
	uint8 i;
	for (i=0;i<N;i++)
	{
		ptr_buffer_arr[i]=pin_read(&ptr_arr[i]);
	}
}
*/