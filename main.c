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
	const char* tx_buf = "ahugestrin";
	char* msg = "Loop restarting\n\r";
	size_t tx_len = strlen(tx_buf);
	size_t msg_len = strlen(msg);
	char rx_buf[32];
	struct lora lora;
	

	spi1_init();
	uart2_init();
	new_lora(&lora);


	systick_init();
	for (;;) {
		lora_set_mode(&lora, 
		uart_write_buf(uart2, msg, msg_len);
		delay(5);
	}
	return 0;
}
