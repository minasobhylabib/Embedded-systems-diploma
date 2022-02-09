#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
// register address
#define GPIOA_BASE 0x40010800
#define GPIOA_CRL *(volatile uint32_t *)(GPIOA_BASE + 0x0)
#define GPIOA_CRH *(volatile uint32_t *)(GPIOA_BASE + 0x04)
#define GPIOA_ODR *(volatile uint32_t *)(GPIOA_BASE + 0x0C)
#define GPIOA_IDR *(volatile uint32_t *)(GPIOA_BASE + 0x08)

#define GPIOB_BASE 0x40010C00
#define GPIOB_CRL *(volatile uint32_t *)(GPIOB_BASE + 0x0)
#define GPIOB_CRH *(volatile uint32_t *)(GPIOB_BASE + 0x04)
#define GPIOB_ODR *(volatile uint32_t *)(GPIOB_BASE + 0x0C)

#define RCC_CR  *(volatile uint32_t *)(RCC_BASE + 0x0)
#define RCC_BASE 0x40021000
#define RCC_APB2ENR  *(volatile uint32_t *)(RCC_BASE + 0x18)



void clock_init()
{
	//Enable clk GPIOA
	RCC_APB2ENR |= 1<<2;
	//Enable clk GPIOB
	RCC_APB2ENR |= 1<<3;
}
void GPIO_init()
{
	// Set portA1 to input floating
	GPIOA_CRL &= 0b0000<<4;
	GPIOA_CRL |= 0b0100<<4;
	// Set portA13 to input floating
	GPIOA_CRH &= 0b0000<<20;
	GPIOA_CRH |= 0b0100<<20;
	// Set portB1 to output push pull
	GPIOB_CRL &= 0b0000<<4;
	GPIOB_CRL |= 0b0010<<4;
	// Set portB13 to output push pull
	GPIOB_CRH &= 0b0000<<20;
	GPIOB_CRH |= 0b0010<<20;
	// Set output ports
	GPIOB_ODR |= 1<<1;
	GPIOB_ODR |= 1<<13;
}
void delay()
{
	unsigned int i;
	for(i=0;i<10000;i++);
}
int main(void)
{
	clock_init();
	GPIO_init();
	while(1)
	{
		if((((GPIOA_IDR & (1<<1)) >>1)) ==0)
		{
			GPIOB_ODR ^=(1<<1);
			delay();
			while((((GPIOA_IDR & (1<<1)) >>1)) ==0);
		}

		if(((GPIOA_IDR & (1<<13))>>13) ==1)
		{
			GPIOB_ODR ^=(1<<13);
			delay();

		}


	}

}
