#pragma once

#include "FreeRTOS.h"
#include "task.h"
#include "event_groups.h"
#include "semphr.h"

//封装FreeRTOS相关函数
class OS
{
public:
	static void init();
	//等待uart一个传输过程的结束
	inline static void wait_uart_1_tc()
	{
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
	}
	
	inline static void wait_uart_2_tc()
	{
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
	}
	
	inline static void wait_finger_attached()
	{
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
	}
	inline static void disable_slice()
	{
		vTaskSuspendAll();
	}
	inline static void enable_slice()
	{
		if(xTaskResumeAll())
		{
			taskYIELD();
		}
	}
	//通知对应的wait函数解除阻塞，根据情况返回一个bool值
	static bool uart_1_tc();
	static bool uart_2_tc();
	static bool finger_attached();

	static TaskHandle_t task_init_debug_handle;
	static TaskHandle_t task_empty_handle;
	static TaskHandle_t task_do_cmd_handle;
	static TaskHandle_t task_rec_ack_handle;
	static TaskHandle_t task_match_finger_handle;
	static TaskHandle_t task_search_handle;
	static TaskHandle_t task_store_handle;
	static TaskHandle_t task_delete_handle;
	
	inline static void delay(size_t ms)
	{
		vTaskDelay(ms);
	}
	inline static void run_cmd(uint32_t cmd_bit)
	{
		xEventGroupSetBits(cmd_bits, cmd_bit);
	}
	
	inline static void wait_start_cmd(uint32_t cmd_bit)
	{
		xEventGroupWaitBits(cmd_bits, cmd_bit, pdTRUE, pdTRUE, portMAX_DELAY);
	}
	
	inline static bool send_queue_pac(size_t* ptr_value)
	{
		if(xQueueSend(queue_pacs, (void*)ptr_value, portMAX_DELAY) == pdPASS)
			return true;
		return false;
	}

	inline static bool rec_queue_pac(size_t* ptr_value)
	{
		if(xQueueReceive(queue_pacs, (void*)ptr_value, portMAX_DELAY) == pdPASS)
			return true;
		return false;
	}
	
	const static uint32_t CMD_INIT_DEBUG;
	const static uint32_t CMD_SEARCH;
	const static uint32_t CMD_STORE;
	const static uint32_t CMD_DELETE;
private:
	static EventGroupHandle_t cmd_bits;
	static QueueHandle_t queue_pacs;
	const static size_t MAX_QUEUE_NUM;
	const static size_t QUEUE_ITEM_SIZE;
};
