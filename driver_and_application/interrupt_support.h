#pragma once

#include "stm32f10x.h"
#include <cstdint>
#include <string>

//并未用到spi
enum peri_name {uart_1, uart_2, spi_1, exti};

class InterruptController
{
public:
	//set priority of each interrupt
	static void config(enum peri_name name, uint8_t preemtion_prio, uint8_t sub_prio);
private:
	static bool prioGroupIsSet;
};
