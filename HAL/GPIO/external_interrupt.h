/*
 * external_interrupt.h
 *
 * Created: 7/8/2018 4:48:18 PM
 *  Author: ebrah
 */ 


#ifndef EXTERNAL_INTERRUPT_H_
#define EXTERNAL_INTERRUPT_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <common/ebra_common.h>

typedef enum
{
	INT_LOW_LEVEL,
	INT_ANY_LOGIC_CHANGE,
	INT_FALLING_EDGE,
	INT_RISING_EDGE
} enum_external_int_type_t;

typedef enum
{
	EXT_INT0=6,
	EXT_INT1=7,
	EXT_INT2=5,
} enum_extenal_int_n_t;

void Enable_EXT_INT(uint8 X);

void Disable_EXT_INT(uint8 X);

void extrnal_int_init(enum_extenal_int_n_t X,enum_external_int_type_t int_type,void (*NotifyWhenISR)());

#endif /* EXTERNAL_INTERRUPT_H_ */