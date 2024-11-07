#include "bus.h"
#include "communicator.h"

RingBuffer* Bus::buffer = NULL;

void Bus::init()
{
	//enable clock of uart, gpio, afio
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	//init uart_1 & uart_2
	USART_InitTypeDef uart_init_struct;
	uart_init_struct.USART_WordLength = USART_WordLength_8b;
	uart_init_struct.USART_StopBits = USART_StopBits_2;
	uart_init_struct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	uart_init_struct.USART_Parity = USART_Parity_No;
	uart_init_struct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	uart_init_struct.USART_BaudRate = 9600*6;
	
	USART_Init(USART1, &uart_init_struct);
	
	uart_init_struct.USART_WordLength = USART_WordLength_8b;
	uart_init_struct.USART_StopBits = USART_StopBits_2;
	uart_init_struct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	uart_init_struct.USART_Parity = USART_Parity_No;
	uart_init_struct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	uart_init_struct.USART_BaudRate = 9600*6;
	USART_Init(USART2, &uart_init_struct);
	
	InterruptController::config(uart_1, 5, 0);
	InterruptController::config(uart_2, 5, 0);
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	USART_ITConfig(USART1, USART_IT_IDLE, ENABLE); 
	USART_ClearFlag(USART1, USART_IT_RXNE);
	USART_ClearFlag(USART1, USART_IT_IDLE); 
	
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	USART_ITConfig(USART2, USART_IT_IDLE, ENABLE); 
	USART_ClearFlag(USART2, USART_IT_RXNE);
	USART_ClearFlag(USART2, USART_IT_IDLE); 
	
	USART_Cmd(USART1, ENABLE);
	USART_Cmd(USART2, ENABLE);
	
	//config I/O port needed by uart_1
	GPIO_InitTypeDef gpio_a_init_struct;
	gpio_a_init_struct.GPIO_Pin = GPIO_Pin_9;//uart_1_tx line
	gpio_a_init_struct.GPIO_Mode = GPIO_Mode_AF_PP;
	gpio_a_init_struct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpio_a_init_struct);
	
	gpio_a_init_struct.GPIO_Pin = GPIO_Pin_10;//uart_1_rx line
	gpio_a_init_struct.GPIO_Speed = GPIO_Speed_50MHz;
	gpio_a_init_struct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &gpio_a_init_struct);
	
	//config I/O port needed by uart_2
	gpio_a_init_struct.GPIO_Pin = GPIO_Pin_2;
	gpio_a_init_struct.GPIO_Mode = GPIO_Mode_AF_PP;//uart_2_tx line
	gpio_a_init_struct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpio_a_init_struct);
	
	gpio_a_init_struct.GPIO_Pin = GPIO_Pin_3;//uart_2_rx line
	gpio_a_init_struct.GPIO_Speed = GPIO_Speed_50MHz;
	gpio_a_init_struct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &gpio_a_init_struct);
	
	buffer = new RingBuffer(256);
}

void Bus::uart_1_send_bytes(uint8_t* buffer, size_t len)
{
	for(size_t i = 0; i < len; ++i)
	{
		while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
		USART_SendData(USART1, (uint8_t)*(buffer + i));
	}
}

void Bus::uart_2_send_bytes(uint8_t* buffer, size_t len)
{
	for(size_t i = 0; i < len; ++i)
	{
		while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
		USART_SendData(USART2, (uint8_t)*(buffer + i));
	}
}

void Bus::uart_2_send_byte(uint8_t byte)
{
	Bus::uart_2_send_bytes(&byte, 1);
}

void Bus::store_byte(uint8_t byte)
{
	Bus::buffer->write(byte);
}

size_t Bus::has_bytes()
{
	return Bus::buffer->has_bytes();
}

bool Bus::uart_1_rec_bytes(uint8_t* buffer, size_t len)
{
	OS::wait_uart_1_tc();
	if(len == 0)
	{
		Bus::buffer->read(buffer, len);
	}
	else
	{
		if(Bus::has_bytes() != len)
			return false;
		else
			Bus::buffer->read(buffer, len);
	}
	
	
	return true;
}

bool Bus::uart_2_rec_bytes(uint8_t* buffer, size_t len)
{
	OS::wait_uart_2_tc();
	if(len == 0)
	{
		Bus::buffer->read(buffer, len);
	}
	else
	{
		if(Bus::has_bytes() != len)
			return false;
		else
			Bus::buffer->read(buffer, len);
	}
	
	
	return true;
}


void Bus::iic_start()
{
	iic_write_sda(1);
	iic_write_scl(1);
	iic_write_sda(0);
	iic_write_scl(0);
}

void Bus::iic_stop()
{
	iic_write_sda(0);
	iic_write_scl(1);
	iic_write_sda(1);
}

void Bus::iic_send_byte(uint8_t byte)
{
	for(size_t i = 0; i < 8; ++i)
	{
		iic_write_sda(byte & (0X80 >> i));
		iic_write_scl(1);
		iic_write_scl(0);
	}
}

uint8_t Bus::iic_rec_byte()
{
	uint8_t byte = 0X00;
	iic_write_sda(1);
	for(size_t i = 0; i < 8; ++i)
	{
		iic_write_scl(1);
		if(iic_read_sda() == 1)
		{
			byte |= (0X80 >> i);
		}
		iic_write_scl(0);
	}

	return byte;
}

void Bus::iic_send_ack(uint8_t ack_bit)
{
	iic_write_sda(ack_bit);
	iic_write_scl(1);
	iic_write_scl(0);
}

uint8_t Bus::iic_rec_ack()
{
	uint8_t ack_bit = 0X00;
	iic_write_sda(1);
	iic_write_scl(1);
	ack_bit = iic_read_sda();
	iic_write_scl(0);

	return ack_bit;
}

extern "C" void USART1_IRQHandler()
{
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	
	if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
	{
		uint8_t data = USART_ReceiveData(USART1);
//		Bus::uart_2_send_byte(data);
		Bus::store_byte(data);
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	}
	
	else if(USART_GetITStatus(USART1, USART_IT_IDLE) == SET)
	{
		if(OS::uart_1_tc() == true)
			xHigherPriorityTaskWoken = pdTRUE;
//		Communicator::print("packet rec\r\n");
//		Bus::uart_2_send_byte(0XED);
		USART_ReceiveData(USART1);
		USART_ClearITPendingBit(USART1, USART_IT_IDLE);
	}
	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

extern "C" void USART2_IRQHandler()
{
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	
	if(USART_GetITStatus(USART2, USART_IT_RXNE) == SET)
	{
		Bus::store_byte(USART_ReceiveData(USART2));
		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
	}
	
	else if(USART_GetITStatus(USART2, USART_IT_IDLE) == SET)
	{
		if(OS::uart_2_tc() == true)
			xHigherPriorityTaskWoken = pdTRUE;

		USART_ReceiveData(USART2);
		USART_ClearITPendingBit(USART2, USART_IT_IDLE);
	}
	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}
