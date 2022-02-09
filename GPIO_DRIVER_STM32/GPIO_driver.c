/*
 * GPIO_driver.c
 *
 *  Created on: Feb 3, 2022
 *      Author: Mina
 */

#include "GPIO_driver.h"

#define set_bit(reg,bit) (reg |= 1<<bit)
#define clear_bit(reg,bit) (reg &= ~( 1<<bit))

uint8_t get_CRLH_position(uint16_t PinNumber)
{
	switch (PinNumber)
	{
	case GPIO_PIN_0:
		return 0;
		break;
	case GPIO_PIN_1:
		return 4;
		break;
	case GPIO_PIN_2:
		return 8;
		break;
	case GPIO_PIN_3:
		return 12;
		break;
	case GPIO_PIN_4:
		return 16;
		break;
	case GPIO_PIN_5:
		return 20;
		break;
	case GPIO_PIN_6:
		return 24;
		break;
	case GPIO_PIN_7:
		return 28;
		break;

	case GPIO_PIN_8:
		return 0;
		break;
	case GPIO_PIN_9:
		return 4;
		break;
	case GPIO_PIN_10:
		return 8;
		break;
	case GPIO_PIN_11:
		return 12;
		break;
	case GPIO_PIN_12:
		return 16;
		break;
	case GPIO_PIN_13:
		return 20;
		break;
	case GPIO_PIN_14:
		return 24;
		break;
	case GPIO_PIN_15:
		return 28;
		break;

	}
	return 0;
}
//-----------------------------
//Macros Configuration References
//-----------------------------
/*@ref Module_REF_NAME_define
 */
/*
 * ===============================================
 *
 * APIs Supported by "MCAL GPIO DRIVER"
 * ===============================================
 */
/**================================================================
 * @Fn-				MCAL_GPIO_Init
 * @brief -			initialize the GPIOx PINy according to the specified parameters in the pinConfig
 * @param [in] -	    GPIOx where x can be (A, B, c, D or E)
 * @param [in] -		PinConfig: pointer to structure contains the configurations of the pin
 * @retval -	        none
 * Note-
 */
void clk_enable(GPIO_TYPEDEF* GPIOx, RCC_TYPEDEF* rcc)
{
	if( GPIOx== GPIOA)
		set_bit(rcc->APB2ENR,2);
	else if( GPIOx== GPIOB)
		set_bit(rcc->APB2ENR,3);
	else if( GPIOx== GPIOC)
		set_bit(rcc->APB2ENR,4);
	else if( GPIOx== GPIOD)
		set_bit(rcc->APB2ENR,5);
	else if( GPIOx== GPIOE)
		set_bit(rcc->APB2ENR,6);
}
void MCAL_GPIO_Init (GPIO_TYPEDEF* GPIOx, GPIO_PinConfig_t* PinConfig)
{
	volatile uint32_t* config = NULL;
	uint8_t pin_config =0;
	config = ((PinConfig->GPIO_PinNumber) < (GPIO_PIN_8))? &GPIOx->CRL : &GPIOx->CRH;
	(*config) &= ~(0xF << get_CRLH_position(PinConfig->GPIO_PinNumber));
	if((PinConfig->GPIO_MODE ==GPIO_MODE_OUTPUT_PP)||(PinConfig->GPIO_MODE ==GPIO_MODE_OUTPUT_OD)||(PinConfig->GPIO_MODE ==GPIO_MODE_OUTPUT_AF_PP)||(PinConfig->GPIO_MODE ==GPIO_MODE_OUTPUT_AF_OD))
	{
		pin_config = ((PinConfig->GPIO_MODE - 4)<<2) | ((PinConfig->GPIO_Output_speed) );

	}else
	{
		if((PinConfig->GPIO_MODE ==GPIO_MODE_INPUT_FLO)||(PinConfig->GPIO_MODE ==GPIO_MODE_ANALOG))
		{
			pin_config = (PinConfig->GPIO_MODE<<2);
		}
		else if(PinConfig->GPIO_MODE == GPIO_MODE__AF_INPUT)
		{
			pin_config = GPIO_MODE_INPUT_FLO <<2;
		}

		else if(PinConfig->GPIO_MODE ==GPIO_MODE_INPUT_PU)
		{
			pin_config = PinConfig->GPIO_MODE<<2;
			GPIOx->ODR |= PinConfig->GPIO_PinNumber;
		}
		else
		{
			pin_config = 2<<2;
			GPIOx->ODR &= ~ PinConfig->GPIO_PinNumber;
		}
	}
	(*config)|= (pin_config <<get_CRLH_position(PinConfig->GPIO_PinNumber));
}



