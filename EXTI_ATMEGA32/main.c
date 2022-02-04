typedef volatile unsigned char vuint_8;
#include "avr/interrupt.h"
#include "util/delay.h"
#include "avr/io.h"


#define MCUCR *(vuint_8*)(0x55)
#define MCUCSR *(vuint_8*)(0x54)
#define GICR *(vuint_8*)(0x5B)
#define SREG *(vuint_8*)(0x5F)
#define PORTB *(vuint_8*)(0x38)
#define DDRB *(vuint_8*)(0x37)
#define PORTD *(vuint_8*)(0x32)
#define PORTD_out *(vuint_8*)(0x12)
#define DDRD *(vuint_8*)(0x31)
#define DDRD_out *(vuint_8*)(0x11)
void main()
{
	DDRD |= 0b111<<5;
	PORTD |= 1<<6;
	MCUCR &= 0b0000;
	MCUCR |= 0b1101;
	MCUCSR &= ~ (1<<6);
	GICR |= 0b111<<5;
	SREG |= (1 << 7);
	//sei();
	/*PORTB &= ~ (1<<2);
	DDRB &= ~ (1<<2);
	PORTD &= 0b00<<2;
	DDRD &= 0b00<<2;*/
	
	
	while(1)
	{
		PORTD &= (0b000<<5);
	}
	
	
}

ISR(INT0_vect)
{
	PORTD |= 1<<5;
	_delay_ms(1000);
	
	
}
ISR(INT1_vect)
{
	PORTD |= 1<<6;
	_delay_ms(1000);
	
}
ISR(INT2_vect)
{
	PORTD |= 1<<7;
	_delay_ms(1000);
	
}

