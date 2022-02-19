/*
 * I2C.h
 *
 *  Created on: Feb 12, 2022
 *      Author: Mina
 */

#ifndef STM32_DRIVERS_INC_I2C_H_
#define STM32_DRIVERS_INC_I2C_H_
#include "stm32f103c6.h"
#include "GPIO_driver.h"

typedef enum
{
	EV_STOP,
	ERROR_AF,
	EV_ADDRESS_MATCH,
	EV_DATA_REQ,
	EV_DATA_RECIEVE
}slave_state;

typedef enum{
	with_stop,
	without_stop
}stop_condition;

typedef enum{
	start,
	repeated_start
}Repeated_start;

typedef enum{
	DISABLE = 0,
	ENABLE =1
}functional_state;

typedef enum{
	I2C_direction_TX=0,
	I2C_direction_RX=1
}I2C_direction;


typedef enum{
	I2C_flag_busy =0,
	EV5,
	EV6,
	EV8_1,
	EV8,
	EV7

}status;

typedef enum{
	RESET =0,
	SET =1
}flag_status;

struct S_I2C_slave_address
{
	uint32_t Enable_Dual_address; //1:enable 0:disable
	uint32_t primary_slave_address;
	uint32_t secondary_slave_address;
	uint32_t addressing_slave_mode; //@ref addressing_slave_mode_define
	};
typedef struct
{
	uint32_t 					I2C_CLK_speed;	//@ref I2C_CLK_speed_define
	uint32_t 					stretch_mode;	//@ref stretch_mode+define
	uint32_t 					I2C_mode;		//@ref I2C_mode_define
	struct S_I2C_slave_address  I2C__slave_address;
	uint32_t 					general_call_address_detection;//@ref general_call_address_detection;_define
	void (*p_slave_event_callback)(slave_state state);
	uint32_t ack_control;           //@ref ack_control_define

}I2C_config_t;

//@ref I2C_CLK_speed_define
#define I2C_SCLK_50k	(50000)
#define I2C_SCLK_100k	(100000)

//@ref stretch_mode_define
#define clk_stretch_mode_enabled	(0)
#define clk_stretch_mode_disabled	(1<<7)

//@ref I2C_mode_define
#define I2C_mode_I2C 		(0)
#define I2C_mode_SM_bus		(1<<1)

//@ref addressing_slave_mode_define
#define addressing_slave_mode_7bits	    (0)
#define addressing_slave_mode_10bits	(1<<15)

//@ref ack_control_define
#define ack_enable		(1<<10)
#define ack_disable		(0)

//@ref general_call_address_detection_define
#define general_call_address_enable  (1<<6)
#define general_call_address_disable (0)

 void MCAL_I2C_INIT(I2C_TYPEDEF* I2Cx,I2C_config_t* conf);
 void MCAL_I2C_RESET(I2C_TYPEDEF* I2Cx);
 void MCAL_I2C_SET_GPIO_PINS(I2C_TYPEDEF* I2Cx);
 void MCAL_I2C_MASTER_TX(I2C_TYPEDEF* I2Cx,uint16_t dev_addr, uint8_t *data, uint32_t length, stop_condition stop, Repeated_start start );
 void MCAL_I2C_MASTER_RX(I2C_TYPEDEF* I2Cx,I2C_config_t* conf,uint16_t dev_addr, uint8_t *data, uint32_t length, stop_condition stop, Repeated_start start );
 void I2C_Generate_state(I2C_TYPEDEF* I2Cx,functional_state new_state, Repeated_start start);
 flag_status I2C_GetFlag_status(I2C_TYPEDEF* I2Cx, status flag);
 void I2C_SEND_ADDRESS(I2C_TYPEDEF* I2Cx, uint16_t address, I2C_direction Direction);
 void I2C_Generate_stop(I2C_TYPEDEF* I2Cx,functional_state ENABLE);

 void MCAL_I2C_slave_send_data(I2C_TYPEDEF* I2Cx,uint8_t data);
 uint8_t MCAL_I2C_slave_receive_data(I2C_TYPEDEF* I2Cx);

 #endif /* STM32_DRIVERS_INC_I2C_H_ */
