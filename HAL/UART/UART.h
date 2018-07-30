/*
 * UART.h
 *
 * Created: 7/30/2018 2:59:43 PM
 *  Author: ahmed
 */ 


#ifndef UART_H_
#define UART_H_


#define UART_Sysclk 40000000UL

typedef enum{
	UART0,
	UART1,
		
}UART_NUM_t;

typedef enum{
	Overrun_Error,Break_Error,
	Parity_Error,Framing_Error,
	Receive_Timeout,NO_ERROR,
}UARTError_t;

typedef enum
{
	RX_BUFFER,TX_BUFFER,
}UART_BUFFER_t;

/* *   */

void UART_init(UART_NUM_t UART,UART_NUM_t baudRate);
UARTError_t UART_getError(UART_NUM_t UART);
char UART_readByte(UART_NUM_t UART);
void UART_sendByte(UART_NUM_t UART,char Chr);
void UART_sendString(UART_NUM_t UART,char *String);
void UART_sendPacket(UART_NUM_t UART,char A[],uint8 N);
uint8 UART_dataRedy(UART_NUM_t UART);

#endif /* UART_H_ */