#include <inttypes.h>
#include <stddef.h>
#include <stdbool.h>

#include <rcc.h>
#include <hal.h>
#include <spi.h>

#define LED_PIN(pin) ((1U << (pin)))
#define LED_PORT 'A'

int main(void) {
	/* Configure hal.h to hold pin bank and pins, 32bits can fit both */
	uint32_t led = LED_PIN(5);
	uint8_t port = LED_PORT;

	systick_init();
	gpio_set_mode(led, GPIO_MODE_OUTPUT, port);
	for (;;) {
		gpio_write(led, true, port);
		delay(1000);
		gpio_write(led, false, port);
		delay(1000);
	}
	return 0;
}
