/*
 * USART.c
 *
 *  Created on: Aug 1, 2018
 *      Author: mh-sh
 */

#include "USART.h"

void UART_init(UART_NUM_t UART, u16 baudRate) {
	UBRRH = (unsigned char) (baudRate >> 8);
	UBRRL = (unsigned char) baudRate;

	UCSRB = (1 << RXEN) | (1 << TXEN);

	UCSRC &= ~(1 << UMSEL);
	//2stop , odd parity , 8bit data
	UCSRC = (1 << URSEL) | (3 << UPM0) | (1 << USBS) | (3 << UCSZ0);

}
UARTError_t UART_getError(UART_NUM_t UART) {
	UARTError_t ret_error = NO_ERROR;
	if (UCSRA & ((1 << FE) | (1 << DOR) | (1 << PE))) {
		if (UCSRA & (1 << FE)) {
			ret_error = Framing_Error;
		} else if (UCSRA & (1 << DOR)) {
			ret_error = Overrun_Error;
		} else if (UCSRA & (1 << PE)) {
			ret_error = Parity_Error;
		}
	}

	return ret_error;

}
char UART_readByte(UART_NUM_t UART) { //Blocking

	while (!(UCSRA & (1 << RXC)))
		;
	return UDR;

}
void UART_sendByte(UART_NUM_t UART, char Chr) { //Blocking
	while (!(UCSRA & (1 << UDRE)))
		;
	UDR = Chr;
}
void UART_sendString(UART_NUM_t UART, char *String) {
	u8 i = 0;
	while (String[i] != '\0') {
		UART_sendByte(UART, String[i++]);
	}
}

void UART_sendPacket(UART_NUM_t UART, char A[], u8 N) {
	u8 i = 0;
	while (i < N) {
		UART_sendByte(UART, A[i++]);
	}

}
u8 UART_dataReady(UART_NUM_t UART) {
	return (UCSRA & (1 << RXC));
}

void UART_Flush(void) {
	unsigned char dummy;
	while (UCSRA & (1 << RXC))
		dummy = UDR;
}
