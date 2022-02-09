
void (*gP_IRQ_Call_Back[16])(void);

void Enable_NVIC(uint16_t IRQ)
{
	switch (IRQ)
	{
	case 0:
		NVIC_EXTI0_IRQ_ENABLE;
		break;
	case 1:
		NVIC_EXTI1_IRQ_ENABLE;
		break;
	case 2:
		NVIC_EXTI2_IRQ_ENABLE;
		break;
	case 3:
		NVIC_EXTI3_IRQ_ENABLE;
		break;
	case 4:
		NVIC_EXTI4_IRQ_ENABLE;
		break;
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		NVIC_EXTI5_9_IRQ_ENABLE;
		break;
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		NVIC_EXTI10_15_IRQ_ENABLE;
		break;
	}
}
void DISABLE_NVIC(uint16_t IRQ)
{
	switch (IRQ)
	{
	case 0:
		NVIC_EXTI0_IRQ_DISABLE;
		break;
	case 1:
		NVIC_EXTI1_IRQ_DISABLE;
		break;
	case 2:
		NVIC_EXTI2_IRQ_DISABLE;
		break;
	case 3:
		NVIC_EXTI3_IRQ_DISABLE;
		break;
	case 4:
		NVIC_EXTI4_IRQ_DISABLE;
		break;
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		NVIC_EXTI5_9_IRQ_DISABLE;
		break;
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		NVIC_EXTI10_15_IRQ_DISABLE;
		break;
	}
}
void Update_EXTI(EXTI_PinConfig_t* EXTI_CONFIG)
{
	GPIO_PinConfig_t pin;
	pin.GPIO_PinNumber = EXTI_CONFIG->EXTI_PIN.GPIO_PinNumber;
	pin.GPIO_MODE = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(EXTI_CONFIG->EXTI_PIN.GPIO_Port, &pin);

	uint8_t AFIO_EXTICR_index = EXTI_CONFIG->EXTI_PIN.EXTI_InputLineNumber/4;
	uint8_t AFIO_EXTICR_postion =4*( EXTI_CONFIG->EXTI_PIN.EXTI_InputLineNumber%4);
	AFIO->EXTICR[AFIO_EXTICR_index]= (AFIO_mapping(EXTI_CONFIG->EXTI_PIN.GPIO_Port)&0xF)<<AFIO_EXTICR_postion;

	EXTI->FTSR &= ~(1<<EXTI_CONFIG->EXTI_PIN.EXTI_InputLineNumber);
	EXTI->RTSR &= ~(1<<EXTI_CONFIG->EXTI_PIN.EXTI_InputLineNumber);
	if(EXTI_CONFIG->Trigger_case == EXT_Trigger_Rising)
	{
		EXTI->RTSR |= 1<<EXTI_CONFIG->EXTI_PIN.EXTI_InputLineNumber;
	}
	else if(EXTI_CONFIG->Trigger_case == EXT_Trigger_Falling)
	{
		EXTI->FTSR |= 1<<EXTI_CONFIG->EXTI_PIN.EXTI_InputLineNumber;
	}
	else if(EXTI_CONFIG->Trigger_case == EXT_Trigger_RisingAndFalling)
	{
		EXTI->RTSR |= 1<<EXTI_CONFIG->EXTI_PIN.EXTI_InputLineNumber;
		EXTI->FTSR |= 1<<EXTI_CONFIG->EXTI_PIN.EXTI_InputLineNumber;

	}

	gP_IRQ_Call_Back[EXTI_CONFIG->EXTI_PIN.EXTI_InputLineNumber]=EXTI_CONFIG->P_IRQ_Call_Back;
	if(EXTI_CONFIG->IRQ_EN == EXT_Enable)
	{
		EXTI->IMR |= 1<<EXTI_CONFIG->EXTI_PIN.EXTI_InputLineNumber;
		Enable_NVIC(EXTI_CONFIG->EXTI_PIN.EXTI_InputLineNumber);
	}
	else
	{
		EXTI->IMR &= ~ 1<<EXTI_CONFIG->EXTI_PIN.EXTI_InputLineNumber;
		DISABLE_NVIC(EXTI_CONFIG->EXTI_PIN.EXTI_InputLineNumber);

	}

}
void MCAL_EXTI_GPIO_RESET(void)
{
	EXTI->IMR  = 0;
	EXTI->EMR  = 0;
	EXTI->RTSR = 0;
	EXTI->FTSR = 0;
	EXTI->SWIER =0;
	EXTI->PR    =0XFFFFFFFF;
	//Disable IRQ from NVIC
	NVIC_EXTI0_IRQ_DISABLE;
	NVIC_EXTI1_IRQ_DISABLE;
	NVIC_EXTI2_IRQ_DISABLE;
	NVIC_EXTI3_IRQ_DISABLE;
	NVIC_EXTI4_IRQ_DISABLE;
	NVIC_EXTI5_9_IRQ_DISABLE;
	NVIC_EXTI10_15_IRQ_DISABLE;
}
void MCAL_EXTI_GPIO_INIT(EXTI_PinConfig_t* EXTI_CONFIG)
{
	Update_EXTI(EXTI_CONFIG);
}
void MCAL_EXTI_GPIO_UPDATE(EXTI_PinConfig_t* EXTI_CONFIG)
{
	Update_EXTI(EXTI_CONFIG);
}

void EXTI0_IRQHandler()
{
	EXTI->PR |= 1<<0;
	gP_IRQ_Call_Back[0]();
}
void EXTI1_IRQHandler()
{
	EXTI->PR |= 1<<1;
	gP_IRQ_Call_Back[1]();
}
void EXTI2_IRQHandler()
{
	EXTI->PR |= 1<<2;
	gP_IRQ_Call_Back[2]();
}
void EXTI3_IRQHandler()
{
	EXTI->PR |= 1<<3;
	gP_IRQ_Call_Back[3]();
}
void EXTI4_IRQHandler()
{
	EXTI->PR |= 1<<4;
	gP_IRQ_Call_Back[4]();
}
void EXTI9_5_IRQHandler ()
{
	if(EXTI->PR & (1<<5)) { EXTI->PR |= 1<<5; gP_IRQ_Call_Back[5](); }
	if(EXTI->PR & (1<<6)) { EXTI->PR |= 1<<6; gP_IRQ_Call_Back[6](); }
	if(EXTI->PR & (1<<7)) { EXTI->PR |= 1<<7; gP_IRQ_Call_Back[7](); }
	if(EXTI->PR & (1<<8)) { EXTI->PR |= 1<<8; gP_IRQ_Call_Back[8](); }
	if(EXTI->PR & (1<<9)) { EXTI->PR |= 1<<9; gP_IRQ_Call_Back[9](); }
}
void EXTI15_10_IRQHandler()
{
	if(EXTI->PR & (1<<10)) { EXTI->PR |= 1<<10; gP_IRQ_Call_Back[10](); }
	if(EXTI->PR & (1<<11)) { EXTI->PR |= 1<<11; gP_IRQ_Call_Back[11](); }
	if(EXTI->PR & (1<<12)) { EXTI->PR |= 1<<12; gP_IRQ_Call_Back[12](); }
	if(EXTI->PR & (1<<13)) { EXTI->PR |= 1<<13; gP_IRQ_Call_Back[13](); }
	if(EXTI->PR & (1<<14)) { EXTI->PR |= 1<<14; gP_IRQ_Call_Back[14](); }
	if(EXTI->PR & (1<<15)) { EXTI->PR |= 1<<15; gP_IRQ_Call_Back[15](); }
}
