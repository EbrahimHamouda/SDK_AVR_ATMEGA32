/*
* USART.h
*
*  Created on: Aug 1, 2018
*      Author: mh-sh
*/

#ifndef HAL_UART_USART_H_
#define HAL_UART_USART_H_

#include "HW_UART.h"
#include "ebra_common.h"

/* Functions
*/

void  Uart_init();  //BAUD RANGE 2400

uint8 Uart_ReadByte();

void  Uart_SendByte(uint8 Chr);

void  Uart_TxInterruptEnable(void (*ptr)());

void  Uart_RxInterruptEnable(void (*ptr)());

#endif /* HAL_UART_USART_H_ */
