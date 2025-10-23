#ifndef UART_H__
#define UART_H__

#include <stdint.h>
#include <hal.h>

#define UART1 ((struct uart *) 0x40011000)
#define UART2 ((struct uart *) 0x40004400)
#define UART6 ((struct uart *) 0x40011400)

#define UART1_TX (PIN_NUM(2))
#define UART1_RX (PIN_NUM(3))
#define UART1_PORT ('A')

struct uart {
	volatile uint32_t SR, DR, BRR, CR1, CR2, CR3, GTPR;
};

static inline void uart_init(struct uart* uart, unsigned long baud, uint32_t uart_pins, uint8_t port) {

	uint8_t af = 7; /* uart AF num */
	uint32_t pins = uart_pins;

	if (uart == UART1) RCC->APB2ENR |= BIT(4); /* Hard coded UART1 */
	if (uart == UART2) RCC->APB1ENR |= BIT(17);

	gpio_set_mode(pins, GPIO_MODE_AF, port);
	gpio_set_af(pins, af, port);

	uart->CR1 = 0;
	uart->BRR = CLK_FREQ / baud;
	uart->CR1 = BIT(13) | BIT(2) | BIT(3);
}

static inline int uart_read_ready(struct uart *uart) {
	return uart->SR & BIT(5);
}

static inline uint8_t uart_read_byte(struct uart *uart) {
	return (uint8_t) (uart->DR & 255);
}

static inline void spin(uint32_t delay) {
	while(delay--) (void) 0;
}

static inline void uart_write_byte(struct uart *uart, uint8_t byte) {
	uart->DR = byte;
	while ((uart->SR & BIT(7)) == 0) spin(1);
}

static inline void uart_write_buf(struct uart *uart, char *buf, size_t len) {
	while (len-- > 0) uart_write_byte(uart, *(uint8_t *) buf++);
}

#endif
