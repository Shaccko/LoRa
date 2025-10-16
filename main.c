#include <inttypes.h>
#include <stddef.h>
#include <stdbool.h>

#include <rcc.h>
#include <hal.h>
#include <uart.h>

int main(void) {
	struct uart* uart = UART2;
	uint16_t led = PIN('A', 5);
	uint8_t buf[] = "kekw\r\n";

	uart_init(uart, 115200);
	systick_init();
	gpio_set_mode(led, GPIO_MODE_OUTPUT);
	for (;;) {
		gpio_write(led, true);
		delay(1000);
		gpio_write(led, false);
		delay(1000);
		uart_write_buf(uart, (char*) &buf, sizeof(buf));
	}
	return 0;
}
