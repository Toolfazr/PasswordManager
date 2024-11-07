#include "finger_sensor.h"
#include "communicator.h"

FingerSensor::FingerSensor():
has_ack(false),
first(true),
ack(NULL)
{
	//empty
}

void FingerSensor::rec_ack_packet()
{
	//初始化一下
	uint8_t* bytes = new uint8_t [20];
	for(size_t i = 0; i < 20; ++i)
	{
		bytes[i] = '\0';
	}
	
	size_t len = Bus::has_bytes();
	if(Bus::uart_1_rec_bytes(bytes, len) && len == 0)
	{
		uint8_t load_index = 0;
		uint8_t len_index = 0;
		uint16_t load_len = 0;

		load_index = 6 + 1 + 2;//head_size + identifier_size + len_size
		len_index = 6 + 1;//head_size + identifier_size

		load_len = (static_cast<uint16_t>(bytes[len_index]) << 8) + bytes[len_index + 1];
		load_len -= 2;//check_sum_size
		
		if(first)//首次接收应答时无需删除先前空间
		{
			ack = new Packet(bytes + load_index, load_len);
			first = false;
		}
		else
		{
			delete ack;
			ack = NULL;
			ack = new Packet(bytes + load_index, load_len);
		}
		has_ack = true;
	}
	else
	{
		//empty
	}
	delete [] bytes;
}

//通过该函数删除指纹，可以在task_init_debug中调用
bool FingerSensor::del_all_fingerprint()
{
	uint8_t load = 0X0D;
	Packet pac(&load, 1);
	pac.set_identifier(0X01);
	send_pac(pac);
	OS::delay(100);
	if(ack->get_ack_code() != 0X00 || has_ack == false)
	{
		return false;
	}
	
	has_ack = false;
	return true;
}

//通过该函数烧录指纹，可以在task_init_debug中调用
bool FingerSensor::reg_finger()
{	
	//get image
	{
		uint8_t load = 0X01;
		Packet pac(&load, 1);
		pac.set_identifier(0X01);
		send_pac(pac);
		Communicator::print("Get image first time\r\n");
		OS::delay(100);
		if(ack->get_ack_code() != 0X00 || has_ack == false)
		{
			return false;
		}
		has_ack = false;
	}
	
	//generate character_1
	{
		uint8_t load[2] = {0X02, 0X01};
		Packet pac(load, 2);
		pac.set_identifier(0X01);
		send_pac(pac);
		Communicator::print("Generate charater A\r\n");
		OS::delay(100);
		if(ack->get_ack_code() != 0X00 || has_ack == false)
		{
			return false;
		}
		has_ack = false;
	}
	
	//get image again
	{
		uint8_t load = 0X01;
		Packet pac(&load, 1);
		pac.set_identifier(0X01);
		send_pac(pac);
		Communicator::print("Get image second time\r\n");
		OS::delay(100);
		if(ack->get_ack_code() != 0X00 || has_ack == false)
		{
			return false;
		}
		has_ack = false;
	}

	//generate character_2
	{
		uint8_t load[2] = {0X02, 0X02};
		Packet pac(load, 2);
		pac.set_identifier(0X01);
		send_pac(pac);
		Communicator::print("Generate charater B\r\n");
		OS::delay(100);
		if(ack->get_ack_code() != 0X00 || has_ack == false)
		{
			return false;
		}
		has_ack = false;
	}
	
	//match
	{
		uint8_t load = 0X03;
		Packet pac(&load, 1);
		pac.set_identifier(0X01);
		send_pac(pac);
		Communicator::print("Matching two characters\r\n");
		OS::delay(100);
		if(ack->get_ack_code() != 0X00 || has_ack == false)
		{
			return false;
		}
		has_ack = false;
	}

	//combine ch_1 & ch_2 to model
	{
		uint8_t load = 0X05;
		Packet pac(&load, 1);
		pac.set_identifier(0X01);
		send_pac(pac);
		Communicator::print("Mixing charater A & B to fingerprint model\r\n");
		OS::delay(100);
		if(ack->get_ack_code() != 0X00 || has_ack == false)
		{
			return false;
		}
		has_ack = false;
	}

	//store model
	{
		uint8_t load[4] = {0X06, 0X01, 0X00, 0X01};
		Packet pac(load, 4);
		pac.set_identifier(0X01);
		send_pac(pac);
		Communicator::print("Storing model\r\n");
		OS::delay(100);
		if(ack->get_ack_code() != 0X00 || has_ack == false)
		{
			OS::delay(50);
			return false;
		}
		has_ack = false;
	}
	
	return true;
}

bool FingerSensor::finger_is_matched()
{
	//get image
	{
		uint8_t load = 0X01;
		Packet pac(&load, 1);
		pac.set_identifier(0X01);
		send_pac(pac);
		OS::delay(30);
		if(ack->get_ack_code() != 0X00 || has_ack == false)
		{
			return false;
		}
		has_ack = false;
	}

	//generate character
	{
		uint8_t load[2] = {0X02, 0X01};
		Packet pac(load, 2);
		pac.set_identifier(0X01);
		send_pac(pac);
		OS::delay(30);
		if(ack->get_ack_code() != 0X00 || has_ack == false)
		{
			return false;
		}
		has_ack = false;
	}

	//get model
	{
		uint8_t load[4] = {0X07, 0X02, 0X00, 0X01};
		Packet pac(load, 4);
		pac.set_identifier(0X01);
		send_pac(pac);
		OS::delay(30);
		if(ack->get_ack_code() != 0X00 || has_ack == false)
		{
			return false;
		}
		has_ack = false;
	}
	
	//match
	{
		uint8_t load = 0X03;
		Packet pac(&load, 1);
		pac.set_identifier(0X01);
		send_pac(pac);
		OS::delay(30);
		if(ack->get_ack_code() != 0X00 || has_ack == false)
		{
			return false;
		}
		has_ack = false;
	}
	
	return true;
}

void FingerSensor::send_pac(Packet& pac)
{
	uint8_t* array = NULL;
	size_t len = pac.to_array(array);
	Bus::uart_1_send_bytes(array, len);
	OS::delay(30);
	delete [] array;
}

FingerSensor::~FingerSensor()
{
	//empty
}
