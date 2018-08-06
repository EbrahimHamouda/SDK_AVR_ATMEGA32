/*
 * I2C.h
 *
 * Created: 7/30/2018 3:00:02 PM
 *  Author: ebrahim 
 */ 


#ifndef I2C_H_
#define I2C_H_

#define I2C_WakeUp       	 SET_BIT((I2C_BASE+I2CCONTROL),I2CENABLEBIT)
#define I2C_START_EN     	 SET_BIT((I2C_BASE+I2CCONTROL),I2CSTARTBIT)
#define I2C_RESTART_EN	 	 SET_BIT((I2C_BASE+I2CCONTROL),I2CSTARTBIT)
#define I2C_STOP_EN		 	 SET_BIT((I2C_BASE+I2CCONTROL),I2CSTOPBIT)
#define I2C_ACK_SET  		 SET_BIT((I2C_BASE+I2CCONTROL),I2CACKBIT)
#define I2C_INTERRUPT_EN     SET_BIT((I2C_BASE+I2CCONTROL),I2CENABLEINT)
#define I2C_IDLE  			 BIT_IS_SET((I2C_BASE+I2CCONTROL),I2CFLAGE)
#define GenericBrodcast 	 0x00


void i2c_init();

void i2c_MasterTx(uint16 Slave_Addrass,uint8 Data);

void i2c_MasterRx(uint16 Slave_Addrass,uint8* Data);

void i2c_SlaveTx();

void i2c_SlaveRx();

#endif /* I2C_H_ */


// i2c is AND gate >>  if( 2master>> init data ) THEN 10v 
/*/

*bus arbatriation check 
*/