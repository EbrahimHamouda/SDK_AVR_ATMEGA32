/*
 * commTxConfg.h
 *
 * Created: 2/13/2019 6:39:13 PM
 *  Author: ebrah
 */ 


#ifndef COMMTXCONFG_H_
#define COMMTXCONFG_H_

/*
* this file use to cnfg the comm stack_ TX
* channels used to Transmit
* the confg of this channels
* the path should be updated to the location of the channels
* to do future "features"
*/

#define _SPI0_CHANNEL_
#define _UART0_CHANNEL_
#define _I2C0_CHANNEL_

#include "C:\Users\ebrah\Desktop\test_comm-stack0\comm_stack\channels\i2c\I2C.h"
#include "C:\Users\ebrah\Desktop\test_comm-stack0\comm_stack\channels\spi\SPI.h"
#include "C:\Users\ebrah\Desktop\test_comm-stack0\comm_stack\channels\uart\USART.h"


typedef enum
{
	UART0_CHANNEL,
	SPI0_CHANNEL,
	I2C0_CHANNEL
} Comm_Channel_t;
 
#endif /* COMMTXCONFG_H_ */