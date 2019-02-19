/*
 * GPIO.h
 *
 *  Created on: 7/30/2018
 *      Author: Ahmed Yusri Mohammed
 */

#ifndef HAL_GPIO_H_
#define HAL_GPIO_H_

#include "hw_gpio.h"
#include <common/ebra_common.h>


typedef uint8 Port_PinType;
typedef uint8 PortType;
typedef uint8 Port_ValType;

#define A	 BASE_A
#define B	 BASE_B
#define C	 BASE_C
#define D	 BASE_D


typedef enum{
	PORT_PIN_IN,
	PORT_PIN_OUT,
}Port_PinDirectionType;

typedef enum{
	PORT_PIN_LEVEL_LOW = 0,
	PORT_PIN_LEVEL_HIGH = 1,
}Port_PinLevelType;

/**********************************
>>>>>>>For error detection.<<<<<<<<
**********************************/
typedef enum{
    PORT_PIN_NOT_EXIST,
	PASS,
}gGPIOError_t;

void SetPinDirection(Port_PinType Pin,Port_PinDirectionType Direction);

void SetPortDirection(PortType port,Port_ValType Val);

void digitalWrite(Port_PinType Pin,Port_PinLevelType Val);

Port_PinLevelType digitalRead(Port_PinType Pin);

void Port_Write(PortType port,Port_ValType Val);

Port_ValType Port_Read(PortType port);

void gpio_spi_cng_master();
void gpio_spi_cng_slave();
void gpio_uart_cng();

#endif /* HAL_GPIO_H_ */