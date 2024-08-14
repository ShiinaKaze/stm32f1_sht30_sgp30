#ifndef SW_I2C_H
#define SW_I2C_H

#include "main.h"

#define SW_I2C_ACK 0
#define SW_I2C_None_ACK 1
#define SW_I2C_GPIOx GPIOB
#define SW_I2C_SCL_PIN GPIO_PIN_10
#define SW_I2C_SDA_PIN GPIO_PIN_11

void SW_I2C_Init(void);
void SW_I2C_Start(void);
void SW_I2C_Stop(void);
uint8_t SW_I2C_TransmitByte(uint8_t Byte);
uint8_t SW_I2C_ReceiveByte(uint8_t ACK);
#endif // SW_I2C_H
