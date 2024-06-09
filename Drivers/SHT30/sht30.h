#ifndef SHT30_H
#define SHT30_H

#include "stm32f1xx_hal.h"
#include "si2c.h"
#include "main.h"
#include "systick.h"
#include "string.h"

typedef struct sht30 {
	uint16_t temp_raw;
	uint8_t temp_crc;
	uint16_t hum_raw;
	uint8_t hum_crc;
	float temp;
	float hum;
} SHT30;

void SHT30_SInit(void);
uint8_t SHT30_SWriteCommand(uint8_t CMD_MSB, uint8_t CMD_LSB);
void SHT30_SReadData(SHT30 *sht30, uint8_t CMD_MSB, uint8_t CMD_LSB);

void SHT30_Init(void);
void SHT30_WriteCommand(uint8_t CMD_MSB, uint8_t CMD_LSB);
void SHT30_ReadData(SHT30 *sht30, uint8_t CMD_MSB, uint8_t CMD_LSB,
		uint16_t Attempts);

#endif // SHT30_H
