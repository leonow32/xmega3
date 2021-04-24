#if COMPONENT_DS3231
#include "ds3231_demo.h"
#if DS3231_USE_DEMO_COMMANDS


// Debug errors
void DS3231_Debug(DS3231_t Result) {
	switch(Result) {
		case DS3231_OK:			Print_ResponseOK();			break;
		case DS3231_Error:		Print_ResponseError();		break;
	}
}


void DS3231_CmdRead(uint8_t argc, uint8_t * argv[]) {
	
	// Execute command
	uint8_t Buffer[7];
	I2C_Start(DS3231_ADDRESS_WRITE);
	I2C_Write(0x00);			// Register address
	I2C_Start(DS3231_ADDRESS_READ);
	for(uint8_t i = 0; i < sizeof(Buffer); i++) {
		Buffer[i] = I2C_Read();
	}
	I2C_Stop();
	
	Print("20");
	Print_Hex(Buffer[6]);
	Print('-');
	Print_Hex(Buffer[5]);
	Print('-');
	Print_Hex(Buffer[4]);
	Print(' ');
	Print_Hex(Buffer[2]);
	Print(':');
	Print_Hex(Buffer[1]);
	Print(':');
	Print_Hex(Buffer[0]);
}


void DS3231_CmdWrite(uint8_t argc, uint8_t * argv[]) {
	
	if(argc == 1) {
		#if CONSOLE_USE_HELP
			Print("ds3231-w YYMMDDhhmmss");
		#endif
		return;
	}
	
	// Argument 1 - Date and time
	uint8_t Buffer[6];
	uint8_t BufferLength;
	if(Parse_HexString(argv[1], Buffer, &BufferLength, sizeof(Buffer), sizeof(Buffer))) return;
	
	// Execute command
	I2C_Start(DS3231_ADDRESS_WRITE);
	I2C_Write(0x00);			// Register address
	I2C_Write(Buffer[5]);		// Seconds
	I2C_Write(Buffer[4]);		// Minutes
	I2C_Write(Buffer[3]);		// Hours
	I2C_Write(0x01);			// Weekday (not used)
	I2C_Write(Buffer[2]);		// Day
	I2C_Write(Buffer[1]);		// Month
	I2C_Write(Buffer[0]);		// Year
	I2C_Stop();
	
	Print_ResponseOK();
}


#endif
#endif
