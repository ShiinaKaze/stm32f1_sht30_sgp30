#include "sht30.h"
#include "systick.h"
#include "sw_i2c.h"

/* SHT30 config */
#define SHT30_ADDRESS 0x44
#define SHT30_CLOCK_STRETCHING_ENABLE 0x2C

/*SHT30 use software I2C*/
void SHT30_Init(void)
{
    Delay_ms(1);
}

uint8_t SHT30_WriteCommand(uint8_t CMD_MSB, uint8_t CMD_LSB)
{
    uint8_t ack;
    SW_I2C_Start();
    SW_I2C_TransmitByte(SHT30_ADDRESS << 1 | 0x00);
    SW_I2C_TransmitByte(CMD_MSB);
    ack = SW_I2C_TransmitByte(CMD_LSB);
    SW_I2C_Stop();
    return ack;
}

void SHT30_Measure_Periodic_Mode(SHT30_TypeDef *sht30)
{
    SHT30_WriteCommand(0xE0, 0x00);

    SW_I2C_Start();
    if (SW_I2C_TransmitByte((SHT30_ADDRESS << 1) | 0x01) == SW_I2C_None_ACK)
    {
        sht30->temp_raw = 0;
        sht30->temp_crc = 0;
        sht30->hum_raw = 0;
        sht30->hum_crc = 0;
        sht30->temp = 0.0;
        sht30->hum = 0.0;
        return;
    }
    sht30->temp_raw = SW_I2C_ReceiveByte(0) << 8;
    sht30->temp_raw = sht30->temp_raw | SW_I2C_ReceiveByte(0);
    sht30->temp_crc = SW_I2C_ReceiveByte(0);
    sht30->hum_raw = SW_I2C_ReceiveByte(0) << 8;
    sht30->hum_raw = sht30->hum_raw | SW_I2C_ReceiveByte(0);
    sht30->hum_crc = SW_I2C_ReceiveByte(1);
    SW_I2C_Stop();

    sht30->temp = (-45.0 + (175.0 * (float)sht30->temp_raw / 65535.0));
    sht30->hum = (100.0 * (float)sht30->hum_raw / 65535.0);
}

void SHT30_Set_Periodic_Data_Acquisition_Mode(uint8_t CMD_MSB, uint8_t CMD_LSB)
{
    SHT30_WriteCommand(CMD_MSB, CMD_LSB);
}
