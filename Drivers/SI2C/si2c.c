/**
 * @file si2c.c
 * @author ShiinaKaze (shiinakaze@qq.com)
 * @brief Software I2C interface
 * @version 0.1
 * @date 2024-05-31
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "systick.h"
#include "si2c.h"

#define SI2C_Delay() Delay_us(6)

/**
 * @brief  I2C start condition
 * @param GPIOx
 * @param SCL_Pin
 * @param SDA_Pin
 * @retval None
 */
void SI2C_Start(GPIO_TypeDef *GPIOx, uint16_t SCL_Pin, uint16_t SDA_Pin)
{

	// pull up SCL,SDA for start
	HAL_GPIO_WritePin(GPIOx, SDA_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOx, SCL_Pin, GPIO_PIN_SET);
	SI2C_Delay();

	// I2C start
	HAL_GPIO_WritePin(GPIOx, SDA_Pin, GPIO_PIN_RESET);
	SI2C_Delay();
	HAL_GPIO_WritePin(GPIOx, SCL_Pin, GPIO_PIN_RESET);
	SI2C_Delay();
}

/**
 * @brief  I2C stop condition
 * @param GPIOx
 * @param SCL_Pin
 * @param SDA_Pin
 * @retval None
 */
void SI2C_Stop(GPIO_TypeDef *GPIOx, uint16_t SCL_Pin, uint16_t SDA_Pin)
{
	// pull down SDA for stop
	HAL_GPIO_WritePin(GPIOx, SDA_Pin, GPIO_PIN_RESET);
	SI2C_Delay();

	// I2C stop
	HAL_GPIO_WritePin(GPIOx, SCL_Pin, GPIO_PIN_SET);
	SI2C_Delay();
	HAL_GPIO_WritePin(GPIOx, SDA_Pin, GPIO_PIN_SET);
	SI2C_Delay();
}

/**
 * @brief Transmit one byte using I2C
 * @param GPIOx
 * @param SCL_Pin
 * @param SDA_Pin
 * @param Byte
 * @retval ACK
 */
uint8_t SI2C_TransmitByte(GPIO_TypeDef *GPIOx, uint16_t SCL_Pin, uint16_t SDA_Pin, uint8_t Byte)
{
	uint8_t ack = 1;
	for (uint8_t i = 0; i < 8; i++)
	{
		HAL_GPIO_WritePin(GPIOx, SDA_Pin, (Byte & (0x80 >> i)));
		SI2C_Delay();
		HAL_GPIO_WritePin(GPIOx, SCL_Pin, GPIO_PIN_SET);
		SI2C_Delay();
		HAL_GPIO_WritePin(GPIOx, SCL_Pin, GPIO_PIN_RESET);
		SI2C_Delay();
	}

	// receive ACK
	HAL_GPIO_WritePin(GPIOx, SCL_Pin, GPIO_PIN_SET);
	SI2C_Delay();
	ack = HAL_GPIO_ReadPin(GPIOx, SDA_Pin);
	SI2C_Delay();
	HAL_GPIO_WritePin(GPIOx, SCL_Pin, GPIO_PIN_RESET);
	SI2C_Delay();
	return ack;
}

/**
 * @brief Receive one byte using I2C
 * @param GPIOx
 * @param SCL_Pin
 * @param SDA_Pin
 * @param ACK
 * @retval Byte or ACK
 */
uint8_t SI2C_ReceiveByte(GPIO_TypeDef *GPIOx, uint16_t SCL_Pin, uint16_t SDA_Pin, GPIO_PinState ACK)
{
	uint8_t byte = 0x00;
	for (uint8_t i = 0; i < 8; i++)
	{
		HAL_GPIO_WritePin(GPIOx, SCL_Pin, GPIO_PIN_SET);
		SI2C_Delay();
		if (HAL_GPIO_ReadPin(GPIOx, SDA_Pin) == 1)
		{
			byte |= (0x80 >> i);
		}
		SI2C_Delay();
		HAL_GPIO_WritePin(GPIOx, SCL_Pin, GPIO_PIN_RESET);
		SI2C_Delay();
	}
	// transmit ACK
	HAL_GPIO_WritePin(GPIOx, SDA_Pin, ACK);
	SI2C_Delay();
	HAL_GPIO_WritePin(GPIOx, SCL_Pin, GPIO_PIN_SET);
	SI2C_Delay();
	HAL_GPIO_WritePin(GPIOx, SCL_Pin, GPIO_PIN_RESET);
	// release SDA
	HAL_GPIO_WritePin(GPIOx, SDA_Pin, GPIO_PIN_SET);
	SI2C_Delay();
	return byte;
}
