/*
 * eeprom.h
 *
 * Created: 2/22/2019 10:55:44 PM
 *  Author: ebrah
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_

void EEPROM_write(unsigned int uiAddress, unsigned char ucData);

unsigned char EEPROM_read(unsigned int uiAddress);



#endif /* EEPROM_H_ */