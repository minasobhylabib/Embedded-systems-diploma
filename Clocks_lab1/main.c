#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
// register address
#define GPIOA_BASE 0x40010800
#define GPIOA_CRH *(volatile uint32_t *)(GPIOA_BASE + 0x04)
#define GPIOA_ODR *(volatile uint32_t *)(GPIOA_BASE + 0x0C)
#define RCC_BASE 0x40021000
#define RCC_APB2ENR  *(volatile uint32_t *)(RCC_BASE + 0x18)
#define RCC_CR  *(volatile uint32_t *)(RCC_BASE + 0x0)
#define RCC_CFGR  *(volatile uint32_t *)(RCC_BASE + 0x4)

int main(void)
{
//Init GPIOA
	RCC_CR |= (1<<0);
	RCC_CFGR &= 0xFFFFFF0F ;
	RCC_CFGR &= 0xFFFFF8FF ;
	RCC_CFGR |= 4<<8;
	RCC_CFGR &= 0xFFFC7FF ;
	RCC_CFGR |= 5<<11;
	RCC_APB2ENR |= 1<<2;
GPIOA_CRH &= 0xFF0FFFFF;
GPIOA_CRH |= 0x00200000;
while(1)
{
GPIOA_ODR |= 1<<13 ;
for (int i = 0; i < 5000; i++); // arbitrary delay
GPIOA_ODR &= ~(1<<13) ;
for (int i = 0; i < 5000; i++); // arbitrary delay
}
}
