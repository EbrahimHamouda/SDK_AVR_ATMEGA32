/*
* GPIO.c
*
* Created: 
*   Author: EbrahimHamouda
*/

#include "GPIO.h"

void SetPinDirection(Port_PinType Pin,Port_PinDirectionType Direction)
{
	if(Pin<8)                  //PORTA
	{
		if (Direction==PORT_PIN_IN)
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
		if (Direction==PORT_PIN_IN)
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
		if (Direction==PORT_PIN_IN)
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
		if (Direction==PORT_PIN_IN)
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
void SetPortDirection(PortType port,Port_ValType Val)
{
	WRITE_REG_8BIT((port+GPIODIR),Val); 
}
void digitalWrite(Port_PinType Pin,Port_PinLevelType Val)
{
	if(Pin<8)                  //PORTA
	{
		if (Val==PORT_PIN_LEVEL_LOW)
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
		if (Val==PORT_PIN_LEVEL_LOW)
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
		if (Val==PORT_PIN_LEVEL_LOW)
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
		if (Val==PORT_PIN_LEVEL_LOW)
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
Port_PinLevelType digitalRead(Port_PinType Pin)
{
	Port_PinLevelType ret_val=0;
	if(Pin<8)                     //PORTA
	{
		if (BIT_IS_SET(BASE_A+GPIOINDATA,Pin))
		{
			ret_val= PORT_PIN_LEVEL_HIGH;
		}
		else
		{
			ret_val = PORT_PIN_LEVEL_LOW;
		}
	}
	else if((Pin<16)&&(Pin>=8)) //PORTB
	{
		Pin-=8;
		if (BIT_IS_SET(BASE_B+GPIOINDATA,Pin))
		{
			ret_val= PORT_PIN_LEVEL_HIGH;
		}
		else
		{
			ret_val = PORT_PIN_LEVEL_LOW;
		}
	}
	else if ((Pin<24)&&(Pin>=16)) //PORTC
	{
		Pin-=16;
		if (BIT_IS_SET(BASE_C+GPIOINDATA,Pin))
		{
			ret_val= PORT_PIN_LEVEL_HIGH;
		}
		else
		{
			ret_val = PORT_PIN_LEVEL_LOW;
		}
	}
	else if ((Pin<32)&&(Pin>=24)) //PORTD
	{
		Pin-=24;
		if (BIT_IS_SET(BASE_D+GPIOINDATA,Pin))
		{
			ret_val= PORT_PIN_LEVEL_HIGH;
		}
		else
		{
			ret_val = PORT_PIN_LEVEL_LOW;
		}
	}
	else
	{
	 //error	
	}
	return ret_val;
}
void Port_Write(PortType port,Port_ValType Val)
{
	WRITE_REG_8BIT((port+GPIOOUTDATA),Val);
}
Port_ValType Port_Read(PortType port)
{
	return READ_REG_8BIT((port+GPIOINDATA));	
}

void gpio_spi_cng_master()
{
	SetPinDirection(B4,PORT_PIN_OUT);    //SS
	SetPinDirection(B5,PORT_PIN_OUT);    //MOSi
	SetPinDirection(B6,PORT_PIN_IN);	 //MISO
	SetPinDirection(B7,PORT_PIN_OUT);	 //SCK
}

void gpio_spi_cng_slave()
{
	SetPinDirection(B4,PORT_PIN_IN);	 //SS
	SetPinDirection(B5,PORT_PIN_IN);	 //MOSI
	SetPinDirection(B6,PORT_PIN_OUT);    //MISO
	SetPinDirection(B7,PORT_PIN_IN);     //SCK
}
void gpio_uart_cng()
{
	SetPinDirection(D0,PORT_PIN_IN); // uart RX
	SetPinDirection(D1,PORT_PIN_OUT); // uart TX
}