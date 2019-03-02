/*
* File:   kpad_driver.c
* Author: ebrahim hamouda	
*
* Created on March 21, 2018, 5:56 PM
*/


#include "key_pad.h"

static void (*ptr_CallBackFun)(uint8);  // for save the call back fun to call it in dispatcher 

void kpad_init(KeyPad_PinCnfg_t* ptr,void (*ptr_Fu)(uint8))
{
	/*
	* make the rows IN put
	* make the coloums OUT PUT
	* assign call back funcation 
	*/
	uint8 i;
	for (i=0;i<4;i++)
	{
		SetPinDirection(ptr->arr_KeyPadInputPins[i],SET_PIN_IN);
		SetPinDirection(ptr->arr_KeyPadOutputPins[i],SET_PIN_OUT);
	}
	ptr_CallBackFun = ptr_Fu;
}

static uint8 get_key(KeyPad_PinCnfg_t* ptr)
{
	/*
	* static funcation the main core of keypad
	* it's usage to know which key has been pressed
	* it called when it found one or more input pin low 
	* check which pin caused low by making one shifting colom low
	*/
    uint8 i,j;	
    uint8 key_ret_val = '\0';
		
	for (i = 0; i < COLUMS; i++)
	{
		BunchPins_Write(ptr->arr_KeyPadOutputPins,COLUMS,SET_VALUE_HIGH); // set all coloums high
		// to stand out the pressed key i need to make all the other out to be high and one only low
		digitalWrite(ptr->arr_KeyPadOutputPins[i],SET_VALUE_LOW);  // clear a single coloum
		for (j = 0; j < ROWS ; j++)
		{
			if (!(digitalRead(ptr->arr_KeyPadInputPins[j])))           // check if single input pin low 
			{
				while (!(digitalRead(ptr->arr_KeyPadInputPins[j])));	// stay here while is pressed "low"
				switch (j) 
				{
					case (0):
					{
						if		(i == 0) key_ret_val = P_0_0; // j=0 , i=0
						else if (i == 1) key_ret_val = P_0_1; // j=0 , i=1
#ifdef _COLUM_3
						else if (i == 2) key_ret_val = P_0_2; // j=0 , i=2
#endif // _COLUM_3
#ifdef _COLUM_4
						else if (i == 3) key_ret_val = P_0_3; // j=0 , i=3
#endif // _COLUM_4
						else
						{
							// Error  to do >> make Det system
						}
						break;
					}
					case (1):
					{
						if		(i == 0) key_ret_val = P_1_0; // j=1 , i=0
						else if (i == 1) key_ret_val = P_1_1; // j=1 , i=1
#ifdef _COLUM_3
						else if (i == 2) key_ret_val = P_1_2; // j=1 , i=2
#endif // _COLUM_3
#ifdef _COLUM_4
						else if (i == 3) key_ret_val = P_1_3; // j=1 , i=3
#endif // _COLUM_4		
						else
						{
							// Error  to do >> make Det system
						}
						break;
					}
#ifdef _ROW_3_
					case (2):
					{
						if		(i == 0) key_ret_val = P_2_0; // j=2 , i=0
						else if (i == 1) key_ret_val = P_2_1; // j=2 , i=1
#ifdef _COLUM_3
						else if (i == 2) key_ret_val = P_2_2; // j=2 , i=2
#endif // _COLUM_3
#ifdef _COLUM_4
						else if (i == 3) key_ret_val = P_2_3; // j=2 , i=3
#endif // _COLUM_4
						else
						{
							// Error  to do >> make Det system
						}
						break;
					}
#endif // _ROW_3_

#ifdef _ROW_4_
					case (3):
					{
						if		(i == 0) key_ret_val = P_3_0; // j=3 , i=0
						else if (i == 1) key_ret_val = P_3_1; // j=3 , i=1
#ifdef _COLUM_3
						else if (i == 2) key_ret_val = P_3_2; // j=3 , i=2
#endif // _COLUM_3
#ifdef _COLUM_4
						else if (i == 3) key_ret_val = P_3_3; // j=3 , i=3
#endif // _COLUM_4
						else
						{
							// Error  to do >> make Det system 
						}
						break;
					}
#endif // _ROW_4_
				}
			}
		}
	}
	return key_ret_val;
}

void keyPad_dispatcher(KeyPad_PinCnfg_t* ptr)
{
	volatile uint8 i;
	BunchPins_Write(ptr->arr_KeyPadOutputPins,COLUMS,SET_VALUE_LOW); // clear output pins
	BunchPins_Write(ptr->arr_KeyPadInputPins,ROWS,SET_VALUE_HIGH); // set intput pins 
	for(i=0;i<ROWS;i++)
	{
		if (!(digitalRead(ptr->arr_KeyPadInputPins[i])))
		{
			ptr_CallBackFun(get_key(ptr));	//call back fun
			// when come back again it should be breaked;
		}
	}
}

void Change_CallBackfunction(void (*ptr_Fu)(uint8 ))
{
	ptr_CallBackFun=ptr_Fu;
}