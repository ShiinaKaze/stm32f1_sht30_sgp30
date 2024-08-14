#ifndef SHT30_H
#define SHT30_H

#include "main.h"

typedef struct sht30
{
    uint16_t temp_raw;
    uint8_t temp_crc;
    uint16_t hum_raw;
    uint8_t hum_crc;
    float temp;
    float hum;
} SHT30_TypeDef;

#define SHT30_ACK 0
#define SHT30_NACK 1


void SHT30_Init(void);
void SHT30_Set_Periodic_Data_Acquisition_Mode(uint8_t CMD_MSB, uint8_t CMD_LSB);
void SHT30_Measure_Periodic_Mode(SHT30_TypeDef *sht30);
#endif // SHT30_H
