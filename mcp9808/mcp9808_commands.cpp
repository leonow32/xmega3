#if C_MCP9808
#include "mcp9808_commands.h"
#if MCP9808_USE_COMMANDS


// Debug errors
void MCP9808_Debug(MCP9808_t Result) {
	
	switch(Result) {
		case MCP9808_OK:									Print("OK");								break;
		case MCP9808_StartNACK:								Print("StartNACK");							break;
		case MCP9808_TransmissionError:						Print("TransmissionError");					break;
	}
}


// Read register
void MCP9808_CmdRead(uint8_t argc, uint8_t * argv[]) {
	
	if(argc == 1) {
		#if CONSOLE_USE_HELP
			Print("mcp9808-r adr[HEX8]");
		#endif
		return;
	}
	
	// Argument 1 - address
	uint8_t Address;
	if(Parse_Hex8(argv[1], &Address)) return;
	
	// Execute command
	uint16_t Data;
	MCP9808_t Result = MCP9808_Read(Address, &Data);
	if(Result) {
		MCP9808_Debug(Result);
	}
	else {
		Print_Hex(Data);
	}
}


// Write register
void MCP9808_CmdWrite(uint8_t argc, uint8_t * argv[]) {
	
	if(argc == 1) {
		#if CONSOLE_USE_HELP
			Print("mcp9808-w adr[HEX8] data[HEX16]");
		#endif
		return;
	}
	
	// Argument 1 - address
	uint8_t Address;
	if(Parse_Hex8(argv[1], &Address)) return;
	
	// Argument 2 - Data
	uint16_t Data;
	if(Parse_Hex16(argv[2], &Data)) return;
	
	// Execute command
	MCP9808_t Result = MCP9808_Write(Address, Data);
	MCP9808_Debug(Result);
}


// Print all registers
void MCP9808_CmdDump(uint8_t argc, uint8_t * argv[]) {
	
	// Execute command
	uint16_t Data;
	for(uint8_t Address = 0x01; Address <= 0x0C; Address++) {
		Print_Hex(Address);
		Print('\t');
		MCP9808_t Result = MCP9808_Read(Address, &Data);
		if(Result) {
			MCP9808_Debug(Result);
		}
		else {
			Print_Hex(Data);
		}
		Print_NL();
	}
}


// Read temperatures
void MCP9808_CmdTemp(uint8_t argc, uint8_t * argv[]) {
	
	// Execute command
	
}


#endif
#endif