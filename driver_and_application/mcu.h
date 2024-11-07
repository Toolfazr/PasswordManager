#include "stm32f10x.h"
#include <cstdint>
#include <cstddef>
#include <map>
#include <string>

template <typename T>
class interrupt_handlers
{
public:
	static void uart_1_handler();
	static void uart_2_handler();
	static void spi_1_handler();
};

class MCU : public interrupt_handlers<MCU>
{
public:
	MCU();
	void set_communication_buffer(std::string, size_t size);
	const std::string mcu_name;
	void uart_1_send_bytes(void* buffer, size_t len);
	void uart_1_rec_bytes(void* buffer, size_t len);
	void uart_2_send_bytes(void* buffer, size_t len);
	void uart_2_rec_bytes(void* buffer, size_t len);
	void spi_1_send_bytes(void* buffer, size_t len);
	void spi_1_rec_bytes(void* buffer, size_t len);

private:
	std::map<std::string, size_t> buffer_size;
	void* uart_1_send_buffer;
	void* uart_1_rec_buffer;
	void* uart_2_send_buffer;
	void* uart_2_rec_buffer;
	void* spi_1_send_buffer;
	void* spi_1_rec_buffer;
};
