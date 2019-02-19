/*
* SPI.h
*
* Created: 7/30/2018 2:59:53 PM
*  Author: EbrahimHamouda
*/


#ifndef SPI_H_
#define SPI_H_

#include <common\ebra_common.h>
#include "HW_SPI.h"

typedef enum
{
	SPI_INTERRUPT_DISABLE,
	SPI_INTERRUPT_ENABLE
} Spi_InterruptType;

typedef enum
{
	SPI_LSB_FIRST,
	SPI_MSB_FIRST
} Spi_DataOrderType;

typedef enum
{
	SPI_SLAVE_MODE,
	SPI_MASTER_MODE
} Spi_ModeSelectType;

typedef enum
{
	SPI_RAISING_EDGE,
	SPI_FALLING_EDGE
} Spi_ClockPolarityType;


typedef enum
{
	SPI_SAMPLE,
	SPI_SETUP,
} Spi_ClockPhaseType;

typedef enum
{
	SPI_FOSC_DIV4,
	SPI_FOSC_DIV16,
	SPI_FOSC_DIV64,
	SPI_FOSC_DIV128,
} Spi_ClockSelectType;

typedef struct
{
	Spi_InterruptType		Interrupt;
	Spi_DataOrderType		DataOrder;
	Spi_ModeSelectType		ModeSelect;  
	Spi_ClockPolarityType   ClockPolarity;
	Spi_ClockPhaseType		ClockPhase;
	Spi_ClockSelectType		ClockSelect;         
} Spi_Config;

void spi_init(Spi_Config* ptr);

uint8 spi_ExchangeData(uint8 data);

uint8 spi_Rx();

void spi_Tx(uint8 data);

void Spi_AssignCallBack(void(*ptr_CallBackFun)(uint8));

void spi_InterruptDisable();

#endif /* SPI_H_ */

