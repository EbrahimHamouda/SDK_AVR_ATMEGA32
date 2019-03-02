/* 
 * File:   lcd.h
 * Author: ebrahim hamouda
 *
 * Created on March 15, 2018, 11:29 PM
 */


#ifndef LCD_H
#define	LCD_H
#include <common/ebra_common.h>
#include "F:\embedded\Work_space\2_Drivers_atmega32\SDK_AVR_ATMEGA32\HAL\GPIO\GPIO.h"
#include "LCD_cnfg.h"

#ifdef _4BIT_MODE
	#define DATA_PINS 4
#else
	#define DATA_PINS 8
#endif // _DEBUG

/*
* notes 
* this file don't touch it don't configure any thing here 
* the configuration struct must be saved in the app layer and don't change it  
* every single API shall use your config it must be const all the run time 

*/
typedef struct
{
	uint8 arr_DataPins[DATA_PINS]; // put the num of the pin for data
	uint8 Enable_pin;			   // put the num of the enable bit
	uint8 Reg_Select;			   // put the num of the RS bit 
} struct_PinsCnfg_t;

/*commands*/
#define ENTRY_MODE   0x06
#define CLEAR_SCREEN 0x01
#define BIT_4        0x28
#define BIT_8        0x38
#define CURSOR_BLINK 0x0f
#define CURSOR_ON    0x0e
#define CURSOR_OFF   0x0c
#define DISPLAY_OFF  0x08

// to init the lcd sent the confg struct and wait 
void lcd_init(const struct_PinsCnfg_t* ptr);
// if u like to change the optional config in run time 
void lcd_cmd(const struct_PinsCnfg_t* ptr,uint8 cmd);
// to sent char to displaied
void lcd_chr(const struct_PinsCnfg_t* ptr,uint8 chr);
// to clear the lcd
void lcd_clear(const struct_PinsCnfg_t* ptr);
// to set cursor poisition 
void lcd_goto(const struct_PinsCnfg_t* ptr,uint8 row, uint8 col);
//to sent whole string
void lcd_str(const struct_PinsCnfg_t* ptr_lcd,uint8 row, uint8 col,uint8* ptr_chr);

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
