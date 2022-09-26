/* 
 * File:   key_pad.h
 * Author: ebrahim hamouda
 *
 * Created on March 21, 2018, 5:52 PM
 */

#ifndef KEY_PAD_H
#define	KEY_PAD_H

#include "F:\embedded\Work_space\2_Drivers_atmega32\SDK_AVR_ATMEGA32\HAL\GPIO\GPIO.h"
#include "keypad_Cnfg.h"


typedef struct
{
	uint8 arr_KeyPadInputPins[ROWS];	 // for Rows only
	uint8 arr_KeyPadOutputPins[COLUMS];  // for coloums only
} KeyPad_PinCnfg_t;

// to init the key pad pass the pin config and the funcation to receive the key pressed
void kpad_init(KeyPad_PinCnfg_t* ptr,void (*ptr_Fu)(uint8 ));
// this funcation called at the inifity loop to check any pressed
void keyPad_dispatcher(KeyPad_PinCnfg_t* ptr);
//this funcatio use to change the call back 
void Change_CallBackfunction(void (*ptr_Fu)(uint8 ));

#endif	/* KEY_PAD_H */

