/*
* commTx.c
*
* Created: 8/9/2018 1:19:32 PM
*  Author: ebrahim
*/

#include "commTx.h"
static CommTx_DataCfgType    Staticptr_cngCommTx; // to buffer the confg 

#define SPTR_DATA2SENT		(Staticptr_cngCommTx.ptr_Data2Sent)
#define S_CHANNEL			(Staticptr_cngCommTx.Channel_Select)
#define NUM_BYTES			(Staticptr_cngCommTx.Num_bytes2sent)
#define CALLTX_FINIHS		(Staticptr_cngCommTx.commtx_compelete)

static uint16		Scounter; // to keep counting the data have been sent 
static bool_t		flage_Tx_Sending; // this flage used as semphore between interrupts and dispatchers 



static void HardWare_CallBack()
{
	/*
	* switch to the channel used to transmit
	* set the transmit_flage to make the dissaptcher do it's work
	*/
	if (Scounter<=NUM_BYTES)  // if hardware interrupts faster than the checking dispatcher 
	{
		switch (S_CHANNEL)
		{
#ifdef _UART0_CHANNEL_
			case UART0_CHANNEL:
			{
				Uart_SendByte(SPTR_DATA2SENT[Scounter]);
				break;
			}
#endif
#ifdef _SPI0_CHANNEL_
			case SPI0_CHANNEL:
			{
				spi_Tx(SPTR_DATA2SENT[Scounter]);
				break;
			}
#endif
#ifdef _I2C0_CHANNEL_
			case I2C0_CHANNEL:
			{
				I2C_TxWithInterrupt(SPTR_DATA2SENT[Scounter]);
				break;
			}
#endif
		}
		Scounter++;
		
		if (Scounter>NUM_BYTES)
		{
			Scounter--;	
		}
	}
	flage_Tx_Sending =1;  // set flage to work dispatcher
}


void comm_TxRest()
{
	/*
	*this funcation used to free the Comm_Tx 
	* to init new transmition 
	*/
	Scounter			= 0;
	flage_Tx_Sending    = 0;
}

void comm_TxInit(CommTx_DataCfgType* ptr_struct)
{
	/*
	* delay to let the reciever be ready
	* check if comm tx ideal first 
	* reset_comm Tx
	* take configuration to  static variable  
	* switch on channels to init the rquired one 
	*/
	comm_TxRest();		// rest static variables
	// Store cnfg variables 
	Staticptr_cngCommTx.Channel_Select = ptr_struct->Channel_Select;
	Staticptr_cngCommTx.Num_bytes2sent = ptr_struct->Num_bytes2sent;
	Staticptr_cngCommTx.commtx_compelete = ptr_struct->commtx_compelete;
	Staticptr_cngCommTx.ptr_Data2Sent = ptr_struct->ptr_Data2Sent;
	
	// init the hardware
	switch(S_CHANNEL)
	{
#ifdef _UART0_CHANNEL_
		case UART0_CHANNEL:
		{
			Uart_init();							
			Uart_TxInterruptEnable(HardWare_CallBack); 
			break;
		}
#endif
#ifdef _SPI0_CHANNEL_
		case SPI0_CHANNEL:
		{	
			Spi_Config my_spi={SPI_INTERRUPT_ENABLE,SPI_LSB_FIRST,SPI_MASTER_MODE,SPI_RAISING_EDGE,SPI_SAMPLE,SPI_FOSC_DIV128};
			spi_init(&my_spi);
			Spi_AssignCallBack(HardWare_CallBack);	
			spi_Tx(SPTR_DATA2SENT[0]); // sent the first element to make interrupt 
			// cannot make interrupt except this way 
			Scounter++; 
			break;		
		}
#endif
#ifdef _I2C0_CHANNEL_
		case I2C0_CHANNEL:
		{
			I2C_Init(I2C_TX); // init 
			I2C_Start(); // set start 
			I2C_TxWithInterrupt(0b11010000+0); // to do make the address a macro in comm_Tx_confg 
			I2C_AssignCallBackTx(HardWare_CallBack); // assign call back
			break;
		}
#endif
	}
}

static void Dissarm_HardwareInterrupt()
{
	/*
	* this fun static it called just here in this file 
	* to dissarm the channel which make the interrupts occures
	*/
	switch (S_CHANNEL)
	{
#ifdef _UART0_CHANNEL_
		case UART0_CHANNEL:
		{
			Uart_TxinterruptDisable();
			break;
		}
#endif
#ifdef _SPI0_CHANNEL_
		case SPI0_CHANNEL:
		{
			spi_InterruptDisable();	
			break;
		}
#endif
#ifdef _I2C0_CHANNEL_
		case I2C0_CHANNEL:
		{
			i2c_disable_interrupt();
			break;
		}
#endif
	}
}

void comm_TxDisspatcher()
{
	if (flage_Tx_Sending)
	{
		flage_Tx_Sending = 0;
		if (Scounter==NUM_BYTES)
		{ 
			/*
			*lock transmition until user funcation finish  
			*dissarm the interrupt of hardware
			* to do to make the interrupt faster just set the flage 
			* and let the dissaptcher do the jop of sending the next byte  
			*/
			Dissarm_HardwareInterrupt();
			CALLTX_FINIHS();
		}
	}
}



