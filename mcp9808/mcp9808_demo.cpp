#if COMPONENT_MCP9808
#include "mcp9808_demo.h"
#if MCP9808_USE_DEMO_COMMANDS


// Debug errors
void MCP9808_Debug(MCP9808_t Result) {
	switch(Result) {
		case MCP9808_OK:									Print_ResponseOK();							break;
		case MCP9808_Timeout:								Print_ResponseTimeout();					break;
		case MCP9808_TransmissionError:						Print_ResponseTransmissionError();			break;
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
void MCP9808_CmdTemperature(uint8_t argc, uint8_t * argv[]) {
	
	// Execute command
	int32_t Temperature;
	MCP9808_t Result = MCP9808_TemperatureGet(&Temperature);
	if(Result) {
		MCP9808_Debug(Result);
		return;
	}
	
	// Print sign
	if(Temperature < 0) {
		Print('-');
		Temperature = -Temperature;
	}
	
	// Print integer part
	uint32_t Integer = Temperature / 10000;
	Print_Dec(Integer);
	Print('.');
	
	// Print factorial part
	uint32_t Factorial = Temperature - Integer * 10000;
	if(Factorial == 0) {
		Print("0000");
	}
	else if(Factorial < 1000) {
		Print('0');
		Print_Dec(Factorial);
	}
	else {
		Print_Dec(Factorial);
	}
}


#endif
#endif