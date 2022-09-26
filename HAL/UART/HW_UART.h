/*
 * HW_UART.h
 *
 * Created: 7/30/2018 2:57:32 PM
 *  Author: ebrahim
 */ 


#ifndef HW_UART_H_
#define HW_UART_H_

#define UART_BASE 0x29 

// OFFESTS 
#define UARTBITREGLOW	   0x00
#define UARTCONTROLB	   0x01
#define UARTCONTROLA	   0x02
#define UARTDATAREG        0x03
#define UARTCONTROLC       0x17
#define UARTBITREGHIGH     0x17


/* UCSRA */
#define RXC     7
#define TXC     6
#define UDRE    5
#define FE      4
#define DOR     3
#define PE      2
#define U2X     1
#define MPCM    0

/* UCSRB */
#define RXCIE   7
#define TXCIE   6
#define UDRIE   5
#define RXEN    4
#define TXEN    3
#define UCSZ2   2
#define RXB8    1
#define TXB8    0

/* UCSRC */
#define URSEL   7
#define UMSEL   6
#define UPM1    5
#define UPM0    4
#define USBS    3
#define UCSZ1   2
#define UCSZ0   1
#define UCPOL   0

#endif /* HW_UART_H_ */