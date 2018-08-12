/* 
 * File:   lcd.h
 * Author: ebrahim hamouda
 *
 * Created on March 15, 2018, 11:29 PM
 */


#ifndef LCD_H
#define	LCD_H
#include "ebra_common.h"
#include "GPIO.h"

#define _4BIT_MODE
#define DATA_PINS 4

typedef struct
{
	uint8 arr_DataPins[DATA_PINS];
	uint8 Enable_pin;
	uint8 Reg_Select;
} Lcd_PinsCfgType;

/*commands*/
#define ENTRY_MODE   0x06
#define CLEAR_SCREEN 0x01
#define BIT_4        0x28
#define BIT_8        0x38
#define CURSOR_BLINK 0x0f
#define CURSOR_ON    0x0e
#define CURSOR_OFF   0x0c
#define DISPLAY_OFF  0x08

void lcd_init(Lcd_PinsCfgType* ptr);
void lcd_cmd(Lcd_PinsCfgType* ptr,uint8 cmd);
void lcd_chr(Lcd_PinsCfgType* ptr,uint8 chr);
void lcd_clear(Lcd_PinsCfgType* ptr);
void lcd_goto(Lcd_PinsCfgType* ptr,uint8 row, uint8 col);
void lcd_str(Lcd_PinsCfgType* ptr_lcd,uint8* ptr_chr);

#endif	/* LCD_H */





















//typedef enum mode {MODE_4BIT,MODE_8BIT} Mode;
//typedef enum cursor{CURSOROFF,CURSOR_ON_BLINK,CURSOR_ON_NBLINK} Cursor;
//typedef struct
//{
//    Mode  lcd_mode; 
//    Cursor lcd_cursor; 
//    uint8*data_port; 
//    uint8*data_dirc;  
//    uint8*ControlPort;
//} lcd;
