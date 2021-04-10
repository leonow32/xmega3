// Wersja 1.08

#include "spi_mem_demo.h"

// Odczytywanie pamiêci
void SpiMem_Demo_Dump(uint8_t argc, uint8_t * argv[]) {
	
	if(argc == 1) {
		#if CMD_USE_HELP
			Uart_Write("smdump start[hex16] length[HEX16]");
		#endif
		return;
	}
	
	// Agument 1 - adres pocz¹tkowy
	uint16_t Address;
	CmdRes_t CmdRes = Parse_Hex16(argv[1], &Address);
	//CmdRes_t CmdRes = Parse_HexNum(argv[1], &Address, 4);
	if(CmdRes) {
		///Command_Debug(CmdRes, argv[1]);
		return;
	}
	
	// Argument 2 - liczba bajtów do odczytania
	uint16_t Length;
	CmdRes = Parse_Hex16(argv[2], &Length);
	//CmdRes = Parse_HexNum(argv[2], &Length, 4);
	if(CmdRes) {
		///Command_Debug(CmdRes, argv[2]);
		return;
	}
	
	// Pobudka
	SpiMem_Wake();

	// Czekanie na gotowoœæ
	SpiFlash_WaitForReady();
	
	// Wykonanie polecenia
	SpiMem_Dump(Address, Length);
	
	// Dobranoc
	SpiMem_Sleep();
}
