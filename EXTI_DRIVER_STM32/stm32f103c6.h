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
#define FLASH_Memory_base                              (0X08000000)
#define System_Memory_base                             (0x1FFFF000)
#define SRAM_base                                      (0x20000000)
#define Peripheral_base                                (0x40000000)
#define Cortex_M3_Internal_Peripheral_base             (0xE0000000)
//NVIC
#define NVIC_base	   (0xE000E100)
#define NVIC_ISER0     *(volatile uint32_t*)(NVIC_base + 0x0)
#define NVIC_ISER1     *(volatile uint32_t*)(NVIC_base + 0x4)
#define NVIC_ISER2     *(volatile uint32_t*)(NVIC_base + 0x8)
#define NVIC_ICER0     *(volatile uint32_t*)(NVIC_base + 0x80)
#define NVIC_ICER1     *(volatile uint32_t*)(NVIC_base + 0x84)
#define NVIC_ICER2     *(volatile uint32_t*)(NVIC_base + 0x88)

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
	volatile uint32_t EXTICR[4];
	uint32_t RESERVED;
	volatile uint32_t MAPR2;
}AFIO_TYPEDEF;







//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants:
//-*-*-*-*-*-*-*-*-*-*-*
#define GPIOA  ((GPIO_TYPEDEF *)GPIOA_BASE)
#define GPIOB  ((GPIO_TYPEDEF *)GPIOB_BASE)
#define GPIOC  ((GPIO_TYPEDEF *)GPIOC_BASE)
#define GPIOD  ((GPIO_TYPEDEF *)GPIOD_BASE)
#define GPIOE  ((GPIO_TYPEDEF *)GPIOE_BASE)

#define RCC    ((RCC_TYPEDEF *)RCCBase)
#define EXTI   ((EXTI_TYPEDEF *)EXT_base)
#define AFIO   ((AFIO_TYPEDEF *)AFIO_base)

//-*-*-*-*-*-*-*-*-*-*-*-
//clock enable Macros:
//-*-*-*-*-*-*-*-*-*-*-*
#define clk_enable_AFIO (RCC->APB2ENR |= 1<<0)
//Generic Macros:
//-*-*-*-*-*-*-*-*-*-*-*
//IVT
//-*-*-*-*-*-*-*-*-*-*-*
#define EXTI0_IRQ	6
#define EXTI1_IRQ	7
#define EXTI2_IRQ	8
#define EXTI3_IRQ	9
#define EXTI4_IRQ	10
#define EXTI5_IRQ	23
#define EXTI6_IRQ	23
#define EXTI7_IRQ	23
#define EXTI8_IRQ	23
#define EXTI9_IRQ	23
#define EXTI10_IRQ	40
#define EXTI11_IRQ	40
#define EXTI12_IRQ	40
#define EXTI13_IRQ	40
#define EXTI14_IRQ	40
#define EXTI15_IRQ	40

#define NVIC_EXTI0_IRQ_ENABLE		(NVIC_ISER0 |= 1<<6)
#define NVIC_EXTI1_IRQ_ENABLE		(NVIC_ISER0 |= 1<<7)
#define NVIC_EXTI2_IRQ_ENABLE		(NVIC_ISER0 |= 1<<8)
#define NVIC_EXTI3_IRQ_ENABLE		(NVIC_ISER0 |= 1<<9)
#define NVIC_EXTI4_IRQ_ENABLE		(NVIC_ISER0 |= 1<<10)
#define NVIC_EXTI5_9_IRQ_ENABLE	    (NVIC_ISER0 |= 1<<23)
#define NVIC_EXTI10_15_IRQ_ENABLE	(NVIC_ISER1 |= 1<<8)

#define NVIC_EXTI0_IRQ_DISABLE		(NVIC_ICER0 |= 1<<6)
#define NVIC_EXTI1_IRQ_DISABLE		(NVIC_ICER0 |= 1<<7)
#define NVIC_EXTI2_IRQ_DISABLE		(NVIC_ICER0 |= 1<<8)
#define NVIC_EXTI3_IRQ_DISABLE		(NVIC_ICER0 |= 1<<9)
#define NVIC_EXTI4_IRQ_DISABLE		(NVIC_ICER0 |= 1<<10)
#define NVIC_EXTI5_9_IRQ_DISABLE	(NVIC_ICER0 |= 1<<23)
#define NVIC_EXTI10_15_IRQ_DISABLE	(NVIC_ICER1 |= 1<<8)





#endif /* INCLUDE_STM32F103C6_H_ */
