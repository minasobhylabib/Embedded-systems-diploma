/*
 * USART.h
 *
 *  Created on: Feb 9, 2022
 *      Author: Mina
 */

#ifndef STM32_DRIVERS_INC_USART_H_
#define STM32_DRIVERS_INC_USART_H_
#include "stm32f103c6.h"
#include "RCC.h"
#include "GPIO_driver.h"

#define USARTDIV(PCLK,BAUD)				((uint32_t)(PCLK/(16*BAUD)))
#define USARTDIV_MUL100(PCLK,BAUD)		((uint32_t)(100*PCLK/(16*BAUD)))
#define MANTISSA_MUL100(PCLK,BAUD)		((uint32_t)(100*USARTDIV(PCLK,BAUD)))
#define MANTISSA(PCLK,BAUD)				((uint32_t)(USARTDIV(PCLK,BAUD)))
#define DIV_FRACTION(PCLK,BAUD)			((uint32_t)((USARTDIV_MUL100(PCLK,BAUD)-MANTISSA_MUL100(PCLK,BAUD))*16/100))
#define USART_BRR_REGISTER(PCLK,BAUD)   ((MANTISSA(PCLK,BAUD)<<4) |( DIV_FRACTION(PCLK,BAUD)&0XF))


typedef struct
{
	uint8_t 		USART_MODE;		//Specifies TX/RX enable
									//The parameters are defined @ref USART_MODE_define
	uint32_t		BAUD_RATE;		//Specifies the Baud rate
									//The parameters are defined @ref USART_BAUD_RATE_define
	uint8_t 		payload_length; //Specifies the number of bits for data
									//The parameters are defined @ref USART_BAUD_payload_length_define
	uint8_t		    parity;			//Specifies the parity option
									//The parameters are defined @ref USART_parity_define
	uint8_t		    stop_bits;		//Specifies the number of stop bits
									//The parameters are defined @ref USART_stopBits_define
	uint8_t 		flow_ctrl;		//Specifies the clear to send and request to send option
									//The parameters are defined @ref USART_flow_ctrl_define
	uint8_t			IRQ_enable;		//Specifies the interrupts
									//The parameters are defined @ref USART_IRQ_enable_define
	void(*P_IRQ_callBack)(void);	//Set the function to be called when interrupt occurs
}USART_CONFIG;



//-----------------------------
// @ref USART_MODE_define
#define USART_MODE_TX		((uint32_t)1<<2)
#define USART_MODE_RX		((uint32_t)1<<3)
#define USART_MODE_TX_RX	((uint32_t)(1<<2 | 1<<3))


//@ref USART_BAUD_RATE_define
#define USART_BaudRate_2400		2400
#define USART_BaudRate_9600		9600
#define USART_BaudRate_19200	19200
#define USART_BaudRate_57600	57600
#define USART_BaudRate_115200	115200
#define USART_BaudRate_230400	230400
#define USART_BaudRate_460800	460800
#define USART_BaudRate_921600	921600
#define USART_BaudRate_2250000	2250000
#define USART_BaudRate_4500000	4500000

// @ref USART_BAUD_payload_length_define
#define USART_BAUD_payload_length_8		((uint32_t)0)
#define USART_BAUD_payload_length_9		((uint32_t)1<<12)

//@ref USART_parity_define
#define USART_Parity_disabled			((uint32_t)0)
#define USART_Parity_even				((uint32_t)1<<10)
#define USART_Parity_odd				((uint32_t)(1<<9 | 1<<10))

//@ref USART_stopBits_define
#define USART_Stop_bits_half			((uint32_t)1<<12)
#define USART_Stop_bits_1				((uint32_t)0)
#define USART_Stop_bits_1_half			((uint32_t)3<<12)
#define USART_Stop_bits_2				((uint32_t)2<<12)

//@ref USART_flow_ctrl_define
#define USART_flow_ctrl_none				((uint32_t)0)
#define USART_flow_ctrl_CTS					((uint32_t)1<<9)
#define USART_flow_ctrl_RTS					((uint32_t)1<<8)
#define USART_flow_ctrl_CTS_RTS				((uint32_t)(1<<8|1<<9))

//@ref USART_IRQ_enable_define
#define USART_IRQ_enable_none			((uint32_t)0)
#define USART_IRQ_enable_TXE			((uint32_t)1<<7)
#define USART_IRQ_enable_TE				((uint32_t)1<<6)
#define USART_IRQ_enable_RXNEIE			((uint32_t)1<<5)
#define USART_IRQ_enable_PE				((uint32_t)1<<8)

enum polling
{
	enable,
	disable
};

/* ===============================================
 *
 * APIs Supported by "MCAL GPIO DRIVER"
 * ===============================================*/
void MCAL_USART_INIT(USART_TYPEDEF* USARTx, USART_CONFIG* CONF);
void MCAL_USART_DeINIT(USART_TYPEDEF* USARTx);
void MCAL_USART_GPIO_SET_PINS(USART_TYPEDEF* USARTx);
void MCAL_USART_SEND_DATA(USART_TYPEDEF* USARTx, uint16_t* BUFF, enum polling pollingEn,USART_CONFIG* CONF);
void MCAL_USART_RECEIVE_DATA(USART_TYPEDEF* USARTx, uint16_t* BUFF, enum polling pollingEn,USART_CONFIG* CONF);
void MCAL_USART_WAIT_TC(USART_TYPEDEF* USARTx);
#endif /* STM32_DRIVERS_INC_USART_H_ */
