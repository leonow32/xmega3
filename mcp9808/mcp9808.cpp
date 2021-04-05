// Version 1.0.0

#if COMPONENT_MCP9808

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


// Read temperature and convert 13-bit signed number to 32-bit signed integer. The result is temperature value multiplied by 10000.
// Example: 10000 means 1'C. 
MCP9808_t MCP9808_TemperatureGet(int32_t * Temperature) {
	
	// Read data from MCP9808_REG_TAMBIENT
	uint16_t Register;
	MCP9808_t Result = MCP9808_Read(MCP9808_REG_TAMBIENT, &Register);
	if(Result) {
		return Result;
	}
	
	// Test data
	//	Register = 0b0000000000000000;		//  0,0000
	//	Register = 0b0000000000010000;		//  1,0000
	//	Register = 0b0000000000000001;		//  0,0625
	//	Register = 0b0000000000010001;		//  1,0625
	//	Register = 0b0001111111111111;		// -0,0625
	//	Register = 0b0001111111110000;		// -1,0000
	//	Register = 0b0001111111101111;		// -1,0625
	
	// Convert to signed integer
	bool Negative = Register & 0b0001000000000000;
	Register = Register & 0x0FFF;
	int32_t Reg32;
	
	if(Negative) {
		Reg32 = uint32_t(0xFFFFF000) | Register;
	}
	else {
		Reg32 = Register;
	}
	
	*Temperature = Reg32 * 625;
	
	return MCP9808_OK;
}



#endif