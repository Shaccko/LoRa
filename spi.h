#ifndef SPI_H__
#define SPI_H__
#include <stdint.h>
#include <stddef.h>


#define SPI1 ((struct spi*) (0x40013000))
#define SPI2 ((struct spi*) (0x40003800))
#define SPI3 ((struct spi*) (0x40003C00))
#define SPI4 ((struct spi*) (0x40013400))
#define SPI5 ((struct spi*) (0x40015000))

#define SPI_MASTER (BIT(2) | BIT(8) | BIT(1)) /* Master and enable bit */
#define SPI_8BITMODE (BIT(11))
#define SPI_CLKMODE2 ((BIT(1) | ~BIT(0)))
#define SPI_MSBFIRST (~BIT(7))
#define SPI_NSS_SOFT (BIT(9))
#define SPI_BAUDRATE8 (3UL << 3)
#define SPI_TIMODE (BIT(4))
#define SPI_TXEIE (BIT(7))
#define SPI_RXNEIE (BIT(6))

#define SPI1_PORT 'A'
#define SCK1_PIN (PIN_NUM(5))
#define NSS1_PIN (PIN_NUM(4))
#define MOSI1_PIN (PIN_NUM(6))
#define MISO1_PIN (PIN_NUM(7))


struct spi {
	volatile uint32_t CR1, CR2, SR, DR, CRCPR, RXCRCR, TXCRCR;
};


void spi_init(struct spi* spi, uint32_t spi_pins, uint8_t spi_port);
void spi_write_buf(struct spi* spi, uint8_t* buf);
void spi_transmit_data(struct spi* spi, uint8_t* buf, size_t len);

#endif
