#include "sht30.h"

/* SHT30 config */
#define SHT30_ADDRESS 0x44
#define SHT30_ACK 0
#define SHT30_NACK 1

/* SHT30 I2C config */
#define SHT30_GPIOx GPIOB
#define SHT30_SCL GPIO_PIN_10
#define SHT30_SDA GPIO_PIN_11

/* SHT30 software I2C interface implement */
#define SI2C_Start() SI2C_Start(SHT30_GPIOx, SHT30_SCL, SHT30_SDA)
#define SI2C_Stop() SI2C_Stop(SHT30_GPIOx, SHT30_SCL, SHT30_SDA)
#define SI2C_TransmitByte(BYTE) SI2C_TransmitByte(SHT30_GPIOx, SHT30_SCL, SHT30_SDA, BYTE)
#define SI2C_ReceiveByte(ACK) SI2C_ReceiveByte(SHT30_GPIOx, SHT30_SCL, SHT30_SDA, ACK)

/*SHT30 use software I2C*/
void SHT30_SInit(void) {
	SHT30_SWriteCommand(0x21, 0x30);
}

uint8_t SHT30_SWriteCommand(uint8_t CMD_MSB, uint8_t CMD_LSB) {
	uint8_t ack;
	SI2C_Start();
	SI2C_TransmitByte(SHT30_ADDRESS << 1 | 0x00);
	SI2C_TransmitByte(CMD_MSB);
	ack = SI2C_TransmitByte(CMD_LSB);
	SI2C_Stop();
	return ack;
}

void SHT30_SReadData(SHT30 *sht30, uint8_t CMD_MSB, uint8_t CMD_LSB) {
	SHT30_SWriteCommand(CMD_MSB, CMD_LSB);

	SI2C_Start();
	if (SI2C_TransmitByte((SHT30_ADDRESS << 1) | 0x01) != SHT30_ACK) {
		return;
	}
	sht30->temp_raw = SI2C_ReceiveByte(GPIO_PIN_RESET) << 8;
	sht30->temp_raw = sht30->temp_raw | SI2C_ReceiveByte(GPIO_PIN_RESET);
	sht30->temp_crc = SI2C_ReceiveByte(GPIO_PIN_RESET);
	sht30->hum_raw = SI2C_ReceiveByte(GPIO_PIN_RESET) << 8;
	sht30->hum_raw = sht30->hum_raw | SI2C_ReceiveByte(GPIO_PIN_RESET);
	sht30->hum_crc = SI2C_ReceiveByte(GPIO_PIN_SET);
	SI2C_Stop();

	sht30->temp = (-45.0 + (175.0 * (float) sht30->temp_raw / 65535.0));
	sht30->hum = (100.0 * (float) sht30->hum_raw / 65535.0);
}

/*SHT30 use hardware I2C*/
void SHT30_Init(void) {
	SHT30_WriteCommand(0x21, 0x30);
}

void SHT30_WriteCommand(uint8_t CMD_MSB, uint8_t CMD_LSB) {
	uint8_t data_buffer[2] = { CMD_MSB, CMD_LSB };
	HAL_I2C_Master_Transmit(&hi2c2, SHT30_ADDRESS << 1, data_buffer, 2, 1000);
}

void SHT30_ReadData(SHT30 *sht30, uint8_t CMD_MSB, uint8_t CMD_LSB,
		uint16_t Attempts) {
	uint8_t data_buffer[6] = { CMD_MSB, CMD_LSB };
	HAL_I2C_Master_Transmit(&hi2c2, SHT30_ADDRESS << 1, data_buffer, 2, 1000);
	while (HAL_I2C_Master_Receive(&hi2c2, (SHT30_ADDRESS << 1) | 0x01,
			data_buffer, 6, 1000) != HAL_OK) {
		Attempts--;
		if (Attempts == 0) {
			return;
		}
	}
	sht30->temp_raw = data_buffer[0] << 8;
	sht30->temp_raw = sht30->temp_raw | data_buffer[1];
	sht30->temp_crc = data_buffer[2];
	sht30->hum_raw = data_buffer[3] << 8;
	sht30->hum_raw = sht30->hum_raw | data_buffer[4];
	sht30->hum_crc = data_buffer[5];
	sht30->temp = (-45.0 + (175.0 * (float) sht30->temp_raw / 65535.0));
	sht30->hum = (100.0 * (float) sht30->hum_raw / 65535.0);
	Delay_s(1);
}
