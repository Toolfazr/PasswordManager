#include "os.h"
#include "bus.h"

TaskHandle_t OS::task_init_debug_handle = NULL;
TaskHandle_t OS::task_empty_handle = NULL;
TaskHandle_t OS::task_do_cmd_handle = NULL;
TaskHandle_t OS::task_rec_ack_handle = NULL;
TaskHandle_t OS::task_match_finger_handle = NULL;
TaskHandle_t OS::task_search_handle = NULL;
TaskHandle_t OS::task_store_handle = NULL;
TaskHandle_t OS::task_delete_handle = NULL;

EventGroupHandle_t OS::cmd_bits = NULL;
QueueHandle_t OS::queue_pacs = NULL;

const uint32_t OS::CMD_INIT_DEBUG = (0X01 << 0);
const uint32_t OS::CMD_SEARCH = (0X01 << 1);
const uint32_t OS::CMD_STORE = (0X01 << 2);
const uint32_t OS::CMD_DELETE = (0X01 << 3);
const size_t OS::MAX_QUEUE_NUM = 3;
const size_t OS::QUEUE_ITEM_SIZE = sizeof(size_t);

void OS::init()
{	
	cmd_bits = xEventGroupCreate();
	queue_pacs = xQueueCreate(MAX_QUEUE_NUM, QUEUE_ITEM_SIZE);
}

bool OS::uart_1_tc()
{
	BaseType_t res = pdFALSE;
	vTaskNotifyGiveFromISR(task_rec_ack_handle, &res);
	
	if(res == pdFALSE)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool OS::uart_2_tc()
{
	BaseType_t res = pdFALSE;
	vTaskNotifyGiveFromISR(task_do_cmd_handle, &res);
	
	if(res == pdFALSE)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool OS::finger_attached()
{
	BaseType_t res = pdFALSE;
	vTaskNotifyGiveFromISR(task_match_finger_handle, &res);
	
	if(res == pdFALSE)
	{
		return false;
	}
	else
	{
		return true;
	}
}
