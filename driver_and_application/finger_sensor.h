#pragma once

#include "data_type.h"
#include "bus.h"
#include "os.h"

class FingerSensor
{
public:
	FingerSensor();
	~FingerSensor();
	bool del_all_fingerprint();
	bool finger_is_matched();
	bool reg_finger();
	void rec_ack_packet();
private:
	void send_pac(Packet& pac);
	bool has_ack;
	bool first;
	Packet* ack;
};
