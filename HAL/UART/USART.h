/*
* USART.h
*
*  Created on: Aug 1, 2018
*      Author: mh-sh
*/

#ifndef HAL_UART_USART_H_
#define HAL_UART_USART_H_

#include <common\ebra_common.h>
#include "HW_UART.h"

#define F_CPU 1000000UL
/* Functions
*/

void  Uart_init();  //BAUD RANGE 2400

uint8 Uart_ReadByte();

void  Uart_SendByte(uint8 Chr);

void  Uart_TxInterruptEnable(void (*ptr)());

void  Uart_RxInterruptEnable(void (*ptr)(uint8));

void Uart_TxinterruptDisable();

#endif /* HAL_UART_USART_H_ */
