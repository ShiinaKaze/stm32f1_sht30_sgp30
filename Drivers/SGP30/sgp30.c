#include "sgp30.h"

#define SGP30_ADDRESS 0x58
#define SGP30_ACK 0
#define SGP30_NACK 1
/* SGP30 I2C config */
#define SGP30_GPIOx GPIOB
#define SGP30_SCL GPIO_PIN_10
#define SGP30_SDA GPIO_PIN_11

/* SGP30 software I2C interface implement */
#define SI2C_Start() SI2C_Start(SGP30_GPIOx, SGP30_SCL, SGP30_SDA)
#define SI2C_Stop() SI2C_Stop(SGP30_GPIOx, SGP30_SCL, SGP30_SDA)
#define SI2C_TransmitByte(BYTE) SI2C_TransmitByte(SGP30_GPIOx, SGP30_SCL, SGP30_SDA, BYTE)
#define SI2C_ReceiveByte(ACK) SI2C_ReceiveByte(SGP30_GPIOx, SGP30_SCL, SGP30_SDA, ACK)

void SGP30_SInit(void) {
	SGP30_SWriteCommand(0x20, 0x03);
}

uint8_t SGP30_SWriteCommand(uint8_t CMD_MSB, uint8_t CMD_LSB) {
	uint8_t ack;
	SI2C_Start();
	SI2C_TransmitByte(SGP30_ADDRESS << 1 | 0x00);
	SI2C_TransmitByte(CMD_MSB);
	ack = SI2C_TransmitByte(CMD_LSB);
	SI2C_Stop();
	return ack;
}

void SGP30_SReadData(SGP30 *sgp30, uint8_t CMD_MSB, uint8_t CMD_LSB) {
	uint16_t timeout = 1000;
	SI2C_Start();
	if ( SI2C_TransmitByte(SGP30_ADDRESS << 1 | 0x00) != SGP30_ACK) {
		return;
	}
	SI2C_TransmitByte(CMD_MSB);
	SI2C_TransmitByte(CMD_LSB);

	// i2c read header, if get nack, retry send
	SI2C_Start();
	while (SI2C_TransmitByte((SGP30_ADDRESS << 1) | 0x01)) {
		SI2C_Start();
		timeout--;
		if (timeout == 0) {
			break;
		}
	}
	sgp30->co2eq = SI2C_ReceiveByte(GPIO_PIN_RESET) << 8;
	sgp30->co2eq = sgp30->co2eq | SI2C_ReceiveByte(GPIO_PIN_RESET);
	sgp30->co2eq_crc = SI2C_ReceiveByte(GPIO_PIN_RESET);
	sgp30->tvoc = SI2C_ReceiveByte(GPIO_PIN_RESET) << 8;
	sgp30->tvoc = sgp30->tvoc | SI2C_ReceiveByte(GPIO_PIN_RESET);
	sgp30->tvoc_crc = SI2C_ReceiveByte(GPIO_PIN_SET);
	SI2C_Stop();
}

void SGP30_SWriteData(uint8_t CMD_MSB, uint8_t CMD_LSB, uint8_t Data_MSB,
		uint8_t Data_LSB, uint8_t Data_CRC) {
	SI2C_Start();
	SI2C_TransmitByte(SGP30_ADDRESS << 1 | 0x00);
	SI2C_TransmitByte(CMD_MSB);
	SI2C_TransmitByte(CMD_LSB);
	SI2C_TransmitByte(Data_MSB);
	SI2C_TransmitByte(Data_LSB);
	SI2C_TransmitByte(Data_CRC);
	SI2C_Stop();
}

void SGP30_Init(void) {
	SGP30_WriteCommand(0x20, 0x03);
}

void SGP30_WriteCommand(uint8_t CMD_MSB, uint8_t CMD_LSB) {
	uint8_t data_buffer[2] = { CMD_MSB, CMD_LSB };
	HAL_I2C_Master_Transmit(&hi2c2, SGP30_ADDRESS << 1, data_buffer, 2, 1000);
}

void SGP30_ReadData(SGP30 *sgp30, uint8_t CMD_MSB, uint8_t CMD_LSB) {
	uint8_t data_buffer[6] = { CMD_MSB, CMD_LSB };
	HAL_I2C_Master_Transmit(&hi2c2, SGP30_ADDRESS << 1, data_buffer, 2, 1000);
	// Measurement duration is typically 10ms
	Delay_ms(10);
	if (HAL_I2C_Master_Receive(&hi2c2, (SGP30_ADDRESS << 1) | 0x01,
			data_buffer, 6, 1000) != HAL_OK) {
			return;
	}
	sgp30->co2eq = data_buffer[0] << 8;
	sgp30->co2eq = sgp30->co2eq | data_buffer[1];
	sgp30->co2eq_crc = data_buffer[2];
	sgp30->tvoc = data_buffer[3] << 8;
	sgp30->tvoc = sgp30->tvoc | data_buffer[4];
	sgp30->tvoc_crc = data_buffer[5];
	Delay_s(1);
}
