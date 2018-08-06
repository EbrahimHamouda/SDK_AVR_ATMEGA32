/*
* HW_SPI.h
*
* Created: 7/30/2018 2:57:47 PM
*  Author: ebrahim
	Design : ahmed yusri 
*/


#ifndef HW_SPI_H_
#define HW_SPI_H_

#define SPI_BASE       0x2d
//OFFEST REGS
#define SPICONTROLREG  0x00
#define SPISTATUSREG   0x01
#define SPIDATAREG     0x02

//OFFEST CONTRIL BITS
#define SPIINTERRUPTBIT		7 
#define SPIENABLEBIT		6
#define SPIDATAORDERBIT		5
#define SPIMODESELECTBIT	4
#define SPICLOCKPOLRITYBIT	3
#define SPICLOCKPHASEBIT	2
#define SPICLOCKSELECTBIT   0

//OFFEST SATUTS BITS
#define SPIINTERRUPTFLAG    7
#define SPIWRITCOLLFLAG     6
#endif /* HW_SPI_H_ */

















