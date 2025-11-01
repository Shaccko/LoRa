#ifndef LORA_H__
#define LORA_H__

#include <hal.h>

/* FiFo buffer and OP modes */
#define RegFifo 0x00
#define RegOpMode 0x01

/* Packet Config Registers */
#define RegPreambleMsb 0x25
#define RegSyncConfig 0x27
#define RegPacketConfig1 0x30

/* IRQ Registers */
#define RegIrqFlags 0x3e /* uint8_t f[2] */

/* DIOx Mapping Registers */
#define RegDioMapping 0x40

/* LoRa pins definitions */
#define LORA_PORT 'B'
#define CS_PIN (PIN_NUM(0))
#define RST_PIN (PIN_NUM(5))
#define IRQ_PIN (PIN_NUM(3))

/* LoRaWAN modem definitions */
#define FREQ_433 433
#define SF_7 0x7
#define BW_125KHz 0x7
#define CR_4_5 0x1
#define POWER_20dB 0xFF
#define OCP_100 0x100
#define PREAMB_8 0x8

enum { SLEEP, STDBY, FSTX, TX, FSRX, RXCONT, RXSINGLE, CAD };

struct lora {
	uint8_t lora_port;
	uint16_t cs_pin, rst_pin, dio0_pin;
	struct spi* lspi;

	uint16_t freq, ocp;
	uint8_t sf, bw, crcrate, preamb, db_pwr, curr_mode;
};



void new_lora(struct lora* lora);
void lora_write_reg(struct lora* lora, uint8_t addr, uint8_t val);
void lora_read_reg(struct lora* lora, uint8_t addr, uint8_t val, uint8_t* out);

#endif
