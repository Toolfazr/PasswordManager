#include "storage_media.h"

void StorageMedia::write_byte(uint16_t addr, uint8_t data)
{
	OS::disable_slice();
    Bus::iic_start();
    Bus::iic_send_byte(0XA0);
    Bus::iic_rec_ack();

    Bus::iic_send_byte(addr>>8);
    Bus::iic_rec_ack();
    Bus::iic_send_byte(addr%256);
    Bus::iic_rec_ack();

    Bus::iic_send_byte(data);
    Bus::iic_rec_ack();

    Bus::iic_stop();
    OS::delay(5);
	OS::enable_slice();
}

void StorageMedia::write_bytes(uint16_t addr, uint8_t *buffer, size_t num)
{
	OS::disable_slice();
    Bus::iic_start();
    Bus::iic_send_byte(0XA0);
    Bus::iic_rec_ack();

    Bus::iic_send_byte(addr>>8);
    Bus::iic_rec_ack();
    Bus::iic_send_byte(addr%256);
    Bus::iic_rec_ack();

    size_t tmp = 0;
    while(num--)
    {
        Bus::iic_send_byte(buffer[tmp++]);
        Bus::iic_rec_ack();
    }

    Bus::iic_stop();
    OS::delay(5);
	OS::enable_slice();
}

uint8_t StorageMedia::read_byte(uint16_t addr)
{
	OS::disable_slice();
    Bus::iic_start();
    Bus::iic_send_byte(0XA0);
    Bus::iic_rec_ack();

    Bus::iic_send_byte(addr>>8);
    Bus::iic_rec_ack();
    Bus::iic_send_byte(addr%256);
    Bus::iic_rec_ack();

    Bus::iic_start();
    Bus::iic_send_byte(0XA1);
    Bus::iic_rec_ack();
	
	uint8_t ret = 0XEE;
    ret = Bus::iic_rec_byte();
    Bus::iic_send_ack(1);
    Bus::iic_stop();
	OS::enable_slice();
	
    return ret;
}

void StorageMedia::read_bytes(uint16_t addr, uint8_t* buffer, size_t num)
{
	OS::disable_slice();
    Bus::iic_start();
    Bus::iic_send_byte(0XA0);
    Bus::iic_rec_ack();

    Bus::iic_send_byte(addr>>8);
    Bus::iic_rec_ack();
    Bus::iic_send_byte(addr%256);
    Bus::iic_rec_ack();

    Bus::iic_start();
    Bus::iic_send_byte(0XA1);
    Bus::iic_rec_ack();

    uint8_t* tmp = buffer;
    while(num--)
    {
        *tmp = Bus::iic_rec_byte();
        (num == 0)?(Bus::iic_send_ack(1)):(Bus::iic_send_ack(0));
        tmp++;
    }
    
    Bus::iic_stop();
	OS::enable_slice();
}

void StorageMedia::print_byte(uint16_t addr)
{
	Communicator::print(read_byte(addr));
	Communicator::print("\r\n");
}

void StorageMedia::print_bytes(uint16_t addr, size_t num)
{
	uint8_t* buffer = new uint8_t [num];
	read_bytes(addr, buffer, num);
	for(size_t i = 0; i < num; ++i)
	{
		Communicator::print(buffer[i]);
		Communicator::print(" ");
	}
	Communicator::print("\r\n");
	delete [] buffer;
}
