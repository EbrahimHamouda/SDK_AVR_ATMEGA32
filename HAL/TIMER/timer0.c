/*
 * timer0.c
 *
 * Created: 7/16/2018 4:16:06 PM
 *  Author: ebrah
 */ 
 
#include "timer0.h"
#include <avr/io.h>
#include <avr/interrupt.h>


// SOLID DATA
#define CLK_SRC_OFFSET 0
#define OCO_PIN_OFFSET 4
/***************/

static ecore_u16 number_of_over_flow;
static ecore_u16 number_of_compare_match;


 volatile void (*temp_addrass_ov_cp_fun)(void)  ;
 volatile void (*temp_addrass_cmp_cp_fun)(void) ;

ISR(TIMER0_OVF_vect)
{
	number_of_over_flow++;
	if(temp_addrass_ov_cp_fun != NULL)
	{
		void (*temp_addrass_ov_cp_fun)(void);
	}
}

ISR(TIMER0_COMP_vect)
{
	number_of_compare_match++;
	if(temp_addrass_ov_cp_fun != NULL)
	{
		void (*temp_addrass_cmp_cp_fun)(void);
	}
}

enum_timr0_errors_t init_tmr0(str_confg_t* p_confg)
{
	enum_timr0_errors_t e_ret_val = NO_ERRORS_TIMR0;
	
	if (p_confg != NULL)
	{
		TCCR0 =  CLEAR_REG  ;
		TCCR0 |= (p_confg->clk_src)<<CLK_SRC_OFFSET ;
		TCCR0 |= (p_confg->oco_pin)<<OCO_PIN_OFFSET ;
		
		switch(p_confg->mode)
		{
			case NORMAL_MODE_TIMR0 :
			{
				break;
			}
			case CTC_MODE_TIMR0:
			{
				TCCR0 |= (1<<3);
				break;
			}
			case FAST_PWM_MODE_TIMR0:
			{
				TCCR0 |= (1<<3);
				TCCR0 |= (1<<6);
				break;
			}
			case PWM_PHASE_CORRECT_MODE_TIMR0 :
			{
				TCCR0 |= (1<<6);
				break;
			}
			default:
			{
				e_ret_val = INCORRECT_MODE_TIMR0;
			}
		}
	}
	else
	{
		e_ret_val = INVALIAD_ARGUMENTS_TIMR0;
	}
	
	return e_ret_val;
}

enum_timr0_errors_t read_tmr0(ecore_u8* value)
{
	enum_timr0_errors_t e_ret_val = NO_ERRORS_TIMR0;
	
	if (value != NULL)
	{
		if (TCCR0 != 0)
		{
			*value = TCNT0;
		}
		else
		{
			e_ret_val = NOT_INIT_TIMR0; 
		}
	}
	else
	{
		e_ret_val = INVALIAD_ARGUMENTS_TIMR0;
	}
	
	return e_ret_val;
}

void write_tmr0(ecore_u8 value)
{	
	 TCNT0 = value ;
}

void set_comp_tmr0(ecore_u8 value)
{
	OCR0 = value;
}

enum_timr0_errors_t ov_int_enable_tmr0( void (*call_back_fun)(void) )
{
	sei(); 
	TIMSK |= 1<<0;
	number_of_over_flow = 0;
	temp_addrass_ov_cp_fun = call_back_fun;
	return 0;
}

enum_timr0_errors_t cmp_int_enable_tmr0( void (*call_back_fun)(void) )
{
	sei();
	TIMSK |= 1<<1;
	number_of_compare_match = 0;
	temp_addrass_cmp_cp_fun = call_back_fun;
	return 0;
}

enum_timr0_errors_t set_ov_int_number(ecore_u16 counter)
{
	number_of_over_flow = counter;
	return 0;
}	

enum_timr0_errors_t set_cmp_int_number(ecore_u16 counter)
{
	number_of_compare_match = counter;
	return 0;
}

ecore_u16 read_number_ov()
{
	return number_of_over_flow;
}

ecore_u16 read_number_cmp()
{
	return number_of_compare_match;
}
	
/*
// enum_timr0_errors_t de_init()
{
	TCCR0 = 0;
}
*/