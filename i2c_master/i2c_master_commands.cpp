#if C_I2C_MASTER 
#include "i2c_master_commands.h"
#if I2C_MASTER_USE_COMMANDS


// Test all addressed on I2C and check if anything 
void I2C_CmdScan(uint8_t argc, uint8_t * argv[]) {
	uint8_t i=0;
	while(1) {
		TWI0.MCTRLB		=	TWI_ACKACT_NACK_gc | TWI_MCMD_STOP_gc;	// TWI Stop
		TWI0.MADDR = i;
		while(!(TWI0.MSTATUS & (TWI_RIF_bm | TWI_WIF_bm)));			// Wait for read/write flag
		if(!(TWI0.MSTATUS & TWI_RXACK_bm)) {
			// If RXACK = 0 then received response, if RXACK = 1 then no response
			Print_Hex(i, ' ');
		}
		
		if(i==255) {
			TWI0.MCTRLB		=	TWI_ACKACT_NACK_gc | TWI_MCMD_STOP_gc;		// Master sends NACK and stops the transmission
			return;
		}
		i++;
	}
}


// Start I2C
void I2C_CmdStart(uint8_t argc, uint8_t * argv[]) {
	
	if(argc == 1) {
		#if CONSOLE_USE_HELP
			Print("i2c-s adr[HEX8]");
		#endif
		return;
	}
	
	// Argument 1 - Address
	uint8_t Address;
	if(Parse_Hex8(argv[1], &Address)) return;
	
	// Execute command
	uint8_t Result;
	Result = I2C_Start(Address);
	if(Result) {
		Print_Hex(Result);
	}
	else {
		Print("OK");
	}
}


// Read I2C
void I2C_CmdRead(uint8_t argc, uint8_t * argv[]) {
	
	if(argc == 1) {
		#if CONSOLE_USE_HELP
			Print("i2c-r count[DEC8]");
		#endif
		return;
	}
	
// 	// Argument 1 - Address
// 	uint8_t Address;
// 	if(Parse_Hex8(argv[1], &Address)) return;
	
	// Execute command
	uint8_t Result;
	Result = I2C_Read();
	Print_Hex(Result);
}


// Write I2C
void I2C_CmdWrite(uint8_t argc, uint8_t * argv[]) {
	
	if(argc == 1) {
		#if CONSOLE_USE_HELP
			Print("i2c-w byte[HEX8]");
		#endif
		return;
	}
	
	// Argument 1 - Address
	uint8_t Data;
	if(Parse_Hex8(argv[1], &Data)) return;
	
	// Execute command
	I2C_Write(Data);
}


// Stop I2C
void I2C_CmdStop(uint8_t argc, uint8_t * argv[]) {
	
	// Execute command
	I2C_Stop();
	Print("OK");
}


// I2C automatic tranmission composer
// Arguments:
// 1) Address of the device or address with array of bytes to be written
// 2) Optional, number of bytes to read
// Example of use:
// - i2c 30
//   invoke device with address 30
void I2C_CmdTransmit(uint8_t argc, uint8_t * argv[]) {
	
	if(argc == 1) {
		#if CONSOLE_USE_HELP
			Print("i2c xxx");
		#endif
		return;
	}
	
	// Argument 1 - Address or data to send
	uint8_t SendBuffer[128];
	uint8_t SendBufferLength;
	if(Parse_HexString(argv[1], SendBuffer, &SendBufferLength, sizeof(SendBuffer), 1)) return;
	
	// Argument 2 - Number of bytes to read (only if read address provided)
	uint8_t ReadLength;
	if(argc < 3) {
		// Second argument not provided
		ReadLength = 0;
	}
	else {
		// Second argument is provided
		if(Parse_Dec8(argv[2], &ReadLength, sizeof(SendBuffer))) return;
	}
	
	// Debug
	Print("Send[");
	Print_Dec(SendBufferLength);
	Print("]: ");
	Print_HexString(SendBuffer, SendBufferLength, ' ');
	Print_NL();
	
	
	
	// If user wants to write
	if(!(SendBuffer[0] & 0x01)) {
		
		// Start transmission
		if(I2C_Start(SendBuffer[0])) {
			Print("NACK");
		}
		
		for(uint8_t i=1; i<SendBufferLength; i++) {
			I2C_Write(SendBuffer[i]);
			if(I2C_CheckNACK()) {
				Print("NACK, write[");
				Print_Dec(i);
				Print("]=");
				Print_Hex(SendBuffer[i]);
				Print_NL();
			}
		}
		
		// Stop transmission
		I2C_Stop();
	}
	
	// If user wants to read some data
	if(ReadLength) {
		I2C_Start(SendBuffer[0] | 0x01);
		if(I2C_CheckNACK()) {
			Print("NACK");
			I2C_Stop();
			return;
		}
		
		uint8_t i=0;
		for(; i<ReadLength; i++) {
			SendBuffer[i] = I2C_Read();
			if(I2C_CheckNACK()) {
				Print("NACK, read[");
				Print_Dec(i);
				Print("]");
				Print_NL();
			}
		}
		
		// Stop transmission
		I2C_Stop();
		
		// Print result
		Print("Read[");
		Print_Dec(i);
		Print("]: ");
		Print_HexString(SendBuffer, i, ' ');
		
	}
}

#endif
#endif