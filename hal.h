#ifndef HAL_H__
#define HAL_H__

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include <rcc.h>


#define BIT(x) (1UL << (x))
#define GPIO(bank) ((struct gpio*) (0x40020000 + 0x400 * (bank)))
#define PIN(bank, num) ((((bank) - 'A') << 8) | (num))
#define PINNO(pin) (pin & 255)
#define PINBANK(pin) (pin >> 8)
#define MASK 0x3U

struct gpio {
	volatile uint32_t MODER, OTYPER, OSPEEDR, PUPDR, IDR, ODR, BSRR, LCKR,
		 AFR[2];
};

enum { GPIO_MODE_INPUT, GPIO_MODE_OUTPUT, GPIO_MODE_AF, GPIO_MODE_ANALOG };

static inline void gpio_set_mode(uint16_t pin, uint8_t MODE) {
	struct gpio *gpio = GPIO(PINBANK(pin));
	RCC->AHB1ENR |= BIT(PINBANK(pin)); /* Enable pin CLK */
	int n = PINNO(pin);
	

	/*Clear, and set pin*/
	gpio->MODER &= ~(MASK << (n * 2));
	gpio->MODER |= (MODE & MASK) << (n * 2);
}

static inline void gpio_write(uint16_t pin, bool val) {
	struct gpio *gpio = GPIO(PINBANK(pin));

	gpio->BSRR = (1U << PINNO(pin)) << (val ? 0 : 16);
}

static inline void gpio_set_af(uint16_t pin, uint8_t af_num) {
	struct gpio *gpio = GPIO(PINBANK(pin));
	int n = PINNO(pin);

	/* 00000000 00000111 
	 * & 7 = 00000111
	 * * 4 = 28 = 00011100
	 */

	gpio->AFR[n >> 3] &= ~(15UL << ((n & 7) * 4));
	gpio->AFR[n >> 3] |= ((uint32_t) af_num) << ((n & 7) * 4);
}

#endif
