/*
 * SPI.c
 *
 *  Created on: Feb 10, 2022
 *      Author: Mina
 */

#include "SPI.h"

#define SPI_SR_TXE		(0x2)
#define SPI_SR_RXNE		(0x1)



SPI_config_t* GLOBAL[2];
void MCAL_SPI_Init (SPI_TYPEDEF* SPIx, SPI_config_t* CONF)
{
	if(SPIx==SPI1)
	{
		clk_enable_SPI1();
		GLOBAL[0]=CONF;
	}
	else if(SPIx==SPI2)
	{
		clk_enable_SPI2();
		GLOBAL[1]=CONF;
	}
	uint16_t temp_CR1=0;
	uint16_t temp_CR2=0;
	temp_CR1 |= 1<<6;
	temp_CR1 |= CONF->Baud_Rate_Prescalar;
	temp_CR1 |= CONF->Clk_Polarity;
	temp_CR1 |=CONF->Clk_phase;
	temp_CR1 |=CONF->Communication_Mode;
	temp_CR1 |=CONF->Data_size;
	temp_CR1 |=CONF->Device_Mode;
	temp_CR1 |=CONF->Frame_format;
	//NSS
	if(CONF->NSS==SPI_NSS_hard_Master_SS_output_enable)
	{
		temp_CR2 |=CONF->NSS;
	}
	else
	{
		temp_CR1 |=CONF->NSS;
	}

	if(CONF->IRQ_Enable !=SPI_IRQ_Enable_none)
	{

		temp_CR2 |=CONF->IRQ_Enable;

		if(SPIx==SPI1)
		{
			NVIC_SPI1_IRQ_ENABLE;
		}
		else if(SPIx==SPI2)
		{
			NVIC_SPI2_IRQ_ENABLE;

		}
	}

	SPIx->CR1=temp_CR1;

	SPIx->CR2=temp_CR2;


}
void MCAL_SPI_reset (SPI_TYPEDEF* SPIx)
{
	if(SPIx==SPI1)
	{
		clk_disable_SPI1();
		NVIC_SPI1_IRQ_DISABLE;
	}
	else if(SPIx==SPI2)
	{
		clk_disable_SPI2();
		NVIC_SPI2_IRQ_DISABLE;
	}
}
void MCAL_SPI_GPIO_SET_PINS(SPI_TYPEDEF* SPIx)
{
	GPIO_PinConfig_t Pin;
	if(SPIx==SPI1)
	{
		//PA4:NSS 	PA5:SCK	PA6:MISO	PA7:MOSI
		if(GLOBAL[0]->Device_Mode ==SPI_Device_Mode_MASTER)
		{
			switch(GLOBAL[0]->NSS)
			{
			case SPI_NSS_hard_Master_SS_output_disable:
				Pin.GPIO_PinNumber=GPIO_PIN_4;
				Pin.GPIO_MODE=GPIO_MODE_INPUT_FLO;
				MCAL_GPIO_Init(GPIOA, &Pin);
				break;
			case SPI_NSS_hard_Master_SS_output_enable:
				Pin.GPIO_PinNumber=GPIO_PIN_4;
				Pin.GPIO_MODE=GPIO_MODE_OUTPUT_AF_PP;
				Pin.GPIO_Output_speed=GPIO_SPEED_10M;
				MCAL_GPIO_Init(GPIOA, &Pin);
				break;
			}
			Pin.GPIO_PinNumber=GPIO_PIN_5;
			Pin.GPIO_MODE=GPIO_MODE_OUTPUT_AF_PP;
			Pin.GPIO_Output_speed=GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &Pin);

			Pin.GPIO_PinNumber=GPIO_PIN_6;
			Pin.GPIO_MODE=GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA, &Pin);

			Pin.GPIO_PinNumber=GPIO_PIN_7;
			Pin.GPIO_MODE=GPIO_MODE_OUTPUT_AF_PP;
			Pin.GPIO_Output_speed=GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &Pin);
		}
		else
		{
			if(GLOBAL[0]->NSS==SPI_NSS_hard_slave)
			{
				Pin.GPIO_PinNumber=GPIO_PIN_4;
				Pin.GPIO_MODE=GPIO_MODE_INPUT_FLO;
				MCAL_GPIO_Init(GPIOA, &Pin);
			}
			Pin.GPIO_PinNumber=GPIO_PIN_5;
			Pin.GPIO_MODE=GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA, &Pin);
			Pin.GPIO_PinNumber=GPIO_PIN_6;
			Pin.GPIO_MODE=GPIO_MODE_OUTPUT_AF_PP;
			Pin.GPIO_Output_speed=GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &Pin);
			Pin.GPIO_PinNumber=GPIO_PIN_7;
			Pin.GPIO_MODE=GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA, &Pin);
		}
	}
	else if(SPIx==SPI2)
	{
		//PB12:NSS	PB13:SCLK	PB14:MISO	PB15:MOSI
		if(GLOBAL[1]->Device_Mode ==SPI_Device_Mode_MASTER)
				{
					switch(GLOBAL[1]->NSS)
					{
					case SPI_NSS_hard_Master_SS_output_disable:
						Pin.GPIO_PinNumber=GPIO_PIN_12;
						Pin.GPIO_MODE=GPIO_MODE_INPUT_FLO;
						MCAL_GPIO_Init(GPIOB, &Pin);
						break;
					case SPI_NSS_hard_Master_SS_output_enable:
						Pin.GPIO_PinNumber=GPIO_PIN_12;
						Pin.GPIO_MODE=GPIO_MODE_OUTPUT_AF_PP;
						Pin.GPIO_Output_speed=GPIO_SPEED_10M;
						MCAL_GPIO_Init(GPIOB, &Pin);
						break;
					}
					Pin.GPIO_PinNumber=GPIO_PIN_13;
					Pin.GPIO_MODE=GPIO_MODE_OUTPUT_AF_PP;
					Pin.GPIO_Output_speed=GPIO_SPEED_10M;
					MCAL_GPIO_Init(GPIOB, &Pin);

					Pin.GPIO_PinNumber=GPIO_PIN_14;
					Pin.GPIO_MODE=GPIO_MODE_INPUT_FLO;
					MCAL_GPIO_Init(GPIOB, &Pin);

					Pin.GPIO_PinNumber=GPIO_PIN_15;
					Pin.GPIO_MODE=GPIO_MODE_OUTPUT_AF_PP;
					Pin.GPIO_Output_speed=GPIO_SPEED_10M;
					MCAL_GPIO_Init(GPIOB, &Pin);
				}
				else
				{
					if(GLOBAL[1]->NSS==SPI_NSS_hard_slave)
					{
						Pin.GPIO_PinNumber=GPIO_PIN_12;
						Pin.GPIO_MODE=GPIO_MODE_INPUT_FLO;
						MCAL_GPIO_Init(GPIOB, &Pin);
					}
					Pin.GPIO_PinNumber=GPIO_PIN_13;
					Pin.GPIO_MODE=GPIO_MODE_INPUT_FLO;
					MCAL_GPIO_Init(GPIOB, &Pin);
					Pin.GPIO_PinNumber=GPIO_PIN_14;
					Pin.GPIO_MODE=GPIO_MODE_OUTPUT_AF_PP;
					Pin.GPIO_Output_speed=GPIO_SPEED_10M;
					MCAL_GPIO_Init(GPIOB, &Pin);
					Pin.GPIO_PinNumber=GPIO_PIN_15;
					Pin.GPIO_MODE=GPIO_MODE_INPUT_FLO;
					MCAL_GPIO_Init(GPIOB, &Pin);
				}

	}
}
void MCAL_SPI_SEND_DATA(SPI_TYPEDEF* SPIx, uint16_t* BUFF, enum SPI_polling pollingEn)
{
	if(pollingEn==enabled)
	{
		while(!(SPIx->SR &SPI_SR_TXE));
	}
	SPIx->DR =*BUFF;
}
void MCAL_SPI_RECEIVE_DATA(SPI_TYPEDEF* SPIx, uint16_t* BUFF, enum SPI_polling pollingEn)
{
	if(pollingEn==enabled)
	{
		while(!(SPIx->SR &SPI_SR_RXNE));
	}
	*BUFF = SPIx->DR;
}
void MCAL_SPI_TX_RX(SPI_TYPEDEF* SPIx, uint16_t* BUFF, enum SPI_polling pollingEn)
{
	MCAL_SPI_SEND_DATA(SPIx,  BUFF, pollingEn);
	MCAL_SPI_RECEIVE_DATA(SPIx, BUFF, pollingEn);

}

void SPI1_IRQHandler()
{
	struct S_IRQ_src S;
	S.TXE =(SPI1->SR &(1<<1)>>1);
	S.RXNE =(SPI1->SR &(1<<0)>>0);
	S.ERRI =(SPI1->SR &(1<<4)>>4);
	GLOBAL[0]->P_IRQ_call(S);

}
void SPI2_IRQHandler()
{
	struct S_IRQ_src S;
	S.TXE =(SPI2->SR &(1<<1)>>1);
	S.RXNE =(SPI2->SR &(1<<0)>>0);
	S.ERRI =(SPI2->SR &(1<<4)>>4);
	GLOBAL[1]->P_IRQ_call(S);
}
