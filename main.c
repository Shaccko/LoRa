#include <inttypes.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>

#include <rcc.h>
#include <hal.h>
#include <spi.h>
#include <uart.h>
#include <LoRa.h>

#define LED_PIN(pin) (BIT(pin))
#define LED_PORT 'A'

int main(void) {
	/* Configure hal.h to hold pin bank and pins, 32bits can fit both */

	char buf[32];
	struct lora lora;
	uint8_t lora_version = 0;
	

	spi1_init();
	uart2_init();

	lora_version = new_lora(&lora);

	systick_init();
	for (;;) {
		if (lora_version == 0x12) uart_write_buf(uart2, "y", 1);
		uart_write_buf(uart2, "done\r\n", 6);
		delay(5);
	}
	return 0;
}
