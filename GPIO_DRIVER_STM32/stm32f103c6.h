/*
 * stm32f103c6.h
 *
 *  Created on: Feb 3, 2022
 *      Author: Mina
 */

#ifndef INCLUDE_STM32F103C6_H_
#define INCLUDE_STM32F103C6_H_
//-----------------------------
//Includes
#include "stdlib.h"
#include "stdint.h"
//-----------------------------
//-----------------------------
//Base addresses for Memories
//-----------------------------
#define FLASH_Memory_base                              0X08000000
#define System_Memory_base                             0x1FFFF000
#define SRAM_base                                      0x20000000
#define Peripheral_base                                0x40000000
#define Cortex_M3_Internal_Peripheral_base             0xE0000000

//-----------------------------
//Base addresses for APB2 Peripherals
//-----------------------------
#define GPIOA_BASE           (Peripheral_base + 0X00010800)
#define GPIOB_BASE           (Peripheral_base + 0X00010C00)
//C,D NOT INCLUDED IN LQFP48 PACKAGE
#define GPIOC_BASE           (Peripheral_base + 0X00011000)
#define GPIOD_BASE           (Peripheral_base + 0X00011400)
#define GPIOE_BASE           (Peripheral_base + 0X00011800)

#define RCCBase			     (0X40021000)
#define EXT_base			 (0x40010400)

#define AFIO_base            (0x40010000)
//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: GPIO
//-*-*-*-*-*-*-*-*-*-*-*


typedef struct {
	volatile uint32_t CRL;
	volatile uint32_t CRH;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t BRR;
	volatile uint32_t LCKR;
}GPIO_TYPEDEF;


//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: RCC
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct {
	volatile uint32_t CR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t APB2RSTR;
	volatile uint32_t APB1RSTR;
	volatile uint32_t AHBENR;
	volatile uint32_t APB2ENR;
	volatile uint32_t APB1ENR;
	volatile uint32_t BDCR;
	volatile uint32_t CSR;
}RCC_TYPEDEF;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: EXTI
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct {
	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RTSR;
	volatile uint32_t FTSR;
	volatile uint32_t SWIER;
	volatile uint32_t PR;
}EXTI_TYPEDEF;
//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: AFIO
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct {
	volatile uint32_t EVCR;
	volatile uint32_t MAPR;
	volatile uint32_t EXTICR1;
	volatile uint32_t EXTICR2;
	volatile uint32_t EXTICR3;
	volatile uint32_t EXTICR4;
	uint32_t RESERVED;
	volatile uint32_t MAPR2;
}AFIO_TYPEDEF;







//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants:
//-*-*-*-*-*-*-*-*-*-*-*
#define GPIOA  (GPIO_TYPEDEF *)(GPIOA_BASE)
#define GPIOB  (GPIO_TYPEDEF *)(GPIOB_BASE)
#define GPIOC  (GPIO_TYPEDEF *)(GPIOC_BASE)
#define GPIOD  (GPIO_TYPEDEF *)(GPIOD_BASE)
#define GPIOE  (GPIO_TYPEDEF *)(GPIOE_BASE)

#define RCC  (RCC_TYPEDEF *)(RCCBase)


#define EXTI   (EXTI_TYPEDEF *)(EXT_base)
#define AFIO   (AFIO_TYPEDEF *)(AFIO_base)
//-*-*-*-*-*-*-*-*-*-*-*-
//clock enable Macros:
//-*-*-*-*-*-*-*-*-*-*-*

//Generic Macros:
//-*-*-*-*-*-*-*-*-*-*-*









#endif /* INCLUDE_STM32F103C6_H_ */
