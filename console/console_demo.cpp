#if COMPONENT_CONSOLE
#include "console_demo.h"

#if CONSOLE_USE_DEMO_COMMANDS

// Print all provided arguments
void Console_CmdArgs(uint8_t argc, uint8_t * argv[]) {
	Print("argc = ");
	Print_Dec(argc);
	for(uint8_t i=0; i<CONSOLE_MAX_ARGUMENTS; i++) {
		Print_NL();
		Print_Dec(i);
		Print(":\t");
		Print_Hex((uint16_t)argv[i]);
		if(argv[i]) {
			Print('\t');
			Print((const char *)argv[i]);
		}
	}
}


// Print first argument
void Console_CmdEcho(uint8_t argc, uint8_t * argv[]) {
	if(argc != 1) {
		Print((const char *)argv[1]);
	}
}


// 
void Console_CmdHex8(uint8_t argc, uint8_t * argv[]) {
	uint8_t Value;
	if(Parse_Hex8(argv[1], &Value)) return;
	Print_Dec(Value);
}


void Console_CmdHex16(uint8_t argc, uint8_t * argv[]) {
	uint16_t Value;
	if(Parse_Hex16(argv[1], &Value)) return;
	Print_Dec(Value);
}


void Console_CmdHex32(uint8_t argc, uint8_t * argv[]) {
	uint32_t Value;
	if(Parse_Hex32(argv[1], &Value)) return;
	Print_Dec(Value);
}


void Console_CmdDec8(uint8_t argc, uint8_t * argv[]) {
	uint8_t Value = 0;
	if(Parse_Dec8(argv[1], &Value, 100)) return;
	Print_Dec(Value);
}


void Console_CmdDec16(uint8_t argc, uint8_t * argv[]) {
	uint16_t Value = 0;
	if(Parse_Dec16(argv[1], &Value, 10000)) return;
	Print_Dec(Value);
}


void Console_CmdDec32(uint8_t argc, uint8_t * argv[]) {
	uint32_t Value = 0;
	if(Parse_Dec32(argv[1], &Value, 1000000)) return;
	Print_Dec(Value);
}


void Console_CmdHexString(uint8_t argc, uint8_t * argv[]) {
	uint8_t Buffer[64];
	uint8_t Length;
	if(Parse_HexString(argv[1], Buffer, &Length)) return;
	Print("Length: ");
	Print_Dec(Length);
	Print_NL();
	Print_Dump(Buffer, Length);
}


void Console_CmdAsciiString(uint8_t argc, uint8_t * argv[]) {
	uint8_t Buffer[32];
	uint8_t Length;
	if(Parse_AsciiString(argv[1], Buffer, &Length, sizeof(Buffer), 3)) return;
	Print("Length: ");
	Print_Dec(Length);
	Print_NL();
	Print_Dump(Buffer, Length);
}


void Console_CmdAsciiCharacter(uint8_t argc, uint8_t * argv[]) {
	uint8_t Character;
	if(Parse_AsciiCharacter(argv[1], &Character)) return;
	Print(Character);
}


#endif
#endif
