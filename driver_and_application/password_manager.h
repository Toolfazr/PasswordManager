#pragma once

#include "bus.h"
#include "os.h"
#include "communicator.h"
#include "finger_sensor.h"
#include "storage_media.h"

enum wrapper_funcs {empty, init_and_debug, cmd, rec_ack, match, rom_search, rom_store, rom_delete};
extern "C" void c_wrapper(void* obj, enum wrapper_funcs function);

typedef struct
{
	void* obj;
	enum wrapper_funcs function;
} wrapper;
extern "C" void c_wrapper_overload(wrapper* w);

class PasswordManager
{
	friend void c_wrapper(void* obj, enum wrapper_funcs function);
	friend void c_wrapper_overload(wrapper* w);
public:
	PasswordManager();
	void run();
	
private:
	void init_exti();
	void init_soft_iic();
	void task_init_debug();
	void task_empty();
	void task_do_cmd();
	void task_rec_ack();
	void task_match_finger();
	void task_search();
	void task_store();
	void task_delete();

	static bool vfy_state;
	bool check_vfy_state();
	void end_access();
	Communicator shell;
	StorageMedia rom;
	FingerSensor sensor;

	const static uint8_t END_FLAG = 0XED;

//发送给Qt的应答位及其之后数据
	const static uint8_t NO_FINGER_VFY = 0X00;
	const static uint8_t PASSWORD_DATA = 0X01;
	const static uint8_t DELETE_SUCCESS = 0X02;
	const static uint8_t STORE_SUCCESS = 0X03;
};
