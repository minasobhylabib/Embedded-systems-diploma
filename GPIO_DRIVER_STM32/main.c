/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
#warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif
#include "stm32f103c6.h"
#include "GPIO_driver.h"
void delay()
{
	unsigned int i;
	for(i=0;i<10000;i++);
}
void GPIO_init()
{
	clk_enable(GPIOA,RCC);
	clk_enable(GPIOB,RCC);
	GPIO_PinConfig_t PinConfig;
	PinConfig.GPIO_PinNumber = GPIO_PIN_1;
	PinConfig.GPIO_MODE = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init ( GPIOA, &PinConfig);

	PinConfig.GPIO_PinNumber = GPIO_PIN_1;
	PinConfig.GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	PinConfig.GPIO_Output_speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init ( GPIOB, &PinConfig);
	MCAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, 1);

	PinConfig.GPIO_PinNumber = GPIO_PIN_13;
	PinConfig.GPIO_MODE = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init ( GPIOA, &PinConfig);
	PinConfig.GPIO_PinNumber = GPIO_PIN_13;
	PinConfig.GPIO_MODE = GPIO_MODE_OUTPUT_PP ;
	PinConfig.GPIO_Output_speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init ( GPIOB, &PinConfig);
	MCAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, 1);

}




int main()
{
	GPIO_init();
	while(1)
	{
		if(MCAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1 )==0)
		{
			MCAL_GPIO_TogglePin(GPIOB, GPIO_PIN_1);
			delay();
			while(MCAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1 )==0);
		}

		if((MCAL_GPIO_ReadPin(GPIOA,GPIO_PIN_13 ))==1)
		{
			MCAL_GPIO_TogglePin(GPIOB, GPIO_PIN_13);
			delay();
		}


	}

}
