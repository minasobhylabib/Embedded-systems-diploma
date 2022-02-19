/*
 * EEPROM.h
 *
 *  Created on: Feb 14, 2022
 *      Author: Mina
 */

#ifndef EEPROM_H_
#define EEPROM_H_
#include "I2C.h"
#define EEPROM_slave_address 0x2A
void EEPROM_init(void);
unsigned char EEPROM_write_nbytes(unsigned int memory_address, unsigned char* bytes, uint8_t length);
unsigned char EEPROM_read_byte(unsigned int address, unsigned char* dataout, uint8_t data_length);
#endif /* EEPROM_H_ */
