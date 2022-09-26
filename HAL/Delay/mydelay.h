/*
 * delay.h
 *
 *  Created on: Aug 4, 2017
 *  *      Author: Ebrahim Hamouda
 *
 */

#ifndef MYDELAY_H_
#define MYDELAY_H_
#include "Data_Types.h"


// the "NOP" takes 1 Cycle only

#define clock   1000000
#define error_ratio 30
uint32 DelayCount;

#define DELAY_MS(x) \
		for( DelayCount = ((clock/1000)*x/error_ratio); DelayCount >0; DelayCount--)\
			{\
				__asm("NOP");\
			}


#endif /* MYDELAY_H_ */
