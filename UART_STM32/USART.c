/*
 * USART.c
 *
 *  Created on: Feb 9, 2022
 *      Author: Mina
 */


#include "USART.h"
void (*p[3])(void);
void MCAL_USART_INIT(USART_TYPEDEF* USARTx, USART_CONFIG* CONF)
{
	uint32_t pclk;
	//Global =CONF;
	if(USARTx==USART1)
	{
		clk_enable_USART1();
		p[0]=CONF->P_IRQ_callBack;
	}
	else if(USARTx==USART2)
	{
		clk_enable_USART2();
		p[1]=CONF->P_IRQ_callBack;
	}
	else if(USARTx==USART3)
	{
		clk_enable_USART3();
		p[2]=CONF->P_IRQ_callBack;
	}

	USARTx->CR1 |= 1<<13;
	USARTx->CR1 |=CONF->USART_MODE;
	USARTx->CR1 |=CONF->parity;
	USARTx->CR1 |=CONF->payload_length;
	USARTx->CR2 |=CONF->stop_bits;
	USARTx->CR3 |=CONF->flow_ctrl;
	if (USARTx==USART1)
	{
		pclk=MCAL_RCC_Get_PCLK2_Freq();
	}
	else
	{
		pclk=MCAL_RCC_Get_PCLK1_Freq();
	}

	//BRR = USART_BRR_REGISTER(pclk,CONF->BAUD_RATE);
	USARTx->BRR=USART_BRR_REGISTER(pclk,CONF->BAUD_RATE);
	if (CONF->IRQ_enable != USART_IRQ_enable_none	)
	{
		USARTx->CR1 |=CONF->IRQ_enable;
		if (USARTx == USART1)
			NVIC_USART1_IRQ_ENABLE;
		else if(USARTx ==USART2)
			NVIC_USART2_IRQ_ENABLE;
		else if(USARTx==USART3)
			NVIC_USART3_IRQ_ENABLE;

	}

}
void MCAL_USART_DeINIT(USART_TYPEDEF* USARTx)
{
	if (USARTx == USART1)
	{
		clk_disable_USART1();
		NVIC_USART1_IRQ_DISABLE;
	}
	else if(USARTx ==USART2)
	{
		clk_disable_USART2();
		NVIC_USART2_IRQ_DISABLE;
	}
	else if(USARTx==USART3)
	{
		clk_disable_USART3();
		NVIC_USART3_IRQ_DISABLE;
	}
}
void MCAL_USART_GPIO_SET_PINS(USART_TYPEDEF* USARTx)
{
	GPIO_PinConfig_t PIN;
	if (USARTx==USART1)
	{
		//PA9 Tx
		PIN.GPIO_MODE=GPIO_MODE_OUTPUT_AF_PP;
		PIN.GPIO_Output_speed = GPIO_SPEED_10M;
		PIN.GPIO_PinNumber = GPIO_PIN_9;
		//PA10 RX
		MCAL_GPIO_Init(GPIOA,&PIN);
		PIN.GPIO_PinNumber = GPIO_PIN_10;
		PIN.GPIO_MODE=GPIO_MODE__AF_INPUT;
		MCAL_GPIO_Init(GPIOA,&PIN);
		//PA11 CTS
		if(USART_flow_ctrl_CTS	||USART_flow_ctrl_CTS_RTS)
		{
			PIN.GPIO_PinNumber = GPIO_PIN_11;
			PIN.GPIO_MODE=GPIO_MODE__AF_INPUT;
			MCAL_GPIO_Init(GPIOA,&PIN);
		}
		//PA12 RTS
		if(USART_flow_ctrl_RTS	||USART_flow_ctrl_CTS_RTS)
		{
			PIN.GPIO_MODE=GPIO_MODE_OUTPUT_AF_PP;
			PIN.GPIO_Output_speed = GPIO_SPEED_10M;
			PIN.GPIO_PinNumber = GPIO_PIN_12;
		}

	}
	else if(USARTx==USART2)
	{
		//PA2 Tx
				PIN.GPIO_MODE=GPIO_MODE_OUTPUT_AF_PP;
				PIN.GPIO_Output_speed = GPIO_SPEED_10M;
				PIN.GPIO_PinNumber = GPIO_PIN_2;
				//PA3 RX
				MCAL_GPIO_Init(GPIOA,&PIN);
				PIN.GPIO_PinNumber = GPIO_PIN_3;
				PIN.GPIO_MODE=GPIO_MODE__AF_INPUT;
				MCAL_GPIO_Init(GPIOA,&PIN);
				//PA0 CTS
				if(USART_flow_ctrl_CTS	||USART_flow_ctrl_CTS_RTS)
				{
					PIN.GPIO_PinNumber = GPIO_PIN_0;
					PIN.GPIO_MODE=GPIO_MODE__AF_INPUT;
					MCAL_GPIO_Init(GPIOA,&PIN);
				}
				//PA1 RTS
				if(USART_flow_ctrl_RTS	||USART_flow_ctrl_CTS_RTS)
				{
					PIN.GPIO_MODE=GPIO_MODE_OUTPUT_AF_PP;
					PIN.GPIO_Output_speed = GPIO_SPEED_10M;
					PIN.GPIO_PinNumber = GPIO_PIN_1;
					MCAL_GPIO_Init(GPIOA,&PIN);
				}

	}
	else if(USARTx==USART3)
	{
		//PB10 Tx
				PIN.GPIO_MODE=GPIO_MODE_OUTPUT_AF_PP;
				PIN.GPIO_Output_speed = GPIO_SPEED_10M;
				PIN.GPIO_PinNumber = GPIO_PIN_10;
				//PB11 RX
				MCAL_GPIO_Init(GPIOB,&PIN);
				PIN.GPIO_PinNumber = GPIO_PIN_11;
				PIN.GPIO_MODE=GPIO_MODE__AF_INPUT;
				MCAL_GPIO_Init(GPIOB,&PIN);
				//PB13 CTS
				if(USART_flow_ctrl_CTS	||USART_flow_ctrl_CTS_RTS)
				{
					PIN.GPIO_PinNumber = GPIO_PIN_13;
					PIN.GPIO_MODE=GPIO_MODE__AF_INPUT;
					MCAL_GPIO_Init(GPIOB,&PIN);
				}
				//PB14 RTS
				if(USART_flow_ctrl_RTS	||USART_flow_ctrl_CTS_RTS)
				{
					PIN.GPIO_MODE=GPIO_MODE_OUTPUT_AF_PP;
					PIN.GPIO_Output_speed = GPIO_SPEED_10M;
					PIN.GPIO_PinNumber = GPIO_PIN_14;
					MCAL_GPIO_Init(GPIOB,&PIN);
				}

	}
}
void MCAL_USART_SEND_DATA(USART_TYPEDEF* USARTx, uint16_t* BUFF, enum polling pollingEn,USART_CONFIG* CONF)
{
	if (pollingEn==enable)
	{
		while(!(USARTx->SR & 1<<7));
	}
	if(CONF->payload_length==USART_BAUD_payload_length_8)
	{
		USARTx->DR = *BUFF&0xff;
	}
	else if(CONF->payload_length==USART_BAUD_payload_length_9)
	{
		USARTx->DR = *BUFF&0x01ff;
	}
}

void MCAL_USART_RECEIVE_DATA(USART_TYPEDEF* USARTx, uint16_t* BUFF, enum polling pollingEn,USART_CONFIG* CONF)
{
	if (pollingEn==enable)
	{
		while(!(USARTx->SR & 1<<5));
	}
	if(CONF->payload_length==USART_BAUD_payload_length_8)
	{
		if(CONF->parity ==USART_Parity_disabled)
			*BUFF=(uint16_t)(USARTx->DR&0XFF);
		else
			*BUFF=(uint16_t)(USARTx->DR&0x7f);
	}
	else if(CONF->payload_length==USART_BAUD_payload_length_9)
	{
		if(CONF->parity ==USART_Parity_disabled)
		{
			*BUFF=(uint16_t)(USARTx->DR&0X01FF);
		}
		else
			*BUFF=(uint16_t)(USARTx->DR&0xff);
	}
}
void MCAL_USART_WAIT_TC(USART_TYPEDEF* USARTx)
{
	while(!(USARTx->SR & 1<<6));
}
void USART1_IRQHandler()
{
	p[0]();

}
void USART2_IRQHandler()
{
	p[1]();

}
void USART3_IRQHandler()
{
	p[2]();

}

