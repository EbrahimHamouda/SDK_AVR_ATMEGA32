/*
* hw_types.h
*
*  Created on: 7/30/2018
*      Author: EbrahimHamouda
*/

#ifndef HW_TYPES_H_
#define HW_TYPES_H_

#define NULL ((void *)0)

#define INPUT  0
#define OUTPUT 1
#define HIGH   1
#define LOW    0

typedef unsigned char uint8;
typedef unsigned int  uint16;
typedef char int8;
typedef char* String;
typedef uint8 bool_t;



 
#define ACCESS_REG_8BIT(REG)         (*(volatile uint8*)REG)

#define READ_REG_8BIT(REG)           (*(volatile uint8*)(REG))

#define WRITE_REG_8BIT(REG,Val)      (ACCESS_REG_8BIT(REG))=(Val);

#define SET_BIT(REG,BIT_NUM)		 (ACCESS_REG_8BIT(REG)|=1<<(BIT_NUM))

#define CLEAR_BIT(REG,BIT_NUM)       (ACCESS_REG_8BIT(REG) &=(~(1<<(BIT_NUM))))

#define BIT_IS_SET(REG,BIT_NUM)      ((ACCESS_REG_8BIT(REG) & (1 << BIT_NUM)))

#define BIT_IS_CLEAR(REG,BIT_NUM)    (!(BIT_IS_SET(REG,BIT_NUM)))

#define TOGGLE_BIT(REG,BIT_NUM)  	 (ACCESS_REG_8BIT(REG) = ACCESS_REG_8BIT(REG) ^ (1<<BIT_NUM) )

/*********************************************
#define Min(x,y) ((x) < (y) ? (x) : (y))
#define Max(x,y) ((x) > (y) ? (x) : (y))
*******************************************/
#endif /* HW_TYPES_H_ */
