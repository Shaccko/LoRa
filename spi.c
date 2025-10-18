#include <stdint.h>
#include <spi.h>
#include <hal.h>



void spi_init(struct spi* spi) {
	/* Define SCL baud rate, SPI_CR1
	 * Select CPOL and CPHA bits for relationship type
	 * and other stuff
	 */

	spi->CR1 = SPI_ENABLE | SPI_MASTER | SPI_8BITMODE | 
		SPI_CLKMODE2 | SPI_MSBFIRST | SPI_NSS_SOFT |
		SPI_BAUDRATE8;
	spi->CR2 = SPI_TIMODE;
	
