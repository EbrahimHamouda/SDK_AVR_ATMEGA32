/*
 * motor_driver.h
 *
 * Created: 3/8/2019 2:20:28 PM
 *  Author: ebrah
 */ 


#ifndef MOTOR_DRIVER_H_
#define MOTOR_DRIVER_H_
#include "F:\embedded\Work_space\2_Drivers_atmega32\SDK_AVR_ATMEGA32\HAL\GPIO\GPIO.h"

void motor_init();

void Go_forward(uint8 power);

void Go_backward(uint8 power);

void Go_Right(uint8 power);

void Go_Left(uint8 power);


#endif /* MOTOR_DRIVER_H_ */