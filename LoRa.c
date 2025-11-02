#include <LoRa.h>

#include <hal.h>
#include <spi.h>


uint8_t new_lora(struct lora* lora) {
	uint8_t lora_version;
	/* Default pins */
	lora->lora_port = LORA_PORT;
	lora->cs_pin = CS_PIN;
	lora->rst_pin = RST_PIN;
	lora->dio0_pin = IRQ_PIN;
	lora->lspi = spi1;

	gpio_set_mode(CS_PIN|RST_PIN, GPIO_MODE_OUTPUT, LORA_PORT); /* Set CS pin */
	gpio_write_pin(LORA_PORT, CS_PIN|RST_PIN, GPIO_PIN_SET); 

	/* Default values for loraWAN modem, don't care
	 * about messing with these.
	 * Should give us a range of 3-4km, according to LoRa
	 * modem calculate by semtech.
	 */
	lora->freq = FREQ_433;
	lora->sf = SF_7;
	lora->bw = BW_125KHz;
	lora->crcrate = CR_4_5;
	lora->preamb = PREAMB_8;
	lora->db_pwr = POWER_20dB;
	lora->ocp = OCP_100;
	lora->curr_mode = STDBY;

	
	/* Initialize LoRa */
	lora_set_mode(lora, SLEEP);
	lora_write_reg(lora, RegOpMode, 0x80); /* Set RegOP to LoRa mode */
	lora_set_mode(lora, STDBY);

	lora_read_reg(lora, RegVersion, &lora_version);

	return lora_version;
}


void lora_write_reg(struct lora* lora, uint8_t addr, uint8_t val) {
	uint8_t reg[2];
	static const size_t reg_len = 2;

	reg[0] = 0x80 | addr;
	reg[1] = val;

	gpio_write_pin(LORA_PORT, CS_PIN, GPIO_PIN_RESET);
	spi_transmit_receive(lora->lspi, reg, 0, reg_len);
	gpio_write_pin(LORA_PORT, CS_PIN, GPIO_PIN_SET);
}

void lora_read_reg(struct lora* lora, uint8_t addr, uint8_t* out) {
	uint8_t reg[2];
	uint8_t rx_buf[2];
	static const size_t reg_len = 2;

	reg[0] = addr & 0x7F; 
	reg[1] = 0;

	gpio_write_pin(LORA_PORT, CS_PIN, GPIO_PIN_RESET);
	spi_transmit_receive(lora->lspi, reg, rx_buf, reg_len);
	gpio_write_pin(LORA_PORT, CS_PIN, GPIO_PIN_SET);
	
	*out = rx_buf[1];
}

void lora_set_mode(struct lora* lora, uint8_t mode) {
	uint8_t curr_op = 0;

	lora_read_reg(lora, RegOpMode, &curr_op);
	curr_op = (uint8_t) ((curr_op & ~7U) | mode); /* Overwrite mode bits */

	lora_write_reg(lora, RegOpMode, curr_op);
	lora->curr_mode = mode;
}

	

/* mode &= (7U);
 * mode |= (MODE)
 */
