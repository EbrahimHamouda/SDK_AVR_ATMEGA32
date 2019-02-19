/*
 * I2C.h
 *
 * Created: 3/12/2014 12:05:49 PM
 *  Author: Ebrahin hamouda 
 */ 


#ifndef I2C_H_
#define I2C_H_

#include<avr/io.h>

/* STATUS VALUES */
typedef void(*Call_backTX_t)(void);
typedef	void(*Call_backRecive_t)(unsigned char);

#define TW_START         0x08 // start has been sent
#define TW_REP_START     0x10 // repeated start 
#define TW_MT_SLA_W_ACK  0x18 // ( slave address + Write have been sent ) + Ack received from slave
#define TW_MT_SLA_R_ACK  0x40 // ( slave address + Read have been sent ) + Ack received from slave
#define TW_MT_DATA_ACK   0x28 // Data byte has been transmitted and ACK has been received from Slave.
#define TW_MR_DATA_ACK   0x50 // Master received data and send ACK
#define TW_MR_DATA_NACK  0x58 // MAster received data but don't send ACK

typedef enum
{
I2C_RX,
I2C_TX
} I2c_Status_t;


void I2C_Init(I2c_Status_t i2c_passStatus);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_Write(unsigned char data);
void I2C_TxWithInterrupt(unsigned char data);
unsigned char I2C_ReadWithACK(void); //read with send Ack
unsigned char I2C_ReadWithACKAndInterrupt(void);//read with send Ack && interrupt enable 
void I2C_AssignCallBackRX(Call_backRecive_t pass_callBack);
unsigned char I2C_ReadWithNACK(void); //read without send Ack
unsigned char I2C_GetStatus(void);
void I2C_AssignCallBackTx(Call_backTX_t pass_callBackFuncation);
void i2c_disable_interrupt();

#endif /* I2C_H_ */