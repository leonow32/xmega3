#if COMPONENT_PRINT
#include "print_demo.h"
#if PRINT_USE_DEMO_COMMANDS


// Change console text color
void Print_CmdColor(uint8_t argc, uint8_t * argv[]) {
	uint8_t ColorCode;
	if(Parse_Dec8(argv[1], &ColorCode)) return;
	Print_Format(PrintFormat_t(ColorCode));
	Print("Test");
}


// Show all ASCII codes
void Print_CmdAscii(uint8_t argc, uint8_t * argv[]) {
	
	// Print header
	Print_Format(ForegroundWhiteBright);
	Print("\t");
	for(uint8_t i='0'; i<='F'; i++) {
		Print(i);
		Print(' ');
		if(i == '9') {
			i = 'A' - 1;
		}
	}
	Print_Format(FormatReset);
	
	for(uint16_t Character = 16; Character < 256; Character++) {
		if(Character % 16 == 0) {
			Print_Format(ForegroundWhiteBright);
			Print_NL();
			Print_Hex(uint8_t(Character));
			Print('\t');
			Print_Format(FormatReset);
		}
		
		Print(uint8_t(Character));
		Print(' ');
	}
}


// Dump fragment of memory
void Print_CmdDump(uint8_t argc, uint8_t * argv[]) {
	
	if(argc == 1) {
		#if CONSOLE_USE_HELP
			Print("dump adr[HEX16] len[DEC16]");
		#endif
		return;
	}
	
	// Argument 1 - Address
	uint16_t Address;
	if(Parse_Hex16(argv[1], &Address)) return;
	
	// Argument 2 - Length
	uint32_t Length;
	if(Parse_Dec32(argv[2], &Length)) return;
	if(Length == 0) {
		Parse_Debug(Parse_Underflow, argv[2]);
		return;
	}
	
	// Execute command
	Print_Dump((uint8_t *)Address, Length);
}


// Convect time_t to  human readable time
void Print_CmdTimet(uint8_t argc, uint8_t * argv[]) {
	
	if(argc == 1) {
		#if CONSOLE_USE_HELP
			Print("timet [DEC32]");
		#endif
		return;
	}
	
	// Argument 1 - time as a number of seconds since 2000.01.01 00:00:00
	uint32_t Time;
	if(Parse_Dec32(argv[1], &Time)) return;
	
	// Execute command
	Print_Time(time_t(Time));
}


// Convect time_t to  human readable time
void Print_CmdTimes(uint8_t argc, uint8_t * argv[]) {
	
	if(argc == 1) {
		#if CONSOLE_USE_HELP
			Print("xxxx");
		#endif
		return;
	}
	
	// Argument 1 - time as a number of seconds since 2000.01.01 00:00:00
	time_t Time;
	if(Parse_Time(argv[1], &Time)) return;
	
	// Execute command
	Print_Time(Time);
	Print_NL();
	Print_Dec(uint32_t(Time));
}


#endif
#endif