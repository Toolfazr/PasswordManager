#pragma once

#include "stm32f10x.h"                  // Device header
#include "interrupt_support.h"
#include "data_type.h"
#include "os.h"

//串口、IIC等相关配置与底层读写函数
class Bus
{
public:
	static void init();
	static void uart_1_send_bytes(uint8_t* buffer, size_t len);
	static void uart_2_send_bytes(uint8_t* buffer, size_t len);
	static void uart_2_send_byte(uint8_t byte);

	//当一次传输未完成, 即无可用的完整数据包时，两个函数阻塞
	//当一次传输完成时，读出len长度数据至buffer中
	//如果当前可读取的数据量不为len则返回false，否则返回true
	static bool uart_1_rec_bytes(uint8_t* buffer, size_t len);
	static bool uart_2_rec_bytes(uint8_t* buffer, size_t len);
	
	//中断函数等通过该方法向buffer存入单个字节数据
	static void store_byte(uint8_t byte);
	//获取环形缓冲区可用字节数
	static size_t has_bytes();

	static void iic_start();
	static void iic_stop();
	static void iic_send_byte(uint8_t byte);
	static uint8_t iic_rec_byte();
	static void iic_send_ack(uint8_t ack_bit);
	static uint8_t iic_rec_ack();
private:
	static inline void iic_write_scl(uint8_t bit_value)
	{
		GPIO_WriteBit(GPIOB, GPIO_Pin_12, (BitAction)bit_value);
		OS::delay(1);
	}

	static inline void iic_write_sda(uint8_t bit_value)
	{
		GPIO_WriteBit(GPIOB, GPIO_Pin_13, (BitAction)bit_value);
		OS::delay(1);
	}

	static inline uint8_t iic_read_sda()
	{
		uint8_t bit_value = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13);
		OS::delay(1);
		return bit_value;
	}

	static RingBuffer* buffer;
};


