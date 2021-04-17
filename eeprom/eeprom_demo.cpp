// Wersja 1.08
#if COMPONENT_EEPROM
#include "eeprom_demo.h"

#if EEPROM_USE_COMMAND_DUMP
	// Dump whole internal EEPROM
	void EEPROM_Demo_Dump(uint8_t argc, uint8_t * argv[]) {
		Print_Dump((uint8_t *)EEPROM_START, EEPROM_SIZE);
	}
#endif

#if EEPROM_USE_DEMO_COMMANDS
	
	// Erase EEPROM
	void EEPROM_CmdErase(uint8_t argc, uint8_t * argv[]) {
		EEPROM_Erase();
	}
	
	
	// Save string at given address
	void EEPROM_CmdWrite(uint8_t argc, uint8_t * argv[]) {
		
		if(argc == 1) {
			#if CONSOLE_USE_HELP
				Print("ee-w adr[HEX8] string[] format[a/h]");
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
		
		// Argument 1 - Address
		uint8_t Address;
		if(Parse_Hex8(argv[1], &Address)) return;
		
		// Argument 2 - String to save
		uint8_t String[128];
		uint8_t StringLength;
		if(ParserPointer(argv[2], String, &StringLength, sizeof(String), 1)) return;
		
		// Execute command
		EEPROM_Write(Address, String, StringLength);
		Print("Length: ");
		Print_Dec(StringLength);
	}
	
#endif
#endif
