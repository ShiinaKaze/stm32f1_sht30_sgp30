#include "sgp30.h"
#include "systick.h"
#include "sw_i2c.h"

#define SGP30_ADDRESS 0x58

void SGP30_Init(void)
{
    Delay_ms(1); // Wait until the sensor enters idle state
}

uint8_t SGP30_WriteCommand(uint8_t CMD_MSB, uint8_t CMD_LSB)
{
    uint8_t ack;
    SW_I2C_Start();
    SW_I2C_TransmitByte(SGP30_ADDRESS << 1 | 0x00);
    SW_I2C_TransmitByte(CMD_MSB);
    ack = SW_I2C_TransmitByte(CMD_LSB);
    SW_I2C_Stop();
    return ack;
}

void SGP30_Measure_IAQ(SGP30_TypeDef *sgp30)
{
    uint16_t timeout = 200;
    SW_I2C_Start();
    SW_I2C_TransmitByte(SGP30_ADDRESS << 1 | 0x00);
    SW_I2C_TransmitByte(0x20);
    SW_I2C_TransmitByte(0x08);

    // measurement duration is 10 ms
    // i2c read header, if get nack, retry send
    SW_I2C_Start();
    while (SW_I2C_TransmitByte((SGP30_ADDRESS << 1) | 0x01))
    {
        SW_I2C_Start();
        timeout--;
        if (timeout == 0)
        {
            sgp30->co2eq_raw = 0;
            sgp30->tvoc_raw = 0;
            sgp30->co2eq_crc = 0;
            sgp30->tvoc_crc = 0;
            sgp30->co2eq = 0;
            sgp30->tvoc = 0;
            return;
        }
    }
    sgp30->co2eq = SW_I2C_ReceiveByte(0) << 8;
    sgp30->co2eq = sgp30->co2eq | SW_I2C_ReceiveByte(0);
    sgp30->co2eq_crc = SW_I2C_ReceiveByte(0);
    sgp30->tvoc = SW_I2C_ReceiveByte(0) << 8;
    sgp30->tvoc = sgp30->tvoc | SW_I2C_ReceiveByte(0);
    sgp30->tvoc_crc = SW_I2C_ReceiveByte(1);
    SW_I2C_Stop();
}

void SGP30_WriteData(uint8_t CMD_MSB, uint8_t CMD_LSB, uint8_t Data_MSB, uint8_t Data_LSB, uint8_t Data_CRC)
{
    SW_I2C_Start();
    SW_I2C_TransmitByte(SGP30_ADDRESS << 1 | 0x00);
    SW_I2C_TransmitByte(CMD_MSB);
    SW_I2C_TransmitByte(CMD_LSB);
    SW_I2C_TransmitByte(Data_MSB);
    SW_I2C_TransmitByte(Data_LSB);
    SW_I2C_TransmitByte(Data_CRC);
    SW_I2C_Stop();
}

void SGP30_IAQ_Init(void)
{
    SGP30_WriteCommand(0x20, 0x03);
}
