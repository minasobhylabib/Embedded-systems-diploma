/*
 * RCC.c
 *
 *  Created on: Feb 9, 2022
 *      Author: Mina
 */

#include "RCC.h"

const uint8_t APBprescalarTable[]={0,0,0,0,1,2,3,4};
const uint8_t AHBprescalarTable[]={0,0,0,0,0,0,0,0,1,2,3,4,6,7,8,9};
uint32_t MCAL_RCC_Get_SYS_clk_Freq(void)
{
	switch((RCC->CFGR >>2)&0b11)
	{
	case 0:
		return HSI_clock;
		break;
	case 1:
		return HSE_clock;
		break;
	default:
		//PLL
		return 16000000;
		break;
	}

}
uint32_t MCAL_RCC_Get_HCLK_Freq(void)
{
	return(MCAL_RCC_Get_SYS_clk_Freq()>>(AHBprescalarTable[(RCC->CFGR >>4)&0b1111]));

}
uint32_t MCAL_RCC_Get_PCLK1_Freq(void)
{
	return(MCAL_RCC_Get_HCLK_Freq()>>(APBprescalarTable[(RCC->CFGR >>8)&0b111]));
}
uint32_t MCAL_RCC_Get_PCLK2_Freq(void)
{
	return(MCAL_RCC_Get_HCLK_Freq()>>(APBprescalarTable[(RCC->CFGR >>11)&0b111]));

}

