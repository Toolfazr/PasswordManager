#pragma once

#include "stm32f10x.h"
#include <cstdint>
#include <cstddef>
#include <string.h>
#include <stdlib.h>


//给串口的缓冲区
class RingBuffer
{
public:
    RingBuffer(size_t ring_buffer_size);
	RingBuffer(const RingBuffer& another);
	~RingBuffer();
	void write(uint8_t byte);
	void read(uint8_t* ptr, size_t len);
	size_t has_bytes();
private:
    uint8_t* buffer;
    size_t write_index;
	size_t read_index;
	size_t ring_buffer_size;
	size_t bytes_num;
};

//与指纹模块通信的数据包
class Packet
{
public:
	Packet(const uint8_t* const load_ptr, size_t load_len);
	Packet(const Packet& another);
	~Packet();
	size_t to_array(uint8_t*& array);
	inline uint8_t get_ack_code(uint8_t* array)
	{
		return array[9];
	}
	inline uint8_t get_ack_code(Packet* pac)
	{
		return pac->load[0];
	}
	inline uint8_t get_ack_code()
	{
		return this->load[0];
	}
	void set_identifier(uint8_t byte);
private:
	size_t head_size;
	uint8_t identifier_size;
	size_t len_size;
	size_t load_size;
	size_t check_sum_size;
	uint16_t size;
	
	uint8_t head[6];
	uint8_t len[2];
	uint8_t identifier;
	uint8_t* load;
	uint8_t check_sum[2];	
};

//Qt传来的数据包
class QtPacketParser
{
public:
	QtPacketParser(uint8_t* buffer);
	inline uint8_t get_cmd()
	{
		return cmd_bit;
	}
	inline uint16_t get_target_addr()
	{
		return target_addr;
	}
	
	inline uint8_t* get_data_ptr()
	{
		return data_ptr;
	}
	inline uint8_t get_data_length()
	{
		return data_length;
	}
	
private:
	uint16_t target_addr;
	uint8_t cmd_bit;
	uint8_t* data_ptr;
	uint8_t data_length;
};
