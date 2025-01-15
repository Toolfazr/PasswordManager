#include "data_type.h"

RingBuffer::RingBuffer(size_t ring_buffer_size)
{
	this->ring_buffer_size = ring_buffer_size;
	write_index = 0;
	read_index = 0;
	buffer = new uint8_t[ring_buffer_size];
	bytes_num = 0;
}

RingBuffer::RingBuffer(const RingBuffer& another)
{
	this->ring_buffer_size = another.ring_buffer_size;
	write_index = 0;
	read_index = 0;
	buffer = new uint8_t[this->ring_buffer_size];
	bytes_num = 0;
}

RingBuffer::~RingBuffer()
{
	delete [] buffer;
}

void RingBuffer::write(uint8_t byte)
{
	buffer[write_index] = byte;
	write_index = (write_index + 1)%ring_buffer_size;
	++bytes_num;
}

void RingBuffer::read(uint8_t* ptr, size_t len)
{
	if(len == 0)
	{
		len = bytes_num;
	}
	
	for(size_t i = 0; i < len; ++i)
	{
		ptr[i] = buffer[(read_index + i)%ring_buffer_size];
	}
	
	read_index = (read_index + len)%ring_buffer_size;
	bytes_num -= len;
}

size_t RingBuffer::has_bytes()
{
	return bytes_num;
}

Packet::Packet(const uint8_t* const load_ptr, size_t load_len):
head_size(6),
identifier_size(1),
len_size(2),
load_size(load_len),
check_sum_size(2),
size(head_size + identifier_size + len_size + load_size + check_sum_size),
load(new uint8_t[load_size])
{
	head[0] = 0XEF;
	head[1] = 0X01;
	head[2] = 0XFF;
	head[3] = 0XFF;
	head[4] = 0XFF;
	head[5] = 0XFF;

	identifier = 0X00;

	len[0] = static_cast<uint8_t>(((load_len + check_sum_size) >> 8) & 0XFF);
	len[1] = static_cast<uint8_t>((load_len + check_sum_size) & 0XFF);
	
	uint16_t sum = 0;
	for(size_t i = 0; i < load_size; ++i)
	{
		load[i] = load_ptr[i];
		sum += load[i];
	}

	sum += identifier + len[0] + len[1];

	check_sum[0] = static_cast<uint8_t>((sum >> 8) & 0XFF);
	check_sum[1] = static_cast<uint8_t>(sum & 0XFF);
}

Packet::Packet(const Packet& another):
head_size(another.head_size),
identifier_size(another.identifier_size),
len_size(another.len_size),
load_size(another.load_size),
check_sum_size(another.check_sum_size),
size(another.size),
load(new uint8_t[another.load_size])
{
	for(size_t i = 0; i < head_size; ++i)
	{
		this->head[i] = another.head[i];
	}

	len[0] = another.len[0];
	len[1] = another.len[1];

	identifier = another.identifier;

	for(size_t i = 0; i < load_size; ++i)
	{
		load[i] = another.load[i];		
	}

	check_sum[0] = another.check_sum[0];
	check_sum[1] = another.check_sum[1];
}

Packet::~Packet()
{
	delete [] load;
}

size_t Packet::to_array(uint8_t*& array)
{
	array = new uint8_t[size];
    size_t index = 0;

    for (size_t i = 0; i < head_size; ++i)
    {
        array[index++] = head[i];
    }

    array[index++] = identifier;

    for (size_t i = 0; i < len_size; ++i)
    {
        array[index++] = len[i];
    }

    for (size_t i = 0; i < load_size; ++i)
    {
        array[index++] = load[i];
    }

    for (size_t i = 0; i < check_sum_size; ++i)
    {
        array[index++] = check_sum[i];
    }

    return size;
}

void Packet::set_identifier(uint8_t byte)
{
	uint16_t sum = ((0X0000 + check_sum[0]) << 8) + check_sum[1];
	sum += byte;

	check_sum[0] = static_cast<uint8_t>((sum >> 8) & 0XFF);
	check_sum[1] = static_cast<uint8_t>(sum & 0XFF);

	identifier = byte;
}

QtPacketParser::QtPacketParser(uint8_t* buffer)
{
	//前两个字节为要访问的地址值
	target_addr = 0;
	target_addr |= buffer[0];
	target_addr = target_addr << 8;
	target_addr |= buffer[1];
	
	//第三个字节为CMD
	cmd_bit = buffer[2];
	
	//第四个字节为数据长度
	data_length = buffer[3];
	
	//数据的第一个字节为长度，其余为加密后的密码数据
	data_ptr = buffer + 3;
}
