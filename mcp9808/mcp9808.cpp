// Version 1.0.0

#if C_MCP9808

#include "mcp9808.h"


// Initialization
void MCP9808_Init(void) {
	return;
}


// Read register
MCP9808_t MCP9808_Read(uint8_t Register, uint16_t * Data) {
	
	MCP9808_t Result = MCP9808_OK;
	
	if(I2C_Start(MCP9808_ADDRESS_WRITE)) {
		Result = MCP9808_StartNACK;
		goto Stop;
	}
	
	if(I2C_Write(Register)) {
		Result = MCP9808_TransmissionError;
		goto Stop;
	}
	
	if(I2C_Start(MCP9808_ADDRESS_READ)) {
		Result = MCP9808_StartNACK;
		goto Stop;
	}
	
	*Data = uint16_t(I2C_Read()) << 8 | I2C_Read();
	
	Stop:
	I2C_Stop();
	return Result;
}


// Write register
MCP9808_t MCP9808_Write(uint8_t Register, uint16_t Data) {
	
	MCP9808_t Result = MCP9808_OK;
	
	if(I2C_Start(MCP9808_ADDRESS_WRITE)) {
		Result = MCP9808_StartNACK;
		I2C_Stop();
	}
	
	if(I2C_Write(Register)) {
		Result = MCP9808_TransmissionError;
		goto Stop;
	}
	
	if(I2C_Write(uint8_t((Data & 0xFF00) >> 8) )) {
		Result = MCP9808_TransmissionError;
		goto Stop;
	}
	
	if(I2C_Write(uint8_t((Data & 0x00FF) >> 0) )) {
		Result = MCP9808_TransmissionError;
		goto Stop;
	}
	
	Stop:
	I2C_Stop();
	return Result;
}



#endif