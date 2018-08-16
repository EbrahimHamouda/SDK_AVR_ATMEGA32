/*
* hw_gpio.h
*
* Created: 7/13/2018 7:52:28 PM
*  Author: EbrahimHamouda .
*/


#ifndef HW_GPIO_H_
#define HW_GPIO_H_


#define BASE_A 0x39
#define BASE_B 0x36
#define BASE_C 0x33
#define BASE_D 0x30



/*
Offset.
*/
#define GPIOINDATA	0x00
#define GPIODIR		0x01
#define GPIOOUTDATA 0x02

// pins

#define  A0	    (0)
#define  A1	    (1)
#define  A2		(2)
#define  A3		(3)
#define  A4		(4)
#define  A5		(5)
#define  A6		(6)
#define  A7		(7)

#define  B0		(8)
#define  B1		(9)
#define  B2		(10)
#define  B3		(11)
#define  B4		(12)
#define  B5		(13)
#define  B6		(14)
#define  B7		(15)

#define  C0		(16)
#define  C1		(17)
#define  C2		(18)
#define  C3		(19)
#define  C4		(20)
#define  C5		(21)
#define  C6		(22)
#define  C7		(23)

#define  D0		(24)
#define  D1		(25)
#define  D2		(26)
#define  D3		(27)
#define  D4		(28)
#define  D5		(29)
#define  D6		(30)
#define  D7		(31)
#endif /* HW_GPIO_H_ */