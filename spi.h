#ifndef SPI_H__
#define SPI_H__
#include <stdint.h>


#define SPI1 ((struct spi*) (0x40003800))
#define SPI2 ((struct spi*) (0x40003C00))
#define SPI5 ((struct spi*) (0x40015000))

#define SPI_MASTER (BIT(2) | BIT(8) | BIT(1)) /* Master and enable bit */
#define SPI_8BITMODE (BIT(11))
#define SPI_CLKMODE2 ((BIT(1) | ~BIT(0)))
#define SPI_MSBFIRST (~BIT(7))
#define SPI_NSS_SOFT (BIT(9))
#define SPI_BAUDRATE8 (3UL << 3)
#define SPI_TIMODE (BIT(4))


struct spi {
	volatile uint32_t CR1, CR2, SR, DR, CRCPR, RXCRCR, TXCRCR;
};



#endif
