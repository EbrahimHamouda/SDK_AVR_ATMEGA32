/*
* RTCDS1307.c
*
* Created: 4/29/2019 4:51:09 PM
*  Author: ebrah
*/
#include "RTCDS1307.h"



#define DEVICE_WRITE_ADDRESS	0xD0	/* Define RTC DS1307 slave write address */
#define DEVICE_READ_ADDRESS		0xD1	/* Make LSB bit high of slave address for read */
#define CONTRO_REG				0x07
#define SECONDS_REG				0x00
#define HOURS_REG				0x02
#define TIME_FORMAT_12			0x40	/* Define 12 hour format */
#define AMPM					0x20




bool_t IsItPM(char hour_)
{
	if(hour_ & (AMPM))
	return 1;
	else
	return 0;
}


void RTC_Init(void)
{
	I2C_Init(I2C_TX);                             // Initialize the I2c module.
	I2C_Start();                            // Start I2C communication
	I2C_Write(DEVICE_WRITE_ADDRESS);        // Connect to DS1307 by sending its ID on I2c Bus
	I2C_Write(CONTRO_REG);					// Select the Ds1307 ControlRegister to configure Ds1307
	I2C_Write(0x00);                        // Write 0x00 to Control register to disable SQW-Out
	I2C_Stop();                             // Stop I2C communication after initializing DS1307
}


void RTC_SetDateTime(rtc_t *rtc)
{
	I2C_Start();							  // Start I2C communication
	
	I2C_Write(DEVICE_WRITE_ADDRESS);		  // connect to DS1307 by sending its ID on I2c Bus
	I2C_Write(SECONDS_REG);   // Request sec RAM address at 00H
	
	I2C_Write(rtc->sec);				       // Write sec from RAM address 00H
	I2C_Write(rtc->min);				   	   // Write min from RAM address 01H
	I2C_Write(rtc->hour);					   // Write hour from RAM address 02H
	I2C_Write(rtc->weekDay);				   // Write weekDay on RAM address 03H
	I2C_Write(rtc->date);                      // Write date on RAM address 04H
	I2C_Write(rtc->month);                     // Write month on RAM address 05H
	I2C_Write(rtc->year);                      // Write year on RAM address 06h
	I2C_Stop();                                // Stop I2C communication after Setting the Date
}

void RTC_GetDateTime(rtc_t *rtc)
{
	I2C_Start();                            // Start I2C communication
	
	I2C_Write(DEVICE_WRITE_ADDRESS);        // connect to DS1307 by sending its ID on I2c Bus
	I2C_Write(SECONDS_REG); // Request Sec RAM address at 00H
	I2C_Stop();
		
	I2C_Start();                            // Start I2C communication
	I2C_Write(DEVICE_READ_ADDRESS);            // connect to DS1307(Read mode) by sending its ID
	
	rtc->sec = I2C_ReadWithACK();                // read second and return Positive ACK
	rtc->min = I2C_ReadWithACK();                 // read minute and return Positive ACK
	rtc->hour= I2C_ReadWithACK();               // read hour and return Negative/No ACK
	rtc->weekDay = I2C_ReadWithACK();           // read weekDay and return Positive ACK
	rtc->date= I2C_ReadWithACK();              // read Date and return Positive ACK
	rtc->month=I2C_ReadWithACK();            // read Month and return Positive ACK
	rtc->year =I2C_ReadWithNACK();             // read Year and return Negative/No ACK
	I2C_Stop();                              // Stop I2C communication after reading the Date
}

