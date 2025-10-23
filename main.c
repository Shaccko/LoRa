#include <inttypes.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>

#include <rcc.h>
#include <hal.h>
#include <spi.h>
#include <uart.h>

#define LED_PIN(pin) (BIT(pin))
#define LED_PORT 'A'

int main(void) {
	/* Configure hal.h to hold pin bank and pins, 32bits can fit both */
	const char* tx_buf = "ahugestrin";
	size_t tx_len = strlen(tx_buf);
	char rx_buf[32];

	struct spi* spi1 = SPI1;
	uint32_t spi1_pins = SCK1_PIN | MOSI1_PIN | MISO1_PIN | NSS1_PIN;
	uint8_t spi1_port = SPI1_PORT;

	struct uart* uart1 = UART2;
	uint32_t uart1_pins = UART1_TX | UART1_RX;
	uint8_t uart1_port = UART1_PORT;

	uart_init(uart1, 9600, uart1_pins, uart1_port);

	systick_init();
	spi_init(spi1, spi1_pins, spi1_port);
	for (;;) {
		spi_transmit_receive(spi1, (uint8_t*)tx_buf, (uint8_t*) rx_buf, tx_len);
		uart_write_buf(uart1, rx_buf, strlen(rx_buf));
		delay(5);
	}
	return 0;
}
