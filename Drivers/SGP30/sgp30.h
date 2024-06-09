#ifndef SGP30_H
#define SGP30_H

#include "stm32f1xx_hal.h"
#include "si2c.h"
#include "systick.h"
#include "main.h"
#include "string.h"

typedef struct sgp30 {
	uint16_t co2eq_raw;
	uint16_t tvoc_raw;
	uint8_t co2eq_crc;
	uint8_t tvoc_crc;
	uint16_t co2eq;
	uint16_t tvoc;
} SGP30;

void SGP30_SInit(void);
uint8_t SGP30_SWriteCommand(uint8_t CMD_MSB, uint8_t CMD_LSB);
void SGP30_SReadData(SGP30 *sgp30, uint8_t CMD_MSB, uint8_t CMD_LSB);

void SGP30_Init(void);
void SGP30_WriteCommand(uint8_t CMD_MSB, uint8_t CMD_LSB);
void SGP30_ReadData(SGP30 *sgp30, uint8_t CMD_MSB, uint8_t CMD_LSB,uint16_t Attempts);

#endif // SGP30_H
