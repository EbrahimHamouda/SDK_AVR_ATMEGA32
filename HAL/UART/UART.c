/*
 * USART.c
 *
 *  Created on: Aug 1, 2018
 *      Author: mh-sh
 */

#include "USART.h"
#include <avr/io.h>

void (*ISR_USART_RXC)(), (*ISR_USART_TXC)();

void USART_RXC_vect() {
	if (ISR_USART_RXC)
		ISR_USART_RXC();
	sei();
}
void USART_TXC_vect() {
	if (ISR_USART_TXC)
		ISR_USART_TXC();
	sei();
}
void UART_addISR(UART_NUM_t UART, UART_INTERRUPT_t ISR_type, void (*ISR)()) {
	if (ISR_type == USART_RXC) {
		ISR_USART_RXC = ISR;
		UCSRB |= (1 << RXCIE);
	} else if (ISR_type == USART_TXC) {
		ISR_USART_TXC = ISR;
		UCSRB |= (1 << TXCIE);
	}
	sei();
}

void UART_init(UART_NUM_t UART, u16 baudRate) {
	UBRRH = (unsigned char) (baudRate >> 8);
	UBRRL = (unsigned char) baudRate;

	UCSRB |= (1 << RXEN) | (1 << TXEN);

	UCSRC &= ~(1 << UMSEL);
	//2stop , odd parity , 8bit data
	UCSRC |= (1 << URSEL) | (3 << UPM0) | (1 << USBS) | (3 << UCSZ0);

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
	u8 dummy;
	while (UCSRA & (1 << RXC))
		dummy = UDR;
}

void UART_deinit(UART_NUM_t UART) {
	UBRRH = 0;
	UBRRL = 0;
	UCSRB = 0;
	UCSRC = 0;
	ISR_USART_RXC = 0;
	ISR_USART_TXC = 0;
}
