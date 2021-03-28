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
			// If RXACK = 0 then received responde, if RXACK = 1 then no response
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

#endif
#endif