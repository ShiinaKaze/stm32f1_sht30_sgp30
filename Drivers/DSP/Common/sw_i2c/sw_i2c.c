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

#include "sw_i2c.h"

#define SI2C_Delay() Delay_us(3)

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

/**
 * @file sw_i2c.c
 * @author ShiinaKaze (shiinakaze@qq.com)
 * @brief Software I2C interface
 * @version 0.1
 * @date 2024-05-31
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "main.h"
#include "sw_i2c.h"
#include "systick.h"

#define SW_I2C_Delay() Delay_us(5)
#define SW_I2C_SCL_WriteBit(BitVal) HAL_GPIO_WritePin(SW_I2C_GPIOx, SW_I2C_SCL_PIN, (GPIO_PinState)BitVal)
#define SW_I2C_SDA_WriteBit(BitVal) HAL_GPIO_WritePin(SW_I2C_GPIOx, SW_I2C_SDA_PIN, (GPIO_PinState)BitVal)
#define SW_I2C_SDA_ReadBit() HAL_GPIO_ReadPin(SW_I2C_GPIOx, SW_I2C_SDA_PIN)

/**
 * @brief I2C start condition
 * @param None
 * @retval None
 */
void SW_I2C_Start(void)
{
	// pull up SCL,SDA for start
	SW_I2C_SDA_WriteBit(1);
	SW_I2C_SCL_WriteBit(1);
	SW_I2C_Delay();

	// I2C start
	SW_I2C_SDA_WriteBit(0);
	SW_I2C_Delay();
	SW_I2C_SCL_WriteBit(0);
	SW_I2C_Delay();
}

/**
 * @brief  I2C stop condition
 * @param none
 * @retval None
 */
void SW_I2C_Stop(void)
{
	// pull down SDA for stop
	SW_I2C_SDA_WriteBit(0);
	SW_I2C_Delay();

	// I2C stop
	SW_I2C_SCL_WriteBit(1);
	SW_I2C_Delay();
	SW_I2C_SDA_WriteBit(1);
	SW_I2C_Delay();
}

/**
 * @brief Transmit one byte using I2C
 * @param Byte
 * @retval ACK
 */
uint8_t SW_I2C_TransmitByte(uint8_t Byte)
{
	uint8_t ack = 1;
	for (uint8_t i = 0; i < 8; i++)
	{
		SW_I2C_SDA_WriteBit((Byte & (0x80 >> i)));
		SW_I2C_Delay();
		SW_I2C_SCL_WriteBit(1);
		SW_I2C_Delay();
		SW_I2C_SCL_WriteBit(0);
		if (i == 7)
		{
			// release SDA
			SW_I2C_SDA_WriteBit(1);
		}
		SW_I2C_Delay();
	}
	// receive ACK
	SW_I2C_Delay();
	SW_I2C_SCL_WriteBit(1);
	ack = SW_I2C_SDA_ReadBit();
	SW_I2C_Delay();
	SW_I2C_SCL_WriteBit(0);
	SW_I2C_Delay();
	return ack;
}

/**
 * @brief Receive one byte using I2C
 * @param ACK
 * @retval Byte or ACK
 */
uint8_t SW_I2C_ReceiveByte(uint8_t ACK)
{
	uint8_t byte = 0x00;
	for (uint8_t i = 0; i < 8; i++)
	{
		SW_I2C_Delay();
		SW_I2C_SCL_WriteBit(1);
		if (SW_I2C_SDA_ReadBit() == 1)
		{
			byte |= (0x80 >> i);
		}
		SW_I2C_Delay();
		SW_I2C_SCL_WriteBit(0);
		SW_I2C_Delay();
	}
	// transmit ACK
	SW_I2C_SDA_WriteBit(ACK);
	SW_I2C_Delay();
	SW_I2C_SCL_WriteBit(1);
	SW_I2C_Delay();
	SW_I2C_SCL_WriteBit(0);
	// release SDA
	SW_I2C_SDA_WriteBit(1);
	SW_I2C_Delay();
	return byte;
}

