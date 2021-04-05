#if C_SPI_MASTER
#include "spi_master_demo.h"
#if SPI_MASTER_USE_DEMO_COMMANDS


// Transmit bytes
// Arguments:
// 1) Data to send
// 2) Number of bytes to read after data is sent
// 3) Dummy byte to be send during data reading
// Examplse of use:
//  - spi 11
//    Send bytes 11 and print 1 byte which was read during transmission
//  - spi 112233
//    Send bytes 112233 and print 3 bytes which were read during transmission
//  - spi 112233 2
//    Send bytes 1122330000 and print 5 bytes which were read during transmission
//  - spi 112233 2 FF
//    Send bytes 112233FFFF and print 5 bytes which were read during transmission
void Spi_CmdStream(uint8_t argc, uint8_t * argv[]) {
	
	if(argc == 1) {
		#if CONSOLE_USE_HELP
			Print("spi data[HEX] readcnt[DEC8] dummy[HEX8]");
		#endif
		return;
	}
	
	// Argument 1 - data to send
	uint8_t Buffer[128];
	uint8_t BufferLength;
	if(Parse_HexString(argv[1], Buffer, &BufferLength, sizeof(Buffer))) return;
	
	// Argument 2 (optional) - number of bytes to read after sending data from argument 1
	uint8_t ReadCount;
	if(argc >= 3) {
		if(Parse_Dec8(argv[2], &ReadCount)) return;
	}
	else {
		ReadCount = 0;
	}
	
	// Argument 3 (optional) - dummy byte that has to be send during read operation if argument 2 is >0. If argument 3 is not given, then 00 will be send
	uint8_t DummyByte;
	if(argc >= 4) {
		if(Parse_Hex8(argv[3], &DummyByte)) return;
	}
	else {
		DummyByte = 0x00;
	}
	
	// Print data to send
	Print_Format(ForegroundWhiteBright);
	Print("SPI Tx[");
	Print_Dec(BufferLength + ReadCount);
	Print("]: ");
	Print_Format(FormatReset);
	Print_HexString(Buffer, BufferLength, ' ');
	for(uint8_t i=0; i<ReadCount; i++) {
		Print_Hex(DummyByte, ' ');
	}
	Print_NL();
	
	// Execute command
	SPI_DEMO_CHIP_SELECT;
	Spi_Transmit(Buffer, Buffer, BufferLength);
	Spi_Read(Buffer+BufferLength, ReadCount, DummyByte);
	SPI_DEMO_CHIP_DESELECT;
	
	// Print result
	Print_Format(ForegroundWhiteBright);
	Print("SPI Rx[");
	Print_Dec(BufferLength + ReadCount);
	Print("]: ");
	Print_Format(FormatReset);
	Print_HexString(Buffer, BufferLength + ReadCount, ' ');
}

#endif
#endif
