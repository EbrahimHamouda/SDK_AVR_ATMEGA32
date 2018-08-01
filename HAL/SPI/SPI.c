/*
* SPI.c
*
* Created: 7/30/2018 3:01:06 PM
*  Author: EbrahimHamouda
*/

#include "SPI.h"

#define SPI_IDLE BIT_IS_SET((SPI_BASE+SPISTATUSREG),SPIINTERRUPTFLAG)

void spi_init(Spi_Config* ptr)
{
	ACCESS_REG_8BIT((SPI_BASE+SPICONTROLREG))  =  0;
	ACCESS_REG_8BIT((SPI_BASE+SPICONTROLREG)) |=  (ptr->Interrup << SPIINTERRUPTBIT) | (ptr->DataOrder << SPIDATAORDERBIT) | (ptr->ModeSelect << SPIMODESELECTBIT) | (ptr->ClockPolarity << SPICLOCKPOLRITYBIT) | (ptr->ClockPhase << SPICLOCKPHASEBIT) | (ptr->ClockSelect << SPICLOCKSELECTBIT);
	ACCESS_REG_8BIT((SPI_BASE+SPICONTROLREG)) |= (1<<SPIENABLEBIT);
}

uint8 spi_master(uint8 data)
{
	WRITE_REG_8BIT((SPI_BASE+SPIDATAREG),data);
	while (!SPI_IDLE);
	return 1;
}

uint8 spi_slave(uint8 data)
{
	/*WRITE_REG_8BIT((SPI_BASE+SPIDATAREG),data);*/
	while (!SPI_IDLE);
	return ACCESS_REG_8BIT((SPI_BASE+SPIDATAREG));
}

