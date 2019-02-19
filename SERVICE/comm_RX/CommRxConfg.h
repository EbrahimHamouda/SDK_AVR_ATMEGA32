/*
 * CommRxConfg.h
 *
 * Created: 2/14/2019 12:10:54 AM
 *  Author: ebrah
 */ 


#ifndef COMMRXCONFG_H_
#define COMMRXCONFG_H_

/*
* this file use to cnfg the comm stack_ RX 
* config the worst case expacted num_bytes to create buffer
* channels used to receive 
* the confg of this channels 
* the path should be updated to the location of the channels 
* to do future "features" 

*/
#define _UART0_
#define _SPIO_
#define _I2C0_
#define MAX__SIZE 1000  // the message will be MAX__SIZE-1 and confirmation letter
#include "C:\Users\ebrah\Desktop\test_comm-stack0\comm_stack\channels\i2c\I2C.h"
#include "C:\Users\ebrah\Desktop\test_comm-stack0\comm_stack\channels\spi\SPI.h"
#include "C:\Users\ebrah\Desktop\test_comm-stack0\comm_stack\channels\uart\USART.h"

typedef enum
{
	UART0=0, // more channel to add in future
	SPIO=1,
	I2C0=2,
} RX_Channel_t;


#endif /* COMMRXCONFG_H_ */