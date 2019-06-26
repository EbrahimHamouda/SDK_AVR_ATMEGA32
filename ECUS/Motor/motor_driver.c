/*
* motor_driver.c
*
* Created: 3/8/2019 2:20:49 PM
*  Author: ebrah
*/
#include "motor_driver.h"
#include "pwm.h"


volatile uint8 power_leve;;
static void Get_power(uint8 power)
{
	power_leve = ((power*20*255)/100);
}

void motor_init()
{
	SetPortDirection(C,0xff); // output
	pwm_generate(B3,0); //forward
	pwm_generate(D4,0); //backward
	pwm_generate(D5,0); //right
	pwm_generate(D7,0); //left
}

void Go_forward(uint8 power)
{
	digitalWrite(C0,SET_VALUE_HIGH); //IN1
	digitalWrite(C1,SET_VALUE_LOW); //IN2
	Get_power(power);
	pwm_generate(B3,power_leve); //forward
}

void Go_backward(uint8 power)
{
	digitalWrite(C2,SET_VALUE_HIGH); //IN3
	digitalWrite(C3,SET_VALUE_LOW); //IN4
	Get_power(power);
	pwm_generate(D4,power_leve);
}

void Go_Right(uint8 power)
{
	digitalWrite(C4,SET_VALUE_HIGH); //IN1
	digitalWrite(C5,SET_VALUE_LOW); //IN2
	Get_power(power);
	pwm_generate(D5,power_leve); //right
}

void Go_Left(uint8 power)
{
	digitalWrite(C6,SET_VALUE_HIGH); //IN1
	digitalWrite(C7,SET_VALUE_LOW); //IN2
	Get_power(power);
	pwm_generate(D7,power_leve); //left
}
