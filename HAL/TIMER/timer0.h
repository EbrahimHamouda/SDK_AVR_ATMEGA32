/*
 * timers.h
 *
 * Created: 7/15/2018 10:06:54 AM
 *  Author: ebrah
 */ 


#ifndef TIMERS_H_
#define TIMERS_H_

#include "common.h"

typedef enum
{
	NO_ERRORS_TIMR0,
	INVALIAD_ARGUMENTS_TIMR0,
	NOT_INIT_TIMR0,
	INCORRECT_MODE_TIMR0,
} enum_timr0_errors_t;

typedef enum
{
	OCO_PIN_DIS_CONNECT,
	OCO_PIN_TOGGEL,
	OCO_PIN_CLEAR,
	OCO_PIN_SET,
} enum_oco_pin_confg_t;

typedef enum
{
	NORMAL_MODE_TIMR0=0,
	CTC_MODE_TIMR0=2,
	PWM_PHASE_CORRECT_MODE_TIMR0=1,
	FAST_PWM_MODE_TIMR0=3,
} enum_mode_t;

typedef enum
{
	DISABLE_TIMER0=0,
	NO_PRESCALER_TMR0=1,
	CLK_DIV_8_TMR0=2,
	CLK_DIV_64_TMR0=3,
	CLK_DIV_256_TMR0=4,
	CLK_DIV_1024_TMR0=5,
	EXTERNAL_CLK_FALLING_EDGE_TMR0=6,
	EXTERNAL_CLK_RISING_EDGE_TMR0=7,
} enum_clk_select_t;

typedef struct  
{
	enum_mode_t mode;
	enum_clk_select_t clk_src;
	enum_oco_pin_confg_t oco_pin;
} str_confg_t;

enum_timr0_errors_t init_tmr0(str_confg_t* p_confg);

enum_timr0_errors_t read_tmr0(ecore_u8* value);

void write_tmr0(ecore_u8 value);

void set_comp_tmr0(ecore_u8 value);

enum_timr0_errors_t ov_int_enable_tmr0(void(*call_back_fun)());

enum_timr0_errors_t cmp_int_enable_tmr0(void(*call_back_fun)());

enum_timr0_errors_t set_ov_int_number(ecore_u16 counter);

enum_timr0_errors_t set_cmp_int_number(ecore_u16 counter);

ecore_u16 read_number_ov();

ecore_u16 read_number_cmp();

/*enum_timr0_errors_t fast_pwm_tmr0(ecore_u8 duty_cycle,ecore_u16 freq);*/
	
/*enum_timr0_errors_t de_init_tmr0();*/



#endif /* TIMERS_H_ */