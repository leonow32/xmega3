#if COMPONENT_MEM23
#include "mem23_demo.h"
#if MEM23_USE_DEMO_COMMANDS


// Read status
void Mem23_CmdStatus(uint8_t argc, uint8_t * argv[]) {
	uint8_t Status;
	
	// If no argument given, then read status
	if(argc == 1) {
		Status = Mem23_StatusRead();
		Print("HEX: ");
		Print_Hex(Status);
		Print("\r\nBIN: ");
		Print_Bin(Status);
	}
	
	// If there is given an argument, then parse argument and write status
	else {
		if(Parse_Hex8(argv[1], &Status)) return;
		Mem23_StatusWrite(Status);
		Print_ResponseOK();
	}
}


// Read bytes from memory
void Mem23_CmdRead(uint8_t argc, uint8_t * argv[]) {
	
	if(argc == 1) {
		#if CONSOLE_USE_HELP
			Print("mem23-r adr[HEX16] len[DEC16]");
		#endif
		return;
	}
	
	uint8_t Buffer[257];
	memset(Buffer, 0, sizeof(Buffer));
	
	// Argument 1 - address
	uint16_t Address;
	if(Parse_Hex16(argv[1], &Address)) return;
	
	// Argument 2 - length
	uint16_t Length;
	if(Parse_Dec16(argv[2], &Length, sizeof(Buffer)-1)) return;
	
	// Argument 3 optional - display format
	uint8_t DisplayFormat;
	if(argc == 4) {
		Parse_AsciiCharacter(argv[3], &DisplayFormat);
	}
	else {
		DisplayFormat = 0;
	}
	
	// Execute command
	Mem23_Read(Address, Buffer, Length);
	
	// Display result
	switch(DisplayFormat) {
		case 'a':
			Print((const char *)Buffer);
			break;
		case 'h':
			Print_HexString(Buffer, Length, ' ', 16);
			break;
		default:
			Print_HexString(Buffer, Length, ' ', 16);
			Print_NL();
			Print((const char *)Buffer);
	}
}


// Write data to memory in ASCII or HEX format
void Mem23_CmdWrite(uint8_t argc, uint8_t * argv[]) {
	
	if(argc == 1) {
		#if CONSOLE_USE_HELP
			Print("mem23-w adr[HEX16] data[] format[a/h]");
		#endif
		return;
	}
	
	// Argument 3 - input type Ascii or Hex
	Parse_t (*ParserPointer)(const uint8_t * InputString, uint8_t * OutputString, uint8_t * OutputLength, const uint8_t MaxLength, const uint8_t MinLength);
	if(argv[3] && *argv[3] == 'h') {
		ParserPointer = Parse_HexString;
	}
	else {
		ParserPointer = Parse_AsciiString;
	}
	
	// Argument 1 - address
	uint16_t Address;
	if(Parse_Hex16(argv[1], &Address)) return;
	
	// Argument 2 - data to write in format apecified in argument 1
	uint8_t Buffer[128];
	uint8_t BufferLength;
	if(ParserPointer(argv[2], Buffer, &BufferLength, sizeof(Buffer), 1)) return;
	
	Print("Lenght: ");
	Print_Dec(BufferLength);
	Print_NL();
	Mem23_Write(Address, Buffer, BufferLength);
	
	Print_ResponseOK();
}


// Dump fragment of memory
void Mem23_CmdDump(uint8_t argc, uint8_t * argv[]) {
	
	if(argc == 1) {
		#if CONSOLE_USE_HELP
			Print("mem23-dump adr[HEX16] len[DEC32]");
		#endif
		return;
	}
	
	// Argument 1 - Address
	uint16_t Address;
	if(Parse_Hex16(argv[1], &Address)) return;
	Address = Address & 0xFFF0;
	
	// Argument 2 - Length
	uint32_t Length;
	if(Parse_Dec32(argv[2], &Length)) return;
	if(Length == 0) {
		Parse_Debug(Parse_Underflow, argv[2]);
		return;
	}
	
	// Start of transmission
	MEM23_CHIP_SELECT;
	Spi_3(MEM23_READ, (Address & 0xFF00) >> 8, Address & 0x00FF);
	
	// Print header
	Print_Format(ForegroundWhiteBright);
	Print("\t");
	for(uint8_t i='0'; i<='F'; i++) {
		Print(' ');
		Print(i);
		Print(' ');
		if(i == '9') {
			i = 'A' - 1;
		}
	}
	Print_Format(FormatReset);
	
	// Loop for 16 bytes
	uint8_t Buffer[16];
	uint16_t Loops = Length / sizeof(Buffer);
	if(Length & 0x0F) {
		Loops++;
	}
	
	while(Loops--) {
		
		// Read 16 bytes
		Spi_Read(Buffer, sizeof(Buffer));
		
		// New line
		Print_NL();
		
		// Print address
		Print_Format(ForegroundWhiteBright);
		Print_Hex(Address);
		Print_Format(FormatReset);
		
		// Print HEX
		Print('\t');
		for(uint8_t h=0; h<=15; h++) {
			Print_Hex(*(Buffer+h), ' ');
		}
		
		// Print ASCII
		Print('\t');
		for(uint8_t h=0; h<=15; h++) {
			if((*(Buffer+h) >= ' ') && (*(Buffer+h) < 127)) {			// omit non-printable characters
				Print(*(Buffer+h));
			}
			else {
				Print(' ');
			}
		}
		
		// Increment pointers
		Address += 16;
		
		// Watchdog reset
		asm volatile("wdr");
	}
	
	// End of transmission
	MEM23_CHIP_DESELECT;
}


#endif
#endif
