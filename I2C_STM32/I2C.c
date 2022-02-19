/*
 * I2C.c
 *
 *  Created on: Feb 12, 2022
 *      Author: Mina
 */
#include "I2C.h"
#include "RCC.h"
void MCAL_I2C_INIT(I2C_TYPEDEF* I2Cx,I2C_config_t* conf)
{
	uint32_t tempreg=0;
	uint32_t fclk1=0;
	if(I2Cx==I2C1)
	{
		clk_enable_I2C1();
	}else if(I2Cx==I2C2)
	{
		clk_enable_I2C2();
	}
	if(conf->I2C_mode == I2C_mode_I2C)
	{

		fclk1= MCAL_RCC_Get_PCLK1_Freq();
		I2Cx->CR2 |=fclk1/1000000;
		I2Cx->CR1 &= ~(1<<0);

		if(conf->I2C_CLK_speed==I2C_SCLK_50k || conf->I2C_CLK_speed== I2C_SCLK_100k)
		{
			tempreg = fclk1/(2*conf->I2C_CLK_speed);
			I2Cx->CCR |= tempreg ;
			I2Cx->TRISE |= (fclk1/1000000)+1;
			I2Cx->CR1 |=(conf->I2C_mode | conf->stretch_mode |conf->general_call_address_detection |conf->ack_control);
			tempreg =0;
			if(conf->I2C__slave_address.Enable_Dual_address==1)
			{
				tempreg |= 1<<0;
				tempreg |= conf->I2C__slave_address.secondary_slave_address <<1;
				I2Cx->OAR2 |= tempreg;
			}
			tempreg=0;
			tempreg |= conf->I2C__slave_address.primary_slave_address <<1;
			tempreg |= conf->I2C__slave_address.addressing_slave_mode;
			I2Cx->OAR1 |= tempreg;
			if(conf->p_slave_event_callback != NULL)
			{
				I2Cx->CR2 |= 0b111<<8;
				if(I2Cx==I2C1)
				{
					NVIC_I2C1_EV_IRQ_ENABLE;
					NVIC_I2C1_ER_IRQ_ENABLE;
				}
				else if(I2Cx==I2C2)
				{
					NVIC_I2C2_EV_IRQ_ENABLE;
					NVIC_I2C2_ER_IRQ_ENABLE;
				}
				I2Cx->SR1=0;
				I2Cx->SR2=0;
			}

		}


		I2Cx->CR1 |= 1<<0;
	}
}
void MCAL_I2C_RESET(I2C_TYPEDEF* I2Cx)
{
	if(I2Cx==I2C1)
	{
		NVIC_I2C1_EV_IRQ_DISABLE;
		NVIC_I2C1_ER_IRQ_DISABLE;
		clk_disable_I2C1();
	}else if(I2Cx==I2C2)
	{
		NVIC_I2C2_EV_IRQ_DISABLE;
		NVIC_I2C2_ER_IRQ_DISABLE;
		clk_disable_I2C2();
	}

}
void MCAL_I2C_SET_GPIO_PINS(I2C_TYPEDEF* I2Cx)
{
	GPIO_PinConfig_t pin;
	if(I2Cx==I2C1)
	{
		pin.GPIO_MODE = GPIO_MODE_OUTPUT_AF_OD;
		pin.GPIO_Output_speed = GPIO_SPEED_10M;
		pin.GPIO_PinNumber = GPIO_PIN_6;
		MCAL_GPIO_Init(GPIOB, &pin);

		pin.GPIO_MODE = GPIO_MODE_OUTPUT_AF_OD;
		pin.GPIO_Output_speed = GPIO_SPEED_10M;
		pin.GPIO_PinNumber = GPIO_PIN_7;
		MCAL_GPIO_Init(GPIOB, &pin);
	}
	else if(I2Cx==I2C2)
	{

		pin.GPIO_MODE = GPIO_MODE_OUTPUT_AF_OD;
		pin.GPIO_Output_speed = GPIO_SPEED_10M;
		pin.GPIO_PinNumber = GPIO_PIN_10;
		MCAL_GPIO_Init(GPIOB, &pin);

		pin.GPIO_MODE = GPIO_MODE_OUTPUT_AF_OD;
		pin.GPIO_Output_speed = GPIO_SPEED_10M;
		pin.GPIO_PinNumber = GPIO_PIN_11;
		MCAL_GPIO_Init(GPIOB, &pin);
	}
}

