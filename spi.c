#include <stdint.h>
#include <spi.h>
#include <hal.h>

void spi_init(struct spi* spi, uint32_t spi_pins, uint8_t spi_port) {
	/* Define SCL baud rate, SPI_CR1
	 * Select CPOL and CPHA bits for relationship type
	 * and other stuff
	 */

	uint8_t spi_af = 5;
	/* SPI1 config only for now */

	gpio_set_mode(spi_pins, GPIO_MODE_AF, spi_port);
	gpio_set_af(spi_pins, spi_af, spi_port);

	spi->CR1 = 0;
	spi->CR1 = SPI_MASTER | SPI_8BITMODE | 
		SPI_CLKMODE2 | SPI_MSBFIRST | SPI_NSS_SOFT |
		SPI_BAUDRATE8;
	spi->CR2 = SPI_TIMODE | SPI_TXEIE | SPI_RXNEIE;
}

void spi_write_buf(struct spi* spi, uint8_t* buf) {
	spi->DR = (uint32_t)buf;
}

void spi_transmit_data(struct spi* spi, uint8_t* buf, size_t len) {
	while (len--) spi_write_buf(spi, buf++);
}

