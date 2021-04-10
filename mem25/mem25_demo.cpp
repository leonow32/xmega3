#if COMPONENT_MEM25
#include "mem25_demo.h"
#if MEM25_USE_DEMO_COMMANDS

// Read bytes from memory
void Mem25_CmdRead(uint8_t argc, uint8_t * argv[]) {
	
	if(argc == 1) {
		#if CONSOLE_USE_HELP
			Print("mem25-r adr[HEX16] len[DEC16] ");
		#endif
		return;
	}
	
	uint8_t Buffer[256];
	memset(Buffer, 0, sizeof(Buffer));
	
	// Argument 1 - address
	uint16_t Address;
	if(Parse_Hex16(argv[1], &Address)) return;
	
	// Argument 2 - length
	uint16_t Length;
	if(Parse_Dec16(argv[2], &Length, sizeof(Buffer))) return;
	
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

// Odczytywanie pamiêci
// 
// void Mem25_Demo_Dump(uint8_t argc, uint8_t * argv[]) {
// 	
// 	if(argc == 1) {
// 		#if CMD_USE_HELP
// 			Uart_Write("smdump start[hex16] length[HEX16]");
// 		#endif
// 		return;
// 	}
// 	
// 	// Agument 1 - adres pocz¹tkowy
// 	uint16_t Address;
// 	CmdRes_t CmdRes = Parse_Hex16(argv[1], &Address);
// 	//CmdRes_t CmdRes = Parse_HexNum(argv[1], &Address, 4);
// 	if(CmdRes) {
// 		///Command_Debug(CmdRes, argv[1]);
// 		return;
// 	}
// 	
// 	// Argument 2 - liczba bajtów do odczytania
// 	uint16_t Length;
// 	CmdRes = Parse_Hex16(argv[2], &Length);
// 	//CmdRes = Parse_HexNum(argv[2], &Length, 4);
// 	if(CmdRes) {
// 		///Command_Debug(CmdRes, argv[2]);
// 		return;
// 	}
// 	
// 	// Pobudka
// 	Mem25_Wake();
// 
// 	// Czekanie na gotowoœæ
// 	SpiFlash_WaitForReady();
// 	
// 	// Wykonanie polecenia
// 	Mem25_Dump(Address, Length);
// 	
// 	// Dobranoc
// 	Mem25_Sleep();
// }


#endif
#endif
