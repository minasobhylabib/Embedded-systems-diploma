/*
 * EEPROM.c
 *
 *  Created on: Feb 14, 2022
 *      Author: Mina
 */
#include "EEPROM.h"
I2C_config_t config;
void EEPROM_init(void)
{

	config.I2C_CLK_speed=I2C_SCLK_100k;
	config.I2C_mode = I2C_mode_I2C;
	config.ack_control=ack_enable;
	config.general_call_address_detection=general_call_address_enable;
	config.stretch_mode=clk_stretch_mode_enabled;
	config.p_slave_event_callback=NULL;
	MCAL_I2C_INIT(I2C1, &config);
	MCAL_I2C_SET_GPIO_PINS(I2C1);
}
unsigned char EEPROM_write_nbytes(unsigned int memory_address, unsigned char* bytes, uint8_t length)
{
	uint8_t buffer[256];
	buffer[0]=(uint8_t)(memory_address>>8);
	buffer[1]=(uint8_t)memory_address;
	int i;
	for(i=2;i<length+2;i++)
	{
		buffer[i]=bytes[i-2];
	}
	MCAL_I2C_MASTER_TX(I2C1, EEPROM_slave_address, buffer, length+2, with_stop, start);
	return 0;
}
unsigned char EEPROM_read_byte(unsigned int address, unsigned char* dataout, uint8_t data_length)
{
	uint8_t buffer[2];
	buffer[0]=(uint8_t)(address>>8);
	buffer[1]=(uint8_t)address;
	MCAL_I2C_MASTER_TX(I2C1, EEPROM_slave_address, buffer, 2, without_stop, start);
	MCAL_I2C_MASTER_RX(I2C1,&config, EEPROM_slave_address, dataout, data_length, with_stop, repeated_start);
	return 0;
}