/**================================================================
 * @Fn-
 * @brief -
 * @param [in] -
 * @param [out] -
 * @retval -
 * Note-
 */
void MCAL_GPIO_reset (GPIO_TYPEDEF* GPIOx, RCC_TYPEDEF* rcc)
{
	if(GPIOx==GPIOA)
	{

		set_bit(rcc->APB2RSTR,2);
		clear_bit(rcc->APB2RSTR,2);
	}
	else if(GPIOx==GPIOB)
	{
		set_bit(rcc->APB2RSTR,3);
		clear_bit(rcc->APB2RSTR,3);
	}
	else if(GPIOx==GPIOC)
	{
		set_bit(rcc->APB2RSTR,4);
		clear_bit(rcc->APB2RSTR,4);
	}
	else if(GPIOx==GPIOD)
	{
		set_bit(rcc->APB2RSTR,5);
		clear_bit(rcc->APB2RSTR,5);
	}
	else if(GPIOx==GPIOE)
	{
		set_bit(rcc->APB2RSTR,6);
		clear_bit(rcc->APB2RSTR,6);
	}
}
/**================================================================
 * @Fn-
 * @brief -
 * @param [in] -
 * @param [out] -
 * @retval -
 * Note-
 */
uint8_t MCAL_GPIO_ReadPin(GPIO_TYPEDEF* GPIOx, uint16_t PinNumber)
{
	uint8_t bit_status;


	if(((GPIOx->IDR) & PinNumber)  != (uint32_t)0)
	{
		bit_status = 1;
	}
	else
	{
		return bit_status=0;
	}
	return bit_status;
}
/**================================================================
 * @Fn-
 * @brief -
 * @param [in] -
 * @param [out] -
 * @retval -
 * Note-
 */
uint16_t MCAL_GPIO_ReadPort(GPIO_TYPEDEF* GPIOx)
{
	uint16_t port_value;
	port_value = (uint16_t)(GPIOx->IDR);
	return port_value;
}
/**================================================================
 * @Fn-
 * @brief -
 * @param [in] -
 * @param [out] -
 * @retval -
 * Note-
 */
void MCAL_GPIO_WritePort(GPIO_TYPEDEF* GPIOx, uint16_t value )
{
	GPIOx->ODR = value;

}
/**================================================================
 * @Fn-
 * @brief -
 * @param [in] -
 * @param [out] -
 * @retval -
 * Note-
 */
void MCAL_GPIO_WritePin(GPIO_TYPEDEF* GPIOx, uint16_t pin_number, uint8_t value)
{
	if(value ==1)
	{
		GPIOx->BSRR = pin_number;
	}
	else
	{
		GPIOx->BRR =pin_number;
	}
}
/**================================================================
 * @Fn-
 * @brief -
 * @param [in] -
 * @param [out] -
 * @retval -
 * Note-
 */

void MCAL_GPIO_TogglePin(GPIO_TYPEDEF* GPIOx, uint16_t PinNumber)
{
	GPIOx->ODR ^= PinNumber;
}
/**================================================================
 * @Fn-
 * @brief -
 * @param [in] -
 * @param [out] -
 * @retval -
 * Note-
 */
uint8_t MCAL_GPIO_LockPin(GPIO_TYPEDEF* GPIOx, uint16_t PinNumber)
{
	volatile uint32_t temp=1<<16;
	temp |=PinNumber;
	GPIOx->LCKR =temp;
	GPIOx->LCKR=PinNumber;
	GPIOx->LCKR =temp;
	temp= GPIOx->LCKR;
	if( GPIOx->LCKR & 1<<16)
	{
		return lock_enabled;
	}
	else
	{
		return lock_error;
	}

}
