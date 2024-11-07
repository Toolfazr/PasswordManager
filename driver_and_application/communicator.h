#pragma once

#include "data_type.h"
#include "os.h"
#include "interrupt_support.h"
#include "bus.h"
#include <string>

class Communicator
{
public:
	static void debug(uint8_t byte);
	static void debug(const char* c_str);
	static void print(const char* c_str);
	static void print(uint8_t byte);
	void do_cmd();
private:
	static const size_t CMD_NUMS = 10;
	static const uint32_t MAX_CMD_BIT = 0X01 << 24;
	static const size_t MAX_BUFFER_SIZE = 128;
};
