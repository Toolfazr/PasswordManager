#include "interrupt_support.h"

bool InterruptController::prioGroupIsSet = false;

void InterruptController::config(enum peri_name name, uint8_t preemtion_prio, uint8_t sub_prio)
{
	if(prioGroupIsSet == false) 
	{
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
		prioGroupIsSet = true;
	}
	
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	
	switch(name)
	{
		case uart_1:
			NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
		break;
		
		case uart_2:
			NVIC_InitStruct.NVIC_IRQChannel = USART2_IRQn;
		break;
		
		case spi_1:
			NVIC_InitStruct.NVIC_IRQChannel = SPI1_IRQn;
		break;
		
		case exti:
			NVIC_InitStruct.NVIC_IRQChannel = EXTI9_5_IRQn;
		break;
	}
	
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = sub_prio;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = preemtion_prio;
	NVIC_Init(&NVIC_InitStruct);
}
