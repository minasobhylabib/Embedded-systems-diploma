/*
 * SPI.h
 *
 *  Created on: Feb 10, 2022
 *      Author: Mina
 */

#ifndef STM32_DRIVERS_INC_SPI_H_
#define STM32_DRIVERS_INC_SPI_H_
#include "stm32f103c6.h"
#include "GPIO_driver.h"

struct S_IRQ_src{
	uint8_t	TXE:1;
	uint8_t	RXNE:1;
	uint8_t	ERRI:1;
	uint8_t Reserved:5;
};
typedef struct {
	uint16_t	Device_Mode;					//specifies master or slave type @ref Device_Mode_define
	uint16_t	Communication_Mode;				//specifies full duplex or half duplex @ref Communication_Mode_define
	uint16_t	Frame_format;					//@ref Frame_format_define
	uint16_t	Data_size;						//@ref Data_size_define
	uint16_t	Clk_Polarity;					//@ref Clk_Polarity_define
	uint16_t	Clk_phase;						//@ref Clk_phase_define
	uint16_t	NSS;							//@ref NSS_define
	uint16_t	Baud_Rate_Prescalar;			//@ref Baud_Rate_Prescalar_define
	uint16_t	IRQ_Enable;						//@ref IRQ_Enable_define
	void (*P_IRQ_call)(struct S_IRQ_src IRQ);

}SPI_config_t;

//@ref Device_Mode_define
#define SPI_Device_Mode_MASTER		(1<<2)//CR1.MSTR
#define SPI_Device_Mode_SLAVE		(0)

//@ref Communication_Mode_define
#define SPI_DIRECTION_2_LINES				(0)	//CR1.bit
#define SPI_DIRECTION_2_LINES_RX_only		(1<<10)
#define SPI_DIRECTION_1_LINE_RX_only		(1<<15)
#define SPI_DIRECTION_1_LINE_TX_only		(1<<14 | 1<<15)

//@ref Frame_format_define
#define SPI_Frame_format_MSB_transmitted_first		(0)
#define SPI_Frame_format_LSB_transmitted_first		(1<<7)

//@ref Data_size_define
#define SPI_data_size_8bit				(0)//CR1.DFF
#define SPI_data_size_16bit				(1<<11)

//@ref Clk_Polarity_define
#define SPI_ClkPolarity_low_when_idle	(0)
#define SPI_ClkPolarity_high_when_idle	(1<<1)

//@ref Clk_phase_define
#define SPI_Data_capture_at_FirstClkEdge	(0)
#define SPI_Data_capture_at_SecondClkEdge	(1<<0)

//@ref NSS_define
	//hardware
#define SPI_NSS_hard_slave						(0)
#define SPI_NSS_hard_Master_SS_output_enable	(1<<2)
#define SPI_NSS_hard_Master_SS_output_disable	(0)
	//software
#define SPI_NSS_Internal_soft_reset				(1<<9)
#define SPI_NSS_Internal_soft_set				(1<<8|1<<9)

//@ref Baud_Rate_Prescalar_define
#define SPI_Baud_Rate_Prescalar_2		(0)
#define SPI_Baud_Rate_Prescalar_4		(0b001<<3)
#define SPI_Baud_Rate_Prescalar_8		(0b010<<3)
#define SPI_Baud_Rate_Prescalar_16		(0b011<<3)
#define SPI_Baud_Rate_Prescalar_32		(0b100<<3)
#define SPI_Baud_Rate_Prescalar_64		(0b101<<3)
#define SPI_Baud_Rate_Prescalar_128		(0b110<<3)
#define SPI_Baud_Rate_Prescalar_256		(0b111<<3)

//@ref IRQ_Enable_define
#define SPI_IRQ_Enable_none			(0)
#define SPI_IRQ_Enable_TXEIE		(1<<7)
#define SPI_IRQ_Enable_RXNIE		(1<<6)
#define SPI_IRQ_Enable_ERRIE		(1<<5)

enum SPI_polling
{
	enabled,
	disabled
};
/** ===============================================
* APIs Supported by "MCAL SPI DRIVER"
* ===============================================
*/
void MCAL_SPI_Init (SPI_TYPEDEF* SPIx, SPI_config_t* CONF);
void MCAL_SPI_reset (SPI_TYPEDEF* SPIx);
void MCAL_SPI_GPIO_SET_PINS(SPI_TYPEDEF* SPIx);
void MCAL_SPI_SEND_DATA(SPI_TYPEDEF* SPIx, uint16_t* BUFF, enum SPI_polling pollingEn);
void MCAL_SPI_RECEIVE_DATA(SPI_TYPEDEF* SPIx, uint16_t* BUFF, enum SPI_polling pollingEn);
void MCAL_SPI_TX_RX(SPI_TYPEDEF* SPIx, uint16_t* BUFF, enum SPI_polling pollingEn);



#endif /* STM32_DRIVERS_INC_SPI_H_ */
