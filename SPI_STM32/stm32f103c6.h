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
#define NVIC_ISER0     *( uint32_t*)(NVIC_base + 0x0)
#define NVIC_ISER1     *( uint32_t*)(NVIC_base + 0x4)
#define NVIC_ISER2     *( uint32_t*)(NVIC_base + 0x8)
#define NVIC_ICER0     *( uint32_t*)(NVIC_base + 0x80)
#define NVIC_ICER1     *( uint32_t*)(NVIC_base + 0x84)
#define NVIC_ICER2     *( uint32_t*)(NVIC_base + 0x88)

//-----------------------------
//Base addresses for APB1 Peripherals
//-----------------------------
#define USART2_base			 (0x40004400)
#define USART3_base			 (0x40004800)
#define SPI2_base			 (0x40003800)
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

#define SPI1_base			 (0x40013000)

#define AFIO_base            (0x40010000)

#define USART1_base			 (0x40013800)


//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: GPIO
//-*-*-*-*-*-*-*-*-*-*-*


typedef struct {
	uint32_t CRL;
	uint32_t CRH;
	uint32_t IDR;
	uint32_t ODR;
	uint32_t BSRR;
	uint32_t BRR;
	uint32_t LCKR;
}GPIO_TYPEDEF;


//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: RCC
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct {
	uint32_t CR;
	uint32_t CFGR;
	uint32_t CIR;
	uint32_t APB2RSTR;
	uint32_t APB1RSTR;
	uint32_t AHBENR;
	uint32_t APB2ENR;
	uint32_t APB1ENR;
	uint32_t BDCR;
	uint32_t CSR;
}RCC_TYPEDEF;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: EXTI
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct {
	uint32_t IMR;
	uint32_t EMR;
	uint32_t RTSR;
	uint32_t FTSR;
	uint32_t SWIER;
	uint32_t PR;
}EXTI_TYPEDEF;
//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: AFIO
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct {
	uint32_t EVCR;
	uint32_t MAPR;
	uint32_t EXTICR[4];
	uint32_t RESERVED;
	uint32_t MAPR2;
}AFIO_TYPEDEF;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: USART
//-*-*-*-*-*-*-*-*-*-*-*

typedef struct {
	uint32_t SR;
	uint32_t DR;
	uint32_t BRR;
	uint32_t CR1;
	uint32_t CR2;
	uint32_t CR3;
	uint32_t GTPR;
}USART_TYPEDEF;


//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: SPI
//-*-*-*-*-*-*-*-*-*-*-*

typedef struct {
	uint32_t CR1;
	uint32_t CR2;
	uint32_t SR;
	uint32_t DR;
	uint32_t CRCPR;
	uint32_t RXCRCR;
	uint32_t TXCRCR;
	uint32_t I2SCFGR;
	uint32_t I2SPR;
}SPI_TYPEDEF;

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

#define USART1 ((USART_TYPEDEF*)USART1_base)
#define USART2 ((USART_TYPEDEF*)USART2_base)
#define USART3 ((USART_TYPEDEF*)USART3_base)

#define SPI1 ((SPI_TYPEDEF*)SPI1_base)
#define SPI2 ((SPI_TYPEDEF*)SPI2_base)

//-*-*-*-*-*-*-*-*-*-*-*-
//clock enable Macros:
//-*-*-*-*-*-*-*-*-*-*-*
#define clk_enable_AFIO()   (RCC->APB2ENR |= 1<<0)
#define clk_enable_USART1() (RCC->APB2ENR |= 1<<14)
#define clk_enable_USART2() (RCC->APB1ENR |= 1<<17)
#define clk_enable_USART3() (RCC->APB1ENR |= 1<<18)
#define clk_enable_SPI1() 	(RCC->APB2ENR |= 1<<12)
#define clk_enable_SPI2() 	(RCC->APB1ENR |= 1<<14)
//-*-*-*-*-*-*-*-*-*-*-*-
//clock disable Macros:
//-*-*-*-*-*-*-*-*-*-*-*
#define clk_disable_USART1()  (RCC->APB2RSTR |= 1<<14)
#define clk_disable_USART2()  (RCC->APB1RSTR |= 1<<17)
#define clk_disable_USART3()  (RCC->APB1RSTR |= 1<<18)
#define clk_disable_SPI1()    (RCC->APB2RSTR |= 1<<12)
#define clk_disable_SPI2()    (RCC->APB1RSTR |= 1<<14)
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

#define USART1_IRQ  37
#define USART2_IRQ  38
#define USART3_IRQ  39

#define SPI1_IRQ    35
#define SPI2_IRQ    36

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

#define NVIC_USART1_IRQ_ENABLE		(NVIC_ISER1 |= 1<<5)
#define NVIC_USART2_IRQ_ENABLE		(NVIC_ISER1 |= 1<<6)
#define NVIC_USART3_IRQ_ENABLE		(NVIC_ISER1 |= 1<<7)

#define NVIC_USART1_IRQ_DISABLE 	(NVIC_ICER1 |= 1<<5)
#define NVIC_USART2_IRQ_DISABLE 	(NVIC_ICER1 |= 1<<6)
#define NVIC_USART3_IRQ_DISABLE 	(NVIC_ICER1 |= 1<<7)

#define NVIC_SPI1_IRQ_ENABLE		(NVIC_ISER1 |= 1<<3)
#define NVIC_SPI2_IRQ_ENABLE		(NVIC_ISER1 |= 1<<4)

#define NVIC_SPI1_IRQ_DISABLE 		(NVIC_ICER1 |= 1<<3)
#define NVIC_SPI2_IRQ_DISABLE 		(NVIC_ICER1 |= 1<<4)

#endif /* INCLUDE_STM32F103C6_H_ */
