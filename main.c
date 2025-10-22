#include <inttypes.h>
#include <stddef.h>
#include <stdbool.h>

#include <rcc.h>
#include <hal.h>
#include <spi.h>

#define LED_PIN(pin) (BIT(pin))
#define LED_PORT 'A'

int main(void) {
	/* Configure hal.h to hold pin bank and pins, 32bits can fit both */
	uint32_t led = LED_PIN(5);
	uint8_t port = LED_PORT;
	uint8_t buf[] = "ahugestrin";
	struct spi* spi1 = SPI1;
	uint32_t spi1_pins = SCK1_PIN | MOSI1_PIN | MISO1_PIN | NSS1_PIN;
	uint8_t spi1_port = SPI1_PORT;

	systick_init();
	spi_init(spi1, spi1_pins, spi1_port);
	for (;;) {
		spi_transmit_data(spi1, &buf, 10);
		gpio_write(led, true, port);
		delay(5);
		gpio_write(led, false, port);
		delay(5);
	}
	return 0;
}
