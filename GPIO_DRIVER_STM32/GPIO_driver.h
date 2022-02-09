/*
 * GPIO_driver.h
 *
 *  Created on: Feb 3, 2022
 *      Author: Mina
 */

#ifndef INCLUDE_GPIO_DRIVER_H_
#define INCLUDE_GPIO_DRIVER_H_


//----------------------------- 29
//Includes
#include "stm32f103c6.h"

//-----------------------------

//-----------------------------
//User type definitions (structures)
typedef struct
{
	uint16_t GPIO_PinNumber;   // Specifies the configurations of GPIO pins
                              // This parameter must be a value of @ref GPIO_PINS_define
	uint8_t GPIO_MODE;        //Specifies the operating mode for the selected pin
							  // This parameter can be a value of @ref GPIO_MODE_define
	uint8_t GPIO_Output_speed;// Specifies the speed of the selected pins
							  // This parameter can be a value of @ref GPIO_SPEED_define
}GPIO_PinConfig_t;

//-----------------------------
//@ref GPIO_PIN_state
#define GPIO_PIN_SET		1
#define GPIO_PIN_RESET      0

#define lock_enabled        1
#define lock_error          0
//-----------------------------
//Macros Configuration References
//-----------------------------
//@ref GPIO_PINS_define
#define GPIO_PIN_0		0x0001u	//Pin 0 selected
#define GPIO_PIN_1		0x0002u	//Pin 1 selected
#define GPIO_PIN_2		0x0004u	//Pin 2 selected
#define GPIO_PIN_3		0x0008u	//Pin 3 selected
#define GPIO_PIN_4		0x0010u	//Pin 4 selected
#define GPIO_PIN_5		0x0020u	//Pin 5 selected
#define GPIO_PIN_6		0x0040u	//Pin 6 selected
#define GPIO_PIN_7		0x0080u	//Pin 7 selected
#define GPIO_PIN_8		0x0100u	//Pin 8 selected
#define GPIO_PIN_9		0x0200u	//Pin 9 selected
#define GPIO_PIN_10		0x0400u	//Pin 10 selected
#define GPIO_PIN_11 	0x0800u	//Pin 11 selected
#define GPIO_PIN_12 	0x1000u	//Pin 12 selected
#define GPIO_PIN_13		0x2000u	//Pin 13 selected
#define GPIO_PIN_14		0x4000u	//Pin 14 selected
#define GPIO_PIN_15		0x8000u	//Pin 15 selected
#define GPIO_PIN_ALL	0xFFFFu	//ALL Pins  selected

/*@ref GPIO_MODE_define
	0: Analog mode
	1: Floating input (reset state)
	2: Input with pull-up
	3: Input with pull-down
	4: General purpose output push-pull
	5: General purpose output open-drain
	6: Alternative function output push-pull
  	7: Alternative function output open-drain
  	8: Alternative function input
*/
#define GPIO_MODE_ANALOG            (uint8_t)0X0 //Analog mode
#define GPIO_MODE_INPUT_FLO         (uint8_t)0X1 //Floating input (reset state)
#define GPIO_MODE_INPUT_PU			(uint8_t)0X2 //Input with pull-up
#define GPIO_MODE_INPUT_PD			(uint8_t)0X3 //Input with pull-down
#define GPIO_MODE_OUTPUT_PP 		(uint8_t)0X4 //General purpose output push-pull
#define GPIO_MODE_OUTPUT_OD 		(uint8_t)0X5 //General purpose output open-drain
#define GPIO_MODE_OUTPUT_AF_PP		(uint8_t)0X6 //Alternative function output push-pull
#define GPIO_MODE_OUTPUT_AF_OD		(uint8_t)0X7 //Alternative function output open-drain
#define GPIO_MODE__AF_INPUT         (uint8_t)0X8 //Alternative function input

/*@ref GPIO_SPEED_define
	1: Output mode, max speed 10 MHz.
	2: Output mode, max speed 2 MHz.
	3: Output mode, max speed 50 MHz.*/


#define GPIO_SPEED_10M	(uint8_t)0X1	//Output mode, max speed 10 MHz.
#define GPIO_SPEED_2M	(uint8_t)0X2	//Output mode, max speed 2 MHz.
#define GPIO_SPEED_50M	(uint8_t)0X3	//Output mode, max speed 50 MHz.
/** ===============================================
* APIs Supported by "MCAL GPIO DRIVER"
* ===============================================
*/
void MCAL_GPIO_Init (GPIO_TYPEDEF* GPIOx, GPIO_PinConfig_t* PinConfig);
void MCAL_GPIO_reset (GPIO_TYPEDEF* GPIOx, RCC_TYPEDEF* rcc);
//Read APIs
uint8_t MCAL_GPIO_ReadPin(GPIO_TYPEDEF* GPIOx, uint16_t PinNumber);
uint16_t MCAL_GPIO_ReadPort(GPIO_TYPEDEF* GPIOx);
//Write APIs
void MCAL_GPIO_WritePort(GPIO_TYPEDEF* GPIOx, uint16_t value );
void MCAL_GPIO_WritePin(GPIO_TYPEDEF* GPIOx,uint16_t pin_number, uint8_t value);

void MCAL_GPIO_TogglePin(GPIO_TYPEDEF* GPIOx, uint16_t PinNumber);
uint8_t MCAL_GPIO_LockPin(GPIO_TYPEDEF* GPIOx, uint16_t PinNumber);
void clk_enable(GPIO_TYPEDEF* GPIOx, RCC_TYPEDEF* rcc);

#endif /* INCLUDE_GPIO_DRIVER_H_ */
