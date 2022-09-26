/*
* SPI.c
*
* Created: 7/30/2018 3:01:06 PM
*  Author: EbrahimHamouda
*/
#include "avr/interrupt.h"
#include "SPI.h"

#define SPI_BUSY BIT_IS_CLEAR((SPI_BASE+SPISTATUSREG),SPIINTERRUPTFLAG)
#define dummy_data 0x52
static void(*static_PtrCallBackFun)(uint8); // the passed data in call_back work only for receiving 
static Spi_Config* static_ptr;

ISR(SPI_STC_vect)
{ // check for collision and read register if there !! 
	
	static_PtrCallBackFun((READ_REG_8BIT((SPI_BASE+SPIDATAREG)))); 
}


void spi_init(Spi_Config* ptr)
{
	static_ptr = ptr;
	//check pointer not null 
	ACCESS_REG_8BIT((SPI_BASE+SPICONTROLREG))  =  0; //clear register then set config 
	ACCESS_REG_8BIT((SPI_BASE+SPICONTROLREG)) |=  (ptr->Interrupt << SPIINTERRUPTBIT) | (ptr->DataOrder << SPIDATAORDERBIT) | (ptr->ModeSelect << SPIMODESELECTBIT) | (ptr->ClockPolarity << SPICLOCKPOLRITYBIT) | (ptr->ClockPhase << SPICLOCKPHASEBIT) | (ptr->ClockSelect << SPICLOCKSELECTBIT);
	ACCESS_REG_8BIT((SPI_BASE+SPICONTROLREG)) |= (1<<SPIENABLEBIT);	// wake up spi to work 
}


void spi_InterruptDisable()
{
	CLEAR_BIT((SPI_BASE+SPICONTROLREG),SPIINTERRUPTBIT);
}

uint8 spi_ExchangeData(uint8 data)
{  // check if slave it will be stucked here 
	WRITE_REG_8BIT((SPI_BASE+SPIDATAREG),data);
	while (SPI_BUSY);
	return READ_REG_8BIT((SPI_BASE+SPIDATAREG));
}

uint8 spi_Rx()
{
 	while (SPI_BUSY);
	return READ_REG_8BIT((SPI_BASE+SPIDATAREG));
}

void spi_Tx(uint8 data)
{
	WRITE_REG_8BIT((SPI_BASE+SPIDATAREG),data);
	while (SPI_BUSY);
}

void Spi_AssignCallBack(void(*ptr_CallBackFun)(uint8))
{
	static_PtrCallBackFun= ptr_CallBackFun ;
}


