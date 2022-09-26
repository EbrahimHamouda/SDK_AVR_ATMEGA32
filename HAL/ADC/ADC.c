/*
* ADC.c
*
* Created: 7/30/2018 3:02:03 PM
*  Author: ebrahim
*/

#include "ADC.h"
#include <avr/interrupt.h>
#define  ADC_BUSY BIT_IS_CLEAR((ADCCON+ADCBASE),4)
#define  V_IN	  ACCESS_REG_16BIT((ADCLOW+ADCBASE))

static void (*S_CallBackFun)(uint16);

ISR(ADC_vect)
{
	S_CallBackFun(V_IN);
}


void adc_init(Vref_SelectType vref,Mode_SelectType mode,Clk_SelectType clk)
{
	ACCESS_REG_8BIT((ADCCON+ADCBASE))    = 0;
	ACCESS_REG_8BIT((ADCMUX+ADCBASE))    = 0;
	ACCESS_REG_8BIT((ADCMUX+ADCBASE))	|= (vref<<6);										// set vref
	ACCESS_REG_8BIT((ADCCON+ADCBASE))	|= (clk <<0);									// set clock + set type of trigger
	ACCESS_REG_8BIT((ADCSFIOR+ADCBASE)) |= (mode <<5);
	if (mode != FREE_RUNNING_MODE)
	{
		SET_BIT((ADCCON+ADCBASE),5);
	}
	SET_BIT((ADCCON+ADCBASE),7);														// enable adc
}

uint16 adc_read(Channel_SelectType channel)
{
	ACCESS_REG_8BIT((ADCMUX+ADCBASE)) &= ~0x1f;              // clear channels value
	ACCESS_REG_8BIT((ADCMUX+ADCBASE)) |= channel;				// set channel
	SET_BIT((ADCCON+ADCBASE),6);									// start conversion for one shoot
	while(ADC_BUSY);											    // stay here while adc is busy
	return  V_IN;
}

void adc_IntEnable(void (*F_callBack)(uint16 val),Channel_SelectType channel)
{
	S_CallBackFun = F_callBack;
	SET_BIT((ADCCON+ADCBASE),3);
	ACCESS_REG_8BIT((ADCMUX+ADCBASE)) |= (channel<<0);				// set channel
	SET_BIT((ADCCON+ADCBASE),6);									// start conversion for one shoot
}

