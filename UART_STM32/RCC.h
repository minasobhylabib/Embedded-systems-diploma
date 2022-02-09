/*
 * RCC.h
 *
 *  Created on: Feb 9, 2022
 *      Author: Mina
 */

#ifndef STM32_DRIVERS_INC_RCC_H_
#define STM32_DRIVERS_INC_RCC_H_
#include "stm32f103c6.h"
#include "GPIO_driver.h"

#define HSI_clock 	(uint32_t)8000000
#define HSE_clock 	(uint32_t)16000000

uint32_t MCAL_RCC_Get_SYS_clk_Freq(void);
uint32_t MCAL_RCC_Get_HCLK_Freq(void);
uint32_t MCAL_RCC_Get_PCLK1_Freq(void);
uint32_t MCAL_RCC_Get_PCLK2_Freq(void);


#endif /* STM32_DRIVERS_INC_RCC_H_ */
