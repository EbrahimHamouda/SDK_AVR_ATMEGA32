/*
* File:   lcd.c
* Author: ebrahim hamouda
*
* Created on March 15, 2018, 11:23 PM
*/

#include "lcd.h"
#define  F_CPU 1000000UL
#include <util/delay.h>

#define EN        ptr->Enable_pin
#define RS        ptr->Reg_Select

static void kick(const struct_PinsCnfg_t* ptr,uint8 chr)
{
	/*
	* assign data in the pins of the confg
	* make pulse to make lcd work
	*/
	uint8 i;
	for (i=0;i<DATA_PINS;i++)
	{
		if (chr & (1<<i))
		{
			digitalWrite(ptr->arr_DataPins[i],SET_VALUE_HIGH);
		}
		else
		{
			digitalWrite(ptr->arr_DataPins[i],SET_VALUE_LOW);
		}
	}
	
	digitalWrite(EN,SET_VALUE_LOW);
	_delay_ms(1);
	digitalWrite(EN,SET_VALUE_HIGH);
}

void lcd_init(const struct_PinsCnfg_t* ptr)
{
	/*
	* set dirction output for data and control pins
	* config the lcd to start working
	*/
	uint8 i;
	for(i=0;i<DATA_PINS;i++)
	{
		SetPinDirection(ptr->arr_DataPins[i],SET_PIN_OUT);
	}
	SetPinDirection(RS,SET_PIN_OUT);
	SetPinDirection(EN,SET_PIN_OUT);
	
	#ifdef _4BIT_MODE
	lcd_cmd(ptr,0x02);						//config lcd mode send commands to
	lcd_cmd(ptr,BIT_4);
	#endif
	
	#ifdef _8BIT_MODE
	lcd_cmd(ptr,BIT_8);
	#endif
	
	lcd_cmd(ptr,ENTRY_MODE);                          // init lcd to use
	lcd_goto(ptr,0, 0);
	lcd_cmd(ptr,CURSOR_BLINK);
	lcd_clear(ptr);
}

void lcd_cmd(const struct_PinsCnfg_t* ptr,uint8 cmd)
{
	/*
	* select the register "command || data " in this case command
	* sent the command
	*/
	digitalWrite(RS,SET_VALUE_LOW);    // register select command
	
	#ifdef _8BIT_MODE
	kick(ptr,cmd);
	#endif

	#ifdef _4BIT_MODE
	kick(ptr,cmd>>4);
	kick(ptr,(cmd));
	#endif
	_delay_ms(2);
}

void lcd_chr(const struct_PinsCnfg_t* ptr,uint8 chr)
{
	/*
	* select the register "command || data " in this case data
	* sent the data
	*/
	digitalWrite(RS,SET_VALUE_HIGH);              // register select data
	
	#ifdef _8BIT_MODE
	kick(ptr,chr);
	#endif

	#ifdef _4BIT_MODE
	kick(ptr,chr>>4);
	kick(ptr,(chr));
	#endif
	_delay_ms(1);
}

void lcd_clear(const struct_PinsCnfg_t* ptr)
{
	lcd_cmd(ptr,CLEAR_SCREEN); // do the same as a command
}

void lcd_goto(const struct_PinsCnfg_t* ptr,uint8 row, uint8 col)
{
	if (row == 0)
	{
		lcd_cmd(ptr,(unsigned) 0x80 | col);
	}
	else if (row == 1)
	{
		lcd_cmd(ptr,(unsigned) 0xc0 | col);
	}
	#ifdef _LCD_16_4_
	else if (row==2)
	{
		lcd_cmd(ptr,(unsigned) 0x90  | col);
	}
	else if (row==3)
	{
		lcd_cmd(ptr,(unsigned) 0xD0 | col);
	}
	#endif // _LCD_16_4_
	else
	{
		// should never be here
	}
}

void lcd_str(const struct_PinsCnfg_t* ptr_lcd,uint8 row, uint8 col,uint8* ptr_chr)
{
	lcd_goto(ptr_lcd,row,col);
	while (*ptr_chr != '\0')
	{
		if (*ptr_chr == '*') // so i can't put * inside string to be shown in lcd
		{
			lcd_goto(ptr_lcd,++row,0);
			ptr_chr++;
			continue;
		}
		lcd_chr(ptr_lcd,*ptr_chr);
		ptr_chr++;
	}
}



