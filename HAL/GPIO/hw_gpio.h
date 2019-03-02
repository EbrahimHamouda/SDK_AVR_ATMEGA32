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

// pins_num
 typedef enum
 {
  A0 = 0,
  A1	, 
  A2	,	
  A3	,	
  A4	,	
  A5	,	
  A6	,	
  A7	,	

  B0	,	
  B1	,	
  B2	,	
  B3	,	
  B4	,	
  B5	,
  B6	,
  B7	,	

  C0	,	
  C1	,	
  C2	,	
  C3	,	
  C4	,
  C5	,	
  C6	,	
  C7	,

  D0	,	
  D1	,	
  D2	,	
  D3	,	
  D4	,	
  D5	,	
  D6	,	
  D7	,	
 } enum_PinsNum_t; 
#endif /* HW_GPIO_H_ */