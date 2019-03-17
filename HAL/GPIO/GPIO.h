/*
 * GPIO.h
 *
 *  Created on: 7/30/2018
 *      Author: Ebrahim hamouda
 */

#ifndef HAL_GPIO_H_
#define HAL_GPIO_H_

#include <common/ebra_common.h>
#include "hw_gpio.h"


typedef enum{			// to set values of logic level
	SET_VALUE_LOW,
	SET_VALUE_HIGH,
} enum_PinValue_t;

typedef enum{      // to set dirication 
	SET_PIN_IN,
	SET_PIN_OUT,
}  enum_PinDirection_t;

typedef enum{   // to set the base address it confg from hw-gpio
	//can be added more if there's
	A = BASE_A,
	B = BASE_B,
	C = BASE_C,
	D = BASE_D,
} enum_PortName_t;


// to set single pin dirction
void SetPinDirection(enum_PinsNum_t Pin,enum_PinDirection_t Direction);

//to set whole port dirction 
void SetPortDirection(uint8 port,uint8 Val);

//to write to single pin value
void digitalWrite(enum_PinsNum_t Pin,enum_PinValue_t Val);

//to read from single pin value
enum_PinValue_t digitalRead(enum_PinsNum_t Pin);

//to write to whole port values
void Port_Write(uint8 port,enum_PinValue_t Val);

//to read the whole port values
uint8 Port_Read(uint8 port);

//to write to multi-different pin in different ports
void BunchPins_Write(uint8* arr,uint8 N,enum_PinValue_t type);

//to read to multi-different pin in different ports
void BunchPins_Read(uint8* arr_Input,uint8 arr_Output,uint8 Num);

//confg spi to be master
void gpio_spi_cng_master();
//confg spi to be slave 
void gpio_spi_cng_slave();
//confg the uart to TX & RX
void gpio_uart_cng();

#endif /* HAL_GPIO_H_ */