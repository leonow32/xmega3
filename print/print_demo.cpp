#if C_PRINT
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


#endif
#endif