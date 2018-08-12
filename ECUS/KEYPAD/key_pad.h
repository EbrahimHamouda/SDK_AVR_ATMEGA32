/* 
 * File:   key_pad.h
 * Author: ebrahim hamouda
 *
 * Created on March 21, 2018, 5:52 PM
 */

#include "GPIO.h"

#ifndef KEY_PAD_H
#define	KEY_PAD_H

typedef struct
{
	uint8 arr_KeyPadInputPins[4];
	uint8 arr_KeyPadOutputPins[4];
} KeyPad_PinCfgType;

void kpad_init(KeyPad_PinCfgType* ptr,void (*ptr_Fu)(uint8 ));

void keyPad_dispatcher(KeyPad_PinCfgType* ptr);

#endif	/* KEY_PAD_H */

