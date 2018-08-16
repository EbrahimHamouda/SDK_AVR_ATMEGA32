/*
* ADC.h
*
* Created: 8/14/2018 2:28:47 PM
*  Author: ebrahim
*/


#ifndef ADC_H_
#define ADC_H_
#include "ebra_common.h"
#include "HW_ADC.h"

typedef enum
{
	AREF = 0,
	AVCC = 1,
	INTERNAL_VREF = 3,
} Vref_SelectType;

typedef enum
{
	CHANNEL0,
	CHANNEL1,
	CHANNEL2,
	CHANNEL3,
	CHANNEL4,
	CHANNEL5,
	CHANNEL6,
	CHANNEL7,
} Channel_SelectType;

typedef enum
{
	FREE_RUNNING_MODE = 0,
	ANALOG_COMPARTOR = 1,
	EXTERNAL_INITERRUPT0 = 2,
	COMPARE_MATCH_TIMER0 = 3,
	OVERFLOW_TIMER0 = 4,
	COMPARE_MATCH_TIMER1=5,
	OVERFLOW_TIMER1=6,
} Mode_SelectType;

typedef enum
{
	CLK_ADC_DIV_2,
	CLK_ADC_DIV_4 = 2,
	CLK_ADC_DIV_8 = 3,
	CLK_ADC_DIV_16 = 4,
	CLK_ADC_DIV_32 = 5,
	CLK_ADC_DIV_64 = 6,
	CLK_ADC_DIV_128 = 7,
} Clk_SelectType;


void adc_init(Vref_SelectType vref,Mode_SelectType mode,Clk_SelectType clk);
uint16 adc_read(Channel_SelectType channel);
void adc_IntEnable(void (*F_callBack)(uint16 val),Channel_SelectType channel);

#endif /* ADC_H_ */