#if C_SPI_MASTER
#include "spi_master_demo.h"
#if SPI_MASTER_USE_DEMO_COMMANDS


// Transmit 1 byte
void Spi_CmdTransmit1(uint8_t argc, uint8_t * argv[]) {
	
	if(argc == 1) {
		#if CONSOLE_USE_HELP
			Print("spi1 data[HEX8]");
		#endif
		return;
	}
	
	// Argument 1
	uint8_t Byte1;
	if(Parse_Hex8(argv[1], &Byte1)) return;
	
	// Execute command
	uint8_t Read;
	SPI_DEMO_CHIP_SELECT;
	Read = Spi_1(Byte1);
	SPI_DEMO_CHIP_DESELECT;
	Print_Hex(Read);
}


// Transmit bytes
void Spi_CmdStream(uint8_t argc, uint8_t * argv[]) {
	
	if(argc == 1) {
		#if CONSOLE_USE_HELP
		Print("spi ");
		#endif
		return;
	}
	
	// Argument 1
	uint8_t Buffer[128];
	uint8_t BufferLength;
	if(Parse_HexString(argv[1], Buffer, &BufferLength, sizeof(Buffer))) return;
	
	Print_Format(ForegroundWhiteBright);
	Print("Send[");
	Print_Dec(BufferLength);
	Print("]: ");
	Print_Format(FormatReset);
	Print_HexString(Buffer, BufferLength, ' ');
	Print_NL();
	
	// Execute command
	SPI_DEMO_CHIP_SELECT;
	Spi_Transmit(Buffer, Buffer, BufferLength);
	SPI_DEMO_CHIP_DESELECT;
	
	Print_Format(ForegroundWhiteBright);
	Print("Read[");
	Print_Dec(BufferLength);
	Print("]: ");
	Print_Format(FormatReset);
	Print_HexString(Buffer, BufferLength, ' ');
}

#endif
#endif
