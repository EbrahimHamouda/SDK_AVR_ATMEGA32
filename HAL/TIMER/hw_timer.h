/*
 * HW_TIMER.h
 *
 * Created: 8/19/2018 6:19:35 AM
 *  Author: EbrahimHamouda
 */ 


#ifndef HW_TIMER_H_
#define HW_TIMER_H_

#define TCCBASE		(0x45)

// OFFEST

#define TCC0		(0x0e)
#define TCC1		(0x09)
#define TCC2		(0x00)
#define FLAG_R      (0x58)
#define MASK_R      (0x59)

//BITS OFFEST

#define FTIMER0  0
#define FTIMER1  2
#define FTIMER2  6

//
#define MTIMER0  0
#define MTIMER1	 2
#define MTIMER2  6

#endif /* HW_TIMER_H_ */