// Wersja 1.08
#if C_EEPROM
#include "eeprom_demo.h"

#if EEPROM_USE_COMMAND_DUMP
	// Dump whole internal EEPROM
	void EEPROM_Demo_Dump(uint8_t argc, uint8_t * argv[]) {
		Print_Dump((uint8_t *)EEPROM_START, EEPROM_SIZE);
	}
#endif

#if EEPROM_USE_COMMAND_READ_WRITE
	
	// Erase EEPROM
	void EEPROM_Demo_Erase(uint8_t argc, uint8_t * argv[]) {
		EEPROM_Erase();
	}
	
	// WyFill EEPROM with patters
	void EEPROM_Demo_Fill(uint8_t argc, uint8_t * argv[]) {
	
		if(argc == 1) {
			#if CONSOLE_USE_HELP
				Print("ee-fill pattern[HEX8]");
			#endif
			return;
		}
	
		// Argument 1 - Address
		uint8_t Pattern;
		if(Parse_Hex8(argv[1], &Pattern)) return;
	
		// Execute command
		EEPROM_Fill(Pattern);
	}
	
	
	// Print one byte at given address
	void EEPROM_Demo_ReadByte(uint8_t argc, uint8_t * argv[]) {
	
		if(argc == 1) {
			#if CONSOLE_USE_HELP
				Print("ee-r adr[HEX8]");
			#endif
			return;
		}
	
		// Argument 1 - Address
		uint8_t Address;
		if(Parse_Hex8(argv[1], &Address)) return;
	
		// Execute command
		uint8_t Data = EEPROM_Read(Address);
		Print("\r\nValue: ");
		Print_Hex(Data);
	}
	
	
	// Print string from EEPROM
	void EEPROM_Demo_ReadString(uint8_t argc, uint8_t * argv[]) {
	
		if(argc == 1) {
			#if CONSOLE_USE_HELP
				Print("ee-rs adr[HEX8] length[DEC16]");
			#endif
			return;
		}
	
		// Argument 1 - Address
		uint8_t Address;
		if(Parse_Hex8(argv[1], &Address)) return;
	
		// Argument 2 - String length to read
		uint16_t Length;
		if(Parse_Dec16(argv[2], &Length, 256)) return;
	
		// Execute command
		uint8_t Buffer[256];
		memset(Buffer, 0, sizeof(Buffer));
		EEPROM_Read(Address, Buffer, Length);
		Print("Length: ");
		Print_Dec(Length);
		Print("\r\nString: ");
		Print((char*)Buffer);
	}
	
	// Save one byte at given address
	void EEPROM_Demo_WriteByte(uint8_t argc, uint8_t * argv[]) {
	
		if(argc == 1) {
			#if CONSOLE_USE_HELP
				Print("ee-w adr[HEX8] byte[HEX8]");
			#endif
			return;
		}
	
		// Argument 1 - Address
		uint8_t Address;
		if(Parse_Hex8(argv[1], &Address)) return;
	
		// Argument 2 - Value to save
		uint8_t Byte;
		if(Parse_Hex8(argv[2], &Byte)) return;
	
		// Execute command
		eeprom_update_byte((uint8_t*)(uint16_t)(Address), Byte);
	}
	
	// Save string at given address
	void EEPROM_Demo_WriteString(uint8_t argc, uint8_t * argv[]) {
	
		if(argc == 1) {
			#if CONSOLE_USE_HELP
				Print("ee-ws adr[HEX8] string[ASC]");
			#endif
			return;
		}
	
		// Argument 1 - Address
		uint8_t Address;
		if(Parse_Hex8(argv[1], &Address)) return;
	
		// Argument 2 - String to save
		uint8_t String[128];
		uint8_t StringLength;
		if(Parse_AsciiString(argv[2], String, &StringLength, sizeof(String))) return;
	
		// Execute command
		EEPROM_Write(Address, String, StringLength);
		Print("Length: ");
		Print_Dec(StringLength);
	}
	
#endif
#endif
