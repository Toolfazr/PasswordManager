#include "password_manager.h"

bool PasswordManager::vfy_state = false;

PasswordManager::PasswordManager():
shell(),
rom(),
sensor()
{
	OS::init();
	Bus::init();
	init_exti();
	init_soft_iic();
}

void PasswordManager::run()
{
	wrapper* w = new wrapper [1];
	w->obj = this;
	w->function = init_and_debug;
	xTaskCreate((TaskFunction_t)c_wrapper_overload, "task_init_debug", 128, w, 5, &OS::task_init_debug_handle);
	
	wrapper* w_1 = new wrapper [1];
	w_1->obj = this;
	w_1->function = empty;
	xTaskCreate((TaskFunction_t)c_wrapper_overload, "task_empty", 128, w_1, 4, &OS::task_empty_handle);
	
	wrapper* w_2 = new wrapper [1];
	w_2->obj = this;
	w_2->function = cmd;
	xTaskCreate((TaskFunction_t)c_wrapper_overload, "task_do_cmd", 384, w_2, 6, &OS::task_do_cmd_handle);
	
	wrapper* w_3 = new wrapper [1];
	w_3->obj = this;
	w_3->function = rec_ack;
	xTaskCreate((TaskFunction_t)c_wrapper_overload, "task_rec_ack", 128, w_3, 5, &OS::task_rec_ack_handle);
	
	wrapper* w_4 = new wrapper [1];
	w_4->obj = this;
	w_4->function = match;
	xTaskCreate((TaskFunction_t)c_wrapper_overload, "task_match_finger", 256, w_4, 5, &OS::task_match_finger_handle);

	wrapper* w_5 = new wrapper [1];
	w_5->obj = this;
	w_5->function = rom_search;
	xTaskCreate((TaskFunction_t)c_wrapper_overload, "task_search", 128, w_5, 5, &OS::task_search_handle);

	wrapper* w_6 = new wrapper [1];
	w_6->obj = this;
	w_6->function = rom_store;
	xTaskCreate((TaskFunction_t)c_wrapper_overload, "task_store", 128, w_6, 5, &OS::task_store_handle);

	wrapper* w_7 = new wrapper [1];
	w_7->obj = this;
	w_7->function = rom_delete;
	xTaskCreate((TaskFunction_t)c_wrapper_overload, "task_delete", 128, w_7, 5, &OS::task_delete_handle);

	//delete [] w;
	//Do NOT delete or change w, Do NOT define w as a stack var, its memory will be used in task
	vTaskStartScheduler();
}

void PasswordManager::task_init_debug()
{
	for(;;)
	{
		OS::wait_start_cmd(OS::CMD_INIT_DEBUG);
		//empty
	}
}

void PasswordManager::task_empty()
{
	for(;;)
	{
		//防止空转
	}
}

void PasswordManager::task_do_cmd()
{
	for(;;)
	{
		shell.do_cmd();
	}
}

void PasswordManager::task_rec_ack()
{
	for(;;)
	{
		sensor.rec_ack_packet();
	}	
}

void PasswordManager::task_match_finger()
{
	for(;;)
	{
		OS::wait_finger_attached();
		vfy_state = sensor.finger_is_matched();
	}
}

//QtPacket只有target_addr与cmd_bit为有效信息
void PasswordManager::task_search()
{
	for(;;)
	{
		OS::wait_start_cmd(OS::CMD_SEARCH);
		uint8_t* ptr = NULL;
		size_t ptr_value = 0XFFFFFFFF;
		OS::rec_queue_pac(&ptr_value);
		ptr = (uint8_t*)ptr_value;
		
		if(check_vfy_state() == false)
		{
			delete [] ptr;
			uint8_t error_ack[2] = {NO_FINGER_VFY, END_FLAG};
			Bus::uart_2_send_bytes(error_ack, 2);
			continue;
		}
			
		//发送从EEPROM中读到的数据
		QtPacketParser parser(ptr);
		uint8_t len = rom.read_byte(parser.get_target_addr());
		
		uint8_t* buffer = new uint8_t [len + 2];
		buffer[0] = PASSWORD_DATA;
		buffer[len + 1] = END_FLAG;
		rom.read_bytes(parser.get_target_addr(), buffer + 1, len);
		
		Bus::uart_2_send_bytes(buffer, len + 2);
		
		delete [] ptr;
		delete [] buffer;
		
		//end_access();
	}
}

