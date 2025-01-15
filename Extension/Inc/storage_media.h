#pragma once

#include "data_type.h"
#include "bus.h"
#include "os.h"
#include "communicator.h"

class StorageMedia
{
public:
	void write_byte(uint16_t addr, uint8_t data);
    void write_bytes(uint16_t addr, uint8_t *buffer, size_t num);
    uint8_t read_byte(uint16_t addr);
    void read_bytes(uint16_t addr, uint8_t *buffer, size_t num);
	void print_byte(uint16_t addr);
	void print_bytes(uint16_t addr, size_t nums);
};
