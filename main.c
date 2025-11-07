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
	uint8_t lora_msg[20] = "hello";
	

	uart2_init();
	spi1_init();

	systick_init();
	lora_version = new_lora(&lora);
	uint8_t counter = 0;
	for (;;) {
		if (lora_version && counter == 0) {
			uart_write_buf(uart2, "lora pass\r\n", 11);
			counter = 1;
		}
		lora_transmit(&lora, (uint8_t*)"Hello", 5);
		delay(50);
	}
	return 0;
}
