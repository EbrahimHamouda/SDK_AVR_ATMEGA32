/*
 * USART.h
 *
 *  Created on: Aug 1, 2018
 *      Author: mh-sh
 */

#ifndef HAL_UART_USART_H_
#define HAL_UART_USART_H_

#include "../../Common.h"
#include "../iom32.h"

#define UART_Sysclk 40000000UL

typedef enum {
	UART0, UART1,

} UART_NUM_t;

typedef enum { /// changed order
	NO_ERROR,
	Overrun_Error,
	Break_Error,
	Parity_Error,
	Framing_Error,
	Receive_Timeout,
} UARTError_t;

typedef enum {
	RX_BUFFER, TX_BUFFER,
} UART_BUFFER_t;

/* *   */

void UART_init(UART_NUM_t UART, u16 baudRate);
UARTError_t UART_getError(UART_NUM_t UART);
char UART_readByte(UART_NUM_t UART);
void UART_sendByte(UART_NUM_t UART, char Chr);
void UART_sendString(UART_NUM_t UART, char *String);
void UART_sendPacket(UART_NUM_t UART, char A[], u8 N);
u8 UART_dataReady(UART_NUM_t UART);

#endif /* HAL_UART_USART_H_ */
