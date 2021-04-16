#if COMPONENT_MEM25
#include "mem25_demo.h"
#if MEM25_USE_DEMO_COMMANDS


// Read status
void Mem25_CmdStatus(uint8_t argc, uint8_t * argv[]) {
	uint8_t Status;
	
	// If no argument given, then read status
	if(argc == 1) {
		Status = Mem25_StatusRead();
		Print("HEX: ");
		Print_Hex(Status);
		Print("\r\nBIN: ");
		Print_Bin(Status);
	}
	
	// If there is given an argument, then parse argument and write status
	else {
		if(Parse_Hex8(argv[1], &Status)) return;
		Mem25_StatusWrite(Status);
		Print_ResponseOK();
	}
}


// Write enable or disable
void Mem25_CmdWriteEnableDisable(uint8_t argc, uint8_t * argv[]) {
	
	if(argc == 1) {
		#if CONSOLE_USE_HELP
			Print("mem25-we [0/1]");
		#endif
		return;
	}
	
	switch(*argv[1]) {
		case '0':
			Mem25_WriteDisble();
			Print_ResponseOK();
			return;
		case '1':
			Mem25_WriteEnable();
			Print_ResponseOK();
			return;
		default:
			Parse_Debug(Parse_UnknownCommand, argv[1]);
			return;
	}
}


// Get ID
void Mem25_CmdGetID(uint8_t argc, uint8_t * argv[]) {
	Print_Hex(Mem25_GetID());
}


// Sleep
void Mem25_CmdSleep(uint8_t argc, uint8_t * argv[]) {
	Mem25_Sleep();
	Print_ResponseOK();
}

// Wake
void Mem25_CmdWake(uint8_t argc, uint8_t * argv[]) {
	Mem25_Wake();
	Print_ResponseOK();
}


// Read bytes from memory
void Mem25_CmdRead(uint8_t argc, uint8_t * argv[]) {
	
	if(argc == 1) {
		#if CONSOLE_USE_HELP
			Print("mem25-r adr[HEX16] len[DEC16]");
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
	Mem25_Read(Address, Buffer, Length);
	
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
void Mem25_CmdWrite(uint8_t argc, uint8_t * argv[]) {
	
	if(argc == 1) {
		#if CONSOLE_USE_HELP
			Print("mem25-w format[a/h] adr[HEX16] data[]");
		#endif
		return;
	}
	
	// Argument 2 - address
	uint16_t Address;
	if(Parse_Hex16(argv[2], &Address)) return;
	
	// Argument 3 - data to write in format apecified in argument 1
	uint8_t Buffer[128];
	uint8_t BufferLength;
	if(*argv[1] == 'a') {
		if(Parse_AsciiString(argv[3], Buffer, &BufferLength, sizeof(Buffer))) return;
	}
	else if(*argv[1] == 'h') {
		if(Parse_HexString(argv[3], Buffer, &BufferLength, sizeof(Buffer), 1)) return;
	}
	else {
		Parse_Debug(Parse_UnknownCommand, argv[1]);
		return;
	}
	
	Print("Lenght: ");
	Print_Dec(BufferLength);
	Print_NL();
	Mem25_Write(Address, Buffer, BufferLength);
	
	Print_ResponseOK();
}


// Dump fragment of memory
void Mem25_CmdDump(uint8_t argc, uint8_t * argv[]) {
	
	if(argc == 1) {
		#if CONSOLE_USE_HELP
			Print("mem25-dump adr[HEX16] len[DEC32]");
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
	MEM25_CHIP_SELECT;
	Spi_3(MEM25_READ, (Address & 0xFF00) >> 8, Address & 0x00FF);
	
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
		
		// Prins ASCII
		Print('\t');
		for(uint8_t h=0; h<=15; h++) {
			if((*(Buffer+h) >= ' ') && (*(Buffer+h) < 127)) {			// omit non-printable characters
				Uart_Write(*(Buffer+h));
			}
			else {
				Uart_Write(' ');
			}
		}
		
		// Increment pointers
		Address += 16;
		
		// Watchdog reset
		asm volatile("wdr");
	}
	
	// End of transmission
	MEM25_CHIP_DESELECT;
}


void Mem25_CmdChipErase(uint8_t argc, uint8_t * argv[]) {
	Mem25_ChipErase();
	Print_ResponseOK();
}


void Mem25_CmdTest(uint8_t argc, uint8_t * argv[]) {
	
	uint8_t Buffer[128];
	for(uint8_t i=0; i<sizeof(Buffer); i++) {
		Buffer[i] = i;
	}
	
	Mem25_Write(0x0000, Buffer, sizeof(Buffer));
	Mem25_Write(0x0100, Buffer, sizeof(Buffer));
	Mem25_ChipErase();
	memset(Buffer, 0, sizeof(Buffer));
	
	Mem25_Read(0x0000, Buffer, sizeof(Buffer));
	Print_HexString(Buffer, sizeof(Buffer), ' ', 16);
	Mem25_Read(0x0100, Buffer, sizeof(Buffer));
	Print_HexString(Buffer, sizeof(Buffer), ' ', 16);
	
}


#endif
#endif
