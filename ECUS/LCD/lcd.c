/*
* File:   lcd.c
* Author: ebrahim hamouda
*
* Created on March 15, 2018, 11:23 PM
*/

#include "lcd.h"
#define  F_CPU 1000000UL
#include <util/delay.h>
#include "GPIO.h"

#define EN        ptr->Enable_pin
#define RS        ptr->Reg_Select

static void kick(Lcd_PinsCfgType* ptr,uint8 chr)
{
	uint8 i;
	for (i=0;i<DATA_PINS;i++)
	{
		if (chr & (1<<i))
		{
			digitalWrite(ptr->arr_DataPins[i],PORT_PIN_LEVEL_HIGH);
		}
		else
		{
			digitalWrite(ptr->arr_DataPins[i],PORT_PIN_LEVEL_LOW);
		}
	}
	digitalWrite(EN,PORT_PIN_LEVEL_LOW);
	_delay_ms(30);
	digitalWrite(EN,PORT_PIN_LEVEL_HIGH);
}

void lcd_init(Lcd_PinsCfgType* ptr)
{
	uint8 i;
	for(i=0;i<DATA_PINS;i++)                                 // set dirction output for data and control
	{
		SetPinDirection(ptr->arr_DataPins[i],PORT_PIN_OUT);
	}
	SetPinDirection(RS,PORT_PIN_OUT);                       
	SetPinDirection(EN,PORT_PIN_OUT);
	
	#ifdef _4BIT_MODE
	lcd_cmd(ptr,0x02);										//config lcd mode send commands to 
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

void lcd_cmd(Lcd_PinsCfgType* ptr,uint8 cmd)
{
	digitalWrite(RS,PORT_PIN_LEVEL_LOW);    // register select command 
	
	#ifdef _8BIT_MODE           
	kick(ptr,cmd);
	#endif

	#ifdef _4BIT_MODE
	kick(ptr,cmd>>4);
	kick(ptr,(cmd));
	#endif
	_delay_ms(50);
}

void lcd_chr(Lcd_PinsCfgType* ptr,uint8 chr) 
{	
	digitalWrite(RS,PORT_PIN_LEVEL_HIGH);              // register select data
	
	#ifdef _8BIT_MODE
	kick(ptr,chr);
	#endif

	#ifdef _4BIT_MODE
	kick(ptr,chr>>4);
	kick(ptr,(chr));
	#endif
	_delay_ms(50);
}

void lcd_clear(Lcd_PinsCfgType* ptr)
{
	lcd_cmd(ptr,CLEAR_SCREEN);
}

void lcd_goto(Lcd_PinsCfgType* ptr,uint8 row, uint8 col) 
{
	if (row == 0) 
	{
		lcd_cmd(ptr,(unsigned) 0x80 | col);
	} else if (row == 1) 
	{
		lcd_cmd(ptr,(unsigned) 0xc0 | col);
	}
}

void lcd_str(Lcd_PinsCfgType* ptr_lcd,uint8* ptr_chr)
{
	while (*ptr_chr != '\0')
	{
		lcd_chr(ptr_lcd,*ptr_chr);
		ptr_chr++;
	}
}
