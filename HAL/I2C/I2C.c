/*
 * I2C.c
 *
 * Created: 3/12/2014 12:05:38 PM
 *  Author: Ebrahim Hamouda
 */ 
#include "I2C.h"

/* MACROS

*/
#define I2C_BUSY		(!(TWCR & (1 << TWINT)))  

 
void I2C_Init(void)
{
    // Bit Rate: 400.000 kHz
    TWBR=0x02;
	TWSR=0x00;
    // General Call Recognition: Off
    // Two Wire Bus address my address if any master device want to call me: 0x1 (used in case this MC is a slave device)
    TWAR=0b00000010; // my address=0x01 :) 
    TWCR=(1<<TWEN); //enable TWI
}

void I2C_Start(void)
{
    /* Clear the TWINT flag before sending the start bit TWINT=1 "MUST"
	 * send the start bit by TWSTA=1
	 * Enable TWI Module TWEN=1 
	 */	
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    // Wait for TWINT flag set in TWCR Register (start bit is send successfully) 
    while (I2C_BUSY);
}

void I2C_Stop(void)
{
    /* Clear the TWINT flag before sending the stop bit TWINT=1
	 * send the stop bit by TWSTO=1
	 * Enable TWI Module TWEN=1 
	 */
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);

}

void I2C_Write(unsigned char data)
{
    // Put data On TWI Register
    TWDR = data;
    /* Clear the TWINT flag before sending the data TWINT=1
	 * Enable TWI Module TWEN=1 
	 */ 
    TWCR = (1 << TWINT) | (1 << TWEN);
    // Wait for TWINT flag set in TWCR Register(data is send successfully) 
    while (I2C_BUSY);
}

unsigned char I2C_ReadWithACK(void)
{
	/* Clear the TWINT flag before reading the data TWINT=1
	 * enable sending ACK TWEA=1
	 * Enable TWI Module TWEN=1 
	 */ 
    TWCR = (1 << TWINT) | (1 << TWEN) | (1<<TWEA);
    // Wait for TWINT flag set in TWCR Register (data received successfully) 
    while (I2C_BUSY);
    // Read Data
    return TWDR;
}

unsigned char I2C_ReadWithNACK(void)
{
	/* Clear the TWINT flag before reading the data TWINT=1
	 * enable sending ACK TWEA=1
	 * Enable TWI Module TWEN=1 
	 */
    TWCR = (1 << TWINT) | (1 << TWEN);
    // Wait for TWINT flag set in TWCR Register (data received successfully) 
    while (I2C_BUSY);
    // Read Data
    return TWDR;
}

unsigned char I2C_GetStatus(void)
{
    unsigned char status;
    status = TWSR & 0xF8; //masking to eliminate first 3 bits 
    return status;
}
