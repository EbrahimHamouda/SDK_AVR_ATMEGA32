/*
 * USART.h
 *
 *  Created on: Aug 1, 2018
 *      Author: mh-sh
 */

#ifndef HAL_UART_USART_H_
#define HAL_UART_USART_H_
//todo add intr
#include "../../Common.h"
#include "math.h"
#include <avr/io.h>
#include <avr/interrupt.h>

//#define UART_Sysclk 40000000UL

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
typedef enum {
	USART_RXC, USART_TXC,
} UART_INTERRUPT_t;

/* *   */

void UART_init(UART_NUM_t UART, u16 baudRate);
UARTError_t UART_getError(UART_NUM_t UART);
void UART_addISR(UART_NUM_t UART, UART_INTERRUPT_t ISR_type, void (*ISR)());
char UART_readByte(UART_NUM_t UART);
void UART_sendByte(UART_NUM_t UART, char Chr);
void UART_sendString(UART_NUM_t UART, char *String);
void UART_sendPacket(UART_NUM_t UART, char A[], u8 N);
u8 UART_dataReady(UART_NUM_t UART);
void UART_Flush(void);
void UART_deinit(UART_NUM_t UART); //todo incomplete

#endif /* HAL_UART_USART_H_ */
