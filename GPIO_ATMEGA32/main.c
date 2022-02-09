typedef volatile unsigned char vuint_8;

#include "avr/io.h"
#include "util/delay.h"
#define PORTD *(vuint_8*)(0x32)
#define DDRD *(vuint_8*)(0x31)
void delay()
{
	unsigned int i;
	for(i=0;i<100000;i++);
}
void main(void)
{
	DDRD |= 0b1111<<4;
	while(1)
	{
		PORTD |= 1<<7;
		_delay_ms(1000);
		PORTD &= ~(1<<7);
		_delay_ms(1000);
		PORTD |= 1<<6;
		_delay_ms(1000);
		PORTD &= ~(1<<6);
		_delay_ms(1000);
		PORTD |= 1<<5;
		_delay_ms(1000);
		PORTD &= ~(1<<5);
		_delay_ms(1000);
		PORTD |= 1<<4;
		_delay_ms(1000);
		PORTD &= ~(1<<4);
		_delay_ms(1000);
	}
}

