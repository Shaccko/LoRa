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
	uint8_t buf[] = "ahugestrin";
	char* msg = "Uart working\r\n";
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
		spi_transmit_data(spi1, buf, 10);
		uart_write_buf(uart1, msg, strlen(msg));
		delay(5);
	}
	return 0;
}
