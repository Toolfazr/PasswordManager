#include "communicator.h"

void Communicator::debug(uint8_t byte)
{
	uint8_t tmp = 0;

	tmp = (byte >> 4) & 0X0F;
	if(tmp >= 10)
	{
		tmp += 'A' - 10;
	}
	else
	{
		tmp += '0';
	}
	Bus::uart_2_send_bytes(&tmp, 1);
	
	tmp = byte & 0X0F;
	if(tmp >= 10)
	{
		tmp += 'A' - 10;
	}
	else
	{
		tmp += '0';
	}
	Bus::uart_2_send_bytes(&tmp, 1);
	
}

void Communicator::debug(const char* c_str)
{
	while(*c_str != '\0')
	{
		Bus::uart_2_send_bytes((uint8_t*)(c_str), 1);
		++c_str;
	}
}

void Communicator::print(const char* c_str)
{
	while(*c_str != '\0')
	{
		Bus::uart_2_send_bytes((uint8_t*)(c_str), 1);
		++c_str;
	}
}

void Communicator::print(uint8_t byte)
{
	uint8_t tmp = 0;

	tmp = (byte >> 4) & 0X0F;
	if(tmp >= 10)
	{
		tmp += 'A' - 10;
	}
	else
	{
		tmp += '0';
	}
	Bus::uart_2_send_bytes(&tmp, 1);
	
	tmp = byte & 0X0F;
	if(tmp >= 10)
	{
		tmp += 'A' - 10;
	}
	else
	{
		tmp += '0';
	}
	Bus::uart_2_send_bytes(&tmp, 1);
}

void Communicator::do_cmd()
{
	//该指针的堆空间由最终处理了数据的任务删除
	uint8_t* qt_packet_buffer = new uint8_t [MAX_BUFFER_SIZE];
	for(size_t i = 0; i < MAX_BUFFER_SIZE; ++i)
	{
		qt_packet_buffer[i] = '\0';
	}
	
	//判断是否超出缓冲区
	size_t len = Bus::has_bytes();
	if(Bus::uart_2_rec_bytes(qt_packet_buffer, len) && len == 0)
	{
		if(qt_packet_buffer[MAX_BUFFER_SIZE] != '\0')
		{
			//缓冲区溢出则不处理
			delete [] qt_packet_buffer;
		}
		else
		{
			//将来自Qt的数据包指针放至队列
			size_t ptr_value = (size_t)qt_packet_buffer;
			OS::send_queue_pac(&ptr_value);
			
			//唤醒数据包中指令对应任务，以处理数据包
			QtPacketParser parser(qt_packet_buffer);
			OS::run_cmd(parser.get_cmd());
		}	
	}
}
