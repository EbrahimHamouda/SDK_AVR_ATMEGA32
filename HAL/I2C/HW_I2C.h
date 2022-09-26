/*
 * HW_I2C.h
 *
 * Created: 7/30/2018 2:58:11 PM
 *  Author: ebrahim hamouda
 */ 


#ifndef HW_I2C_H_
#define HW_I2C_H_



#define I2C_BASE 

//offest 
#define I2CCONTROL
#define I2CSTATUS
#define I2CDATA
#define I2CADDRASS
#define I2CBITRATE
//

// BIT OFFEST >> CONTROL
#define I2CFLAGE     7
#define I2CACKBIT    6
#define I2CSTARTBIT  5
#define I2CSTOPBIT   4
#define I2CCOLFALGE  3
#define I2CENABLEBIT 2
#define I2CENABLEINT 0

// BIT OFFEST >> STATUS 
#define I2CSTATUS   3
#define I2CPRESCALE 0

#endif /* HW_I2C_H_ */