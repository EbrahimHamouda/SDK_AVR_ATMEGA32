/*
* File:   kpad_driver.c
* Author: ebrahim hamouda	
*
* Created on March 21, 2018, 5:56 PM
*/


#include "key_pad.h"

static void (*ptr_CallBackFun)(uint8);  // for save the call back fun to call it in dispatcher 

void kpad_init(KeyPad_PinCfgType* ptr,void (*ptr_Fu)(uint8))
{
	uint8 i;
	for (i=0;i<4;i++)
	{
		SetPinDirection(ptr->arr_KeyPadInputPins[i],PORT_PIN_IN);
		SetPinDirection(ptr->arr_KeyPadOutputPins[i],PORT_PIN_OUT);
	}
	ptr_CallBackFun = ptr_Fu;
}

static uint8 get_key(KeyPad_PinCfgType* ptr)
{
	volatile uint8 i,j;	
    uint8 key_ret_val = '\0';
	
	for (i = 0; i < 4; i++)
	{
		BunchPins_Write(ptr->arr_KeyPadOutputPins,4,PORT_PIN_LEVEL_HIGH); // set output pins
		digitalWrite(ptr->arr_KeyPadOutputPins[i],PORT_PIN_LEVEL_LOW);  // clear a single output pin	
		for (j = 0; j < 4; j++)
		{
			if (!(digitalRead(ptr->arr_KeyPadInputPins[j])))            // check if single input pin high 
			{
				while (!(digitalRead(ptr->arr_KeyPadInputPins[j])));	// stay here while is pressed 
				switch (j) 
				{
					case (0):
					{
						if		(i == 0) key_ret_val = '7';
						else if (i == 1) key_ret_val = '8';
						else if (i == 2) key_ret_val = '9';
						else if (i == 3) key_ret_val = '/';
						break;
					}
					case (1):
					{
						if		(i == 0) key_ret_val = '4';
						else if (i == 1) key_ret_val = '5';
						else if (i == 2) key_ret_val = '6';
						else if (i == 3) key_ret_val = '*';
						break;
					}
					case (2):
					{
						if		(i == 0) key_ret_val = '1';
						else if (i == 1) key_ret_val = '2';
						else if (i == 2) key_ret_val = '3';
						else if (i == 3) key_ret_val = '-';
						break;
					}
					case (3):
					{
						if		(i == 0) key_ret_val = 'c';
						else if (i == 1) key_ret_val = '0';
						else if (i == 2) key_ret_val = '=';
						else if (i == 3) key_ret_val = '+';
						break;
					}
				}
			}
		}
	}
	return key_ret_val;
}

void keyPad_dispatcher(KeyPad_PinCfgType* ptr)
{
	volatile uint8 i;
	BunchPins_Write(ptr->arr_KeyPadOutputPins,4,PORT_PIN_LEVEL_LOW); // clear output pins
	BunchPins_Write(ptr->arr_KeyPadInputPins,4,PORT_PIN_LEVEL_HIGH); // set intput pins
	for(i=0;i<4;i++)
	{
		if (!(digitalRead(ptr->arr_KeyPadInputPins[i])))
		{
			ptr_CallBackFun(get_key(ptr));	//call back fun
			// when come back again it should be breaked;
		}
	}
}
