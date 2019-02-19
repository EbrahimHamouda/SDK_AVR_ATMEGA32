/*
* com.c
*
*  Created on: Aug 4, 2018
*      Author: EbrahimHamouda
*/

#include "commRX.h"

static uint8		  Rx_Buffer[MAX__SIZE]; // the buffer to RX in 
static uint16		  RX_Buffer_Index; // the index for buffer
static bool_t		  RX_FlageDataReciving;// flage to indicate the RX 
static bool_t		  Rx_LockBuffer;// to lock buffer while process
static RX_cfg_t static_RX_cnfg;

#define CALL_BACK_RX_COMPELETE_FUN static_RX_cnfg.ptr_user_fun
#define CHANNEL_SLECTE			   static_RX_cnfg.channel
#define CNFRMATION_LETTER		   static_RX_cnfg.cofm_letter

void RX_CommFree(void)
{
	/*
	* Buffer_index to zero to start new receiving in buffer
	* clear flage to stop dispatcher cheking untill first interrupt
	* Free buffer from locking to start save data
	*/
	RX_Buffer_Index = 0;   
	RX_FlageDataReciving =0; 
	Rx_LockBuffer=0;  // un lock the buffer
}

static void HardWare_CallBack(uint8 data)
{
	/*
	* check if the buffer lock first
	* set flage the new data received 
	* buffer the received data  
	*/
	
	RX_FlageDataReciving  = 1;					//set flage to make dispatcher look at the new data
	Rx_Buffer[RX_Buffer_Index++] = data;		//store in buffer and increament the index
}

void Comm_RxInit(RX_cfg_t* ptr_cfg_str)
{
/*
* check if the comm_busy or not 
* free the comm from pervious usage 
* save the confg in static variable 
* switch to the channel selected to set the hardware
*/

	RX_CommFree(); // make sure the buffer ready to start RX_in
	static_RX_cnfg.ptr_user_fun = ptr_cfg_str->ptr_user_fun;	// call user funcation
	static_RX_cnfg.channel		= ptr_cfg_str->channel;
	static_RX_cnfg.cofm_letter  = ptr_cfg_str->cofm_letter;

	switch(CHANNEL_SLECTE) //init the hardware
	{
#ifdef _UART0_ 
		case UART0:
		{
			Uart_init();
			Uart_RxInterruptEnable(HardWare_CallBack); 
			break;
		}
#endif
#ifdef _SPIO_
		case SPIO:
		{
			Spi_Config my_spi={SPI_INTERRUPT_ENABLE,SPI_LSB_FIRST,SPI_SLAVE_MODE,SPI_RAISING_EDGE,SPI_SAMPLE,SPI_FOSC_DIV128};
			spi_init(&my_spi);
			Spi_AssignCallBack(HardWare_CallBack);
			break;
		}
#endif
#ifdef _I2C0_
		case I2C0:
		{
			I2C_Init(I2C_RX);
			I2C_AssignCallBackRX(HardWare_CallBack);
			break;
		}
#endif
	}
}

void RX_com_dispatch() 
{
	/*
	* checking new data revceived 
	* To do -> state machine in "idle- recieving hadder - recieving data - reciecing Check sum "
	* do algorthim  of checking hadder 
	* do algorthim of checking check sum 
	* do algorthim of checking the confirmation letter
	*/
	if (RX_FlageDataReciving)			// check the flage 
	{

		 RX_FlageDataReciving=0;				// clear the flage to stop checking till next byte 
		 if (Rx_Buffer[RX_Buffer_Index-1] == static_RX_cnfg.cofm_letter)  // check the confirmation letter
		 {
			 Rx_Buffer[RX_Buffer_Index-1] = static_RX_cnfg.cofm_letter; // not needed 
			static_RX_cnfg.ptr_user_fun(Rx_Buffer,RX_Buffer_Index);	 // call application funcation to indicate the receiving finished
		 }
	}
}

