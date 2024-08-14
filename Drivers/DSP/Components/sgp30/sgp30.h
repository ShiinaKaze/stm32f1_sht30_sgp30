#ifndef SGP30_H
#define SGP30_H

#include "main.h"

typedef struct sgp30
{
    uint16_t co2eq_raw;
    uint16_t tvoc_raw;
    uint8_t co2eq_crc;
    uint8_t tvoc_crc;
    uint16_t co2eq;
    uint16_t tvoc;
} SGP30_TypeDef;

#define SGP30_ACK 0
#define SGP30_NACK 0

void SGP30_Init(void);
uint8_t SGP30_WriteCommand(uint8_t CMD_MSB, uint8_t CMD_LSB);
void SGP30_Measure_IAQ(SGP30_TypeDef *sgp30);
void SGP30_IAQ_Init(void);
#endif // SGP30_H
