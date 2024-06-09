#ifndef SI2C_H
#define SI2C_H

#include "stm32f1xx_hal.h"
#include "systick.h"

#define I2C_ACK 0
#define I2C_None_ACK 1

void SI2C_Start(GPIO_TypeDef *GPIOx, uint16_t SCL_Pin, uint16_t SDA_Pin);
void SI2C_Stop(GPIO_TypeDef *GPIOx, uint16_t SCL_Pin, uint16_t SDA_Pin);
uint8_t SI2C_TransmitByte(GPIO_TypeDef *GPIOx, uint16_t SCL_Pin, uint16_t SDA_Pin, uint8_t Byte);
uint8_t SI2C_ReceiveByte(GPIO_TypeDef *GPIOx, uint16_t SCL_Pin, uint16_t SDA_Pin, GPIO_PinState ACK);
#endif // __SW_I2C_H
