#include "oled.h"
#include "oled_font.h"

// SSD1306 configuration
// The SSD1306 address already contains write/read bit
#define SSD1306_Slave_Address 0x78
#define SSD1306_Control_Command 0x00
#define SSD1306_Control_Data 0x40

/*************************************************************************************************/

/*SSD1306 hardware implement*/

void SSD1306_WriteCommand(uint8_t Command) {
	uint8_t data_buffer[2] = { SSD1306_Control_Command, Command };
	HAL_I2C_Master_Transmit(&hi2c1, SSD1306_Slave_Address, data_buffer, 2, 100);
}

void SSD1306_WriteData(uint8_t Data) {
	uint8_t data_buffer[2] = { SSD1306_Control_Data, Data };
	HAL_I2C_Master_Transmit(&hi2c1, SSD1306_Slave_Address, data_buffer, 2, 100);
}

/**
 * @brief  OLED sets cursor position
 * @param  Y With the upper left corner as the origin, downward direction coordinates, range: 0-7
 * @param  X With the upper left corner as the origin, the coordinates in the right direction, range 0-127
 * @retval None
 */
void OLED_SetCursor(uint8_t Y, uint8_t X) {
	SSD1306_WriteCommand(0xB0 | Y);						// Set Y position
	SSD1306_WriteCommand(0x10 | ((X & 0xF0) >> 4));	// Set X position 4 bits higher
	SSD1306_WriteCommand(SSD1306_Control_Command | (X & 0x0F)); // Set X position 4 bits lower
}

/**
 * @brief  OLED clear screen
 * @param  None
 * @retval None
 */
void OLED_Clear(void) {
	uint8_t i, j;
	for (j = 0; j < 8; j++) {
		OLED_SetCursor(j, 0);
		for (i = 0; i < 128; i++) {
			SSD1306_WriteData(SSD1306_Control_Command);
		}
	}
}

/**
 * @brief  OLED displays a character
 * @param  Line Line position, value range 1-4
 * @param  Column Column position, value range 1-16
 * @param  Char A character to display, range: ASCII characters
 * @retval None
 */
void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char) {
	uint8_t i;
	OLED_SetCursor((Line - 1) * 2, (Column - 1) * 8); // Set the cursor position in the top half
	for (i = 0; i < 8; i++) {
		SSD1306_WriteData(Font8x16[Char - ' '][i]); // Displays the top half of the content
	}
	OLED_SetCursor((Line - 1) * 2 + 1, (Column - 1) * 8); // Set the cursor position in the bottom half
	for (i = 0; i < 8; i++) {
		SSD1306_WriteData(Font8x16[Char - ' '][i + 8]); // Displays the bottom half of the content
	}
}

/**
 * @brief  OLED display string
 * @param  Line Line position, value range 1-4
 * @param  Column Column position, value range 1-16
 * @param  String String to display, range: ASCII characters
 * @retval None
 */
void OLED_ShowString(uint8_t Line, uint8_t Column, char *String) {
	uint8_t i;
	for (i = 0; String[i] != '\0'; i++) {
		OLED_ShowChar(Line, Column + i, String[i]);
	}
}

/**
 * @brief  OLED power function
 * @retval The return value is equal to X to the Y power
 */
uint32_t OLED_Pow(uint32_t X, uint32_t Y) {
	uint32_t Result = 1;
	while (Y--) {
		Result *= X;
	}
	return Result;
}

/**
 * @brief  OLED display numbers (decimal, positive)
 * @param  Line Line position, range 1-4
 * @param  Column Column position, range 1-16
 * @param  Number The number to display
 * @param  Length To display the length of the number, the value ranges from 1 to 10
 * @retval None
 */
void OLED_ShowNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length) {
	uint8_t i;
	for (i = 0; i < Length; i++) {
		OLED_ShowChar(Line, Column + i,
				Number / OLED_Pow(10, Length - i - 1) % 10 + '0');
	}
}

/**
 * @brief  OLED display number (decimal, signed number)
 * @param  Line Line position, range 1-4
 * @param  Column Column position, range 1-16
 * @param  Number The number to display
 * @param  Length To display the length of the number, the value ranges from 1 to 10
 * @retval None
 */
void OLED_ShowSignedNum(uint8_t Line, uint8_t Column, int32_t Number,
		uint8_t Length) {
	uint8_t i;
	uint32_t Number1;
	if (Number >= 0) {
		OLED_ShowChar(Line, Column, '+');
		Number1 = Number;
	} else {
		OLED_ShowChar(Line, Column, '-');
		Number1 = -Number;
	}
	for (i = 0; i < Length; i++) {
		OLED_ShowChar(Line, Column + i + 1,
				Number1 / OLED_Pow(10, Length - i - 1) % 10 + '0');
	}
}

/**
 * @brief  OLED display numbers (hexadecimal, positive)
 * @param  Line Line position, range 1-4
 * @param  Column Column position, range 1-16
 * @param  Number The number to display， value range：0-0xFFFFFFFF
 * @param  Length To display the number length, the value ranges from 1 to 8
 * @retval None
 */
void OLED_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number,
		uint8_t Length) {
	uint8_t i, SingleNumber;
	for (i = 0; i < Length; i++) {
		SingleNumber = Number / OLED_Pow(16, Length - i - 1) % 16;
		if (SingleNumber < 10) {
			OLED_ShowChar(Line, Column + i, SingleNumber + '0');
		} else {
			OLED_ShowChar(Line, Column + i, SingleNumber - 10 + 'A');
		}
	}
}

/**
 * @brief  OLED display numbers (binary, positive)
 * @param  Line Line position, range 1-4
 * @param  Column Column position, range 1-16
 * @param  Number The number to display，value range ：0-1111 1111 1111 1111
 * @param  Length To display the number length, the value ranges from 1 to 16
 * @retval None
 */
void OLED_ShowBinNum(uint8_t Line, uint8_t Column, uint32_t Number,
		uint8_t Length) {
	uint8_t i;
	for (i = 0; i < Length; i++) {
		OLED_ShowChar(Line, Column + i,
				Number / OLED_Pow(2, Length - i - 1) % 2 + '0');
	}
}

/**
 * @brief  Initializes the OLED
 * @param  None
 * @retval None
 */
void OLED_Init(void) {
	// software configuration from SSD1306 Application Note
	SSD1306_WriteCommand(0xA8); // Set MUX Ratio
	SSD1306_WriteCommand(0x3F);

	SSD1306_WriteCommand(0xD3); // Set Display Offset
	SSD1306_WriteCommand(0x00);

	SSD1306_WriteCommand(0x40); // Set Display Start Line

	SSD1306_WriteCommand(0xA1); // Set Segment re-map

	SSD1306_WriteCommand(0xC8); // Set COM Output Scan Direction

	SSD1306_WriteCommand(0xDA); // Set COM Pins hardware configuration
	SSD1306_WriteCommand(0x12);

	SSD1306_WriteCommand(0x81); // Set Contrast Control
	SSD1306_WriteCommand(0xCF);

	SSD1306_WriteCommand(0xA4); // Disable Entire Display On

	SSD1306_WriteCommand(0xA6); // Set Normal Display

	SSD1306_WriteCommand(0xD5); // Set Osc Frequency
	SSD1306_WriteCommand(0x80);

	SSD1306_WriteCommand(0x8D); // Enable charge pump regulator
	SSD1306_WriteCommand(0x14);

	SSD1306_WriteCommand(0xAF); // Display On AFh

	OLED_Clear(); // OLED Clear
}