void PasswordManager::task_store()
{
	for(;;)
	{
		OS::wait_start_cmd(OS::CMD_STORE);
		
		uint8_t* ptr = NULL;
		size_t ptr_value = 0XFFFFFFFF;
		OS::rec_queue_pac(&ptr_value);
		ptr = (uint8_t*)ptr_value;
		
		if(check_vfy_state() == false)
		{
			delete [] ptr;
			uint8_t error_ack[2] = {NO_FINGER_VFY, END_FLAG};
			Bus::uart_2_send_bytes(error_ack, 2);
			continue;
		}
		
		QtPacketParser parser(ptr);
		rom.write_bytes(parser.get_target_addr(), parser.get_data_ptr(), parser.get_data_length());
		
		//发送store成功的标志位以及store的数据
		uint8_t* buffer = new uint8_t [parser.get_data_length() + 2];
		buffer[0] = STORE_SUCCESS;
		rom.read_bytes(parser.get_target_addr(), buffer + 1, parser.get_data_length());
		buffer[parser.get_data_length() + 1] = END_FLAG;
		Bus::uart_2_send_bytes(buffer, parser.get_data_length() + 2);
		
		delete [] buffer;
		delete [] ptr;
		
		//end_access();
	}
}

//QtPacket只有target_addr与cmd_bit为有效信息
void PasswordManager::task_delete()
{
	for(;;)
	{
		OS::wait_start_cmd(OS::CMD_DELETE);	
		
		uint8_t* ptr = NULL;
		size_t ptr_value = 0XFFFFFFFF;
		OS::rec_queue_pac(&ptr_value);
		ptr = (uint8_t*)ptr_value;
		
		if(check_vfy_state() == false)
		{
			delete [] ptr;
			uint8_t error_ack[2] = {NO_FINGER_VFY, END_FLAG};
			Bus::uart_2_send_bytes(error_ack, 2);
			continue;
		}
		
		QtPacketParser parser(ptr);
		uint8_t len = rom.read_byte(parser.get_target_addr());
		uint8_t* buffer = new uint8_t [len];
	
		for(size_t i = 0; i < len; ++i)
		{
			buffer[i] = 0XEE;
		}
		
		rom.write_bytes(parser.get_target_addr(), buffer, len);
		
		uint8_t ack[2] = {DELETE_SUCCESS, END_FLAG};
		Bus::uart_2_send_bytes(ack, 2);
		
		delete [] buffer;
		delete [] ptr;
		
		//end_access();
	}
}

bool PasswordManager::check_vfy_state()
{	
	return vfy_state;
}

void PasswordManager::end_access()
{
	vfy_state = false;
}

void c_wrapper(void* obj, enum wrapper_funcs function)
{
	PasswordManager* pm = static_cast<PasswordManager*>(obj);
	if(pm)
	{
		switch(function)
		{
			case empty:
				pm->task_empty();//防止空转卡死
			break;
			
			case init_and_debug:
				pm->task_init_debug();
			break;
			
			case cmd:
				pm->task_do_cmd();
			break;

			case rec_ack:
				pm->task_rec_ack();
			break;
			
			case match:
				pm->task_match_finger();
			break;

			case rom_search:
				pm->task_search();
			break;

			case rom_store:
				pm->task_store();
			break;

			case rom_delete:
				pm->task_delete();
			break;
		}
	}
}

extern "C" void c_wrapper_overload(wrapper* w)
{
	c_wrapper(w->obj, w->function);
}

void PasswordManager::init_exti()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef gpio_b_init_struct;
	gpio_b_init_struct.GPIO_Pin = GPIO_Pin_5;
	gpio_b_init_struct.GPIO_Mode = GPIO_Mode_IPU;
	gpio_b_init_struct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &gpio_b_init_struct);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource5);
	
	EXTI_InitTypeDef exti_init_struct;
	exti_init_struct.EXTI_Line = EXTI_Line5;
	exti_init_struct.EXTI_Mode = EXTI_Mode_Interrupt;
	exti_init_struct.EXTI_Trigger = EXTI_Trigger_Rising;
	exti_init_struct.EXTI_LineCmd = ENABLE;
	EXTI_Init(&exti_init_struct);
	
	InterruptController::config(exti, 7, 0);
	EXTI_ClearFlag(EXTI_Line5);
}

void PasswordManager::init_soft_iic()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOB, GPIO_Pin_12 | GPIO_Pin_13);
}

extern "C" void EXTI9_5_IRQHandler(void)
{
	portBASE_TYPE pdHigherPriorityTaskWoken = pdFALSE;
	if(EXTI_GetITStatus(EXTI_Line5) == SET)
	{
		if(OS::finger_attached() == true)
			pdHigherPriorityTaskWoken = pdTRUE;
		EXTI_ClearITPendingBit(EXTI_Line5);
	}
	portYIELD_FROM_ISR(pdHigherPriorityTaskWoken);
}