void MCAL_I2C_MASTER_TX(I2C_TYPEDEF* I2Cx,uint16_t dev_addr, uint8_t *data, uint32_t length, stop_condition stop, Repeated_start start )
{
	int i;
	I2C_Generate_state(I2Cx,ENABLE,start);
	while(!(I2C_GetFlag_status(I2Cx,EV5)));
	I2C_SEND_ADDRESS(I2Cx,dev_addr,I2C_direction_TX);
	while(!(I2C_GetFlag_status(I2Cx,EV6)));
	while(!(I2C_GetFlag_status(I2Cx,EV8_1)));
	for(i=0;i<length;i++)
	{
		I2Cx->DR=data[i];
		while(!(I2C_GetFlag_status(I2Cx,EV8)));

	}
	if(stop==with_stop)
	{
		I2C_Generate_stop(I2Cx,ENABLE);
	}


}
void MCAL_I2C_MASTER_RX(I2C_TYPEDEF* I2Cx,I2C_config_t* conf,uint16_t dev_addr, uint8_t *data, uint32_t length, stop_condition stop, Repeated_start start )
{
	int i;
	I2C_Generate_state(I2Cx,ENABLE,start);
	while(!(I2C_GetFlag_status(I2Cx,EV5)));
	I2C_SEND_ADDRESS(I2Cx,dev_addr,I2C_direction_RX);
	while(!(I2C_GetFlag_status(I2Cx,EV6)));
	for(i=0;i<length;i++)
	{

		*data=I2Cx->DR;
		while(!(I2C_GetFlag_status(I2Cx,EV7)));
		data++;
	}
	conf->ack_control=ack_disable;
	if(stop==with_stop)
	{
		I2C_Generate_stop(I2Cx,ENABLE);
	}
	conf->ack_control=ack_enable;

}
void I2C_Generate_state(I2C_TYPEDEF* I2Cx,functional_state new_state, Repeated_start start)
{
	if(start != repeated_start)
	{
		while(I2C_GetFlag_status(I2Cx,I2C_flag_busy));

	}
	if(new_state != DISABLE)
	{
		I2Cx->CR1 |= 1<<8;
	}
	else
	{
		I2Cx->CR1 &= ~( 1<<8);
	}
}

flag_status I2C_GetFlag_status(I2C_TYPEDEF* I2Cx, status flag)
{
	volatile uint32_t dummy_read;
	flag_status bitStatus=RESET;
	switch(flag)
	{
	case I2C_flag_busy:
	{
		if((I2Cx->SR2)&(1<<1))
		{
			bitStatus=SET;
		}
		else
		{
			bitStatus=RESET;
		}
		break;
	}
	case EV5:
	{
		if((I2Cx->SR1)&(1<<0))
		{
			bitStatus=SET;
		}
		else
		{
			bitStatus=RESET;
		}
		break;
	}
	case EV6:
	{
		if((I2Cx->SR1)&(1<<1))
		{
			bitStatus=SET;
		}
		else
		{
			bitStatus=RESET;
		}
		dummy_read=I2Cx->SR2;

		break;

	}
	case EV8_1:
	{
		if(((I2Cx->SR1)&(1<<7))&&((I2Cx->SR2)&(0b111)))
		{
			bitStatus=SET;
		}
		else
		{
			bitStatus=RESET;
		}
		break;
	}
	case EV8:
	{
		if((I2Cx->SR1)&(1<<7))
		{
			bitStatus=SET;
		}
		else
		{
			bitStatus=RESET;
		}
		break;
	}
	case EV7:
	{
		if((I2Cx->SR1)&(1<<6))
		{
			bitStatus=SET;
		}
		else
		{
			bitStatus=RESET;
		}
		break;
	}


	}
	return bitStatus;
}
void I2C_SEND_ADDRESS(I2C_TYPEDEF* I2Cx, uint16_t address, I2C_direction Direction)
{
	address = address<<1;
	if(Direction != I2C_direction_TX)
	{
		address |= 1<<0;
	}
	else
	{
		address &= ~( 1<<0);
	}
	I2Cx->DR = address;
}

void I2C_Generate_stop(I2C_TYPEDEF* I2Cx,functional_state new_state)
{
	if(new_state != DISABLE)
	{
		I2Cx->CR1 |= 1<<9;
	}
	else
	{
		I2Cx->CR1 &= ~( 1<<9);
	}
}


void MCAL_I2C_slave_send_data(I2C_TYPEDEF* I2Cx,uint8_t data)
{
	I2Cx->DR = data;
}
uint8_t MCAL_I2C_slave_receive_data(I2C_TYPEDEF* I2Cx)
{
	return ((uint8_t)I2Cx->DR);
}
void I2C1_EV_IRQHandler()
{

}
void I2C1_ER_IRQHandler()
{

}
void I2C2_EV_IRQHandler()
{

}
void I2C2_ER_IRQHandler()
{

}

