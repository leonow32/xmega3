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


// I2C automatic tranmission composer
// Arguments:
// 1) Address of the device or address with array of bytes to be written
// 2) Optional, number of bytes to read
// Example of use:
// - i2c 30
//   Start transmission, call address 30 and stop. If no device acknowledgesm then print NACK
// - i2c 30112233
//   Start transmission, call address 30, transmit bytes 112233 and stop
// - i2c 31 4
//   Start transmission, call address 31 and read 4 bytes
// - i2c 30112233 4
//   Start transmission, call address 30, transmit bytes 112233, stop, start address 31 and read 4 bytes
void I2C_CmdTransmit(uint8_t argc, uint8_t * argv[]) {
	
	if(argc == 1) {
		#if CONSOLE_USE_HELP
			Print("i2c senddata[HEXSTR] (readcnt[DEC8])");
		#endif
		return;
	}
	
	// Argument 1 - Address or data to send
	uint8_t Buffer[128];
	uint8_t BufferLength;
	if(Parse_HexString(argv[1], Buffer, &BufferLength, sizeof(Buffer), 1)) return;
	
	// Argument 2 - Number of bytes to read
	uint8_t ReadLength;
	if(argc < 3) {
		// Second argument not provided
		ReadLength = 0;
	}
	else {
		// Second argument is provided
		if(Parse_Dec8(argv[2], &ReadLength, sizeof(Buffer))) return;
	}
	
	// Debug
	Print("Send[");
	Print_Dec(BufferLength);
	Print("]: ");
	Print_HexString(Buffer, BufferLength, ' ');
	Print_NL();
	
	// If user wants to write
	if((Buffer[0] & 0x01) == 0) {
		
		// Start transmission
		if(I2C_Start(Buffer[0])) {
			Print("NACK, adr ");
			Print_Hex(Buffer[0]);
			Print_NL();
		}
		
		// Send all given bytes
		for(uint8_t i=1; i<BufferLength; i++) {
			if(I2C_Write(Buffer[i])) {
				Print("NACK, write[");
				Print_Dec(i);
				Print("]=");
				Print_Hex(Buffer[i]);
				Print_NL();
			}
		}
		
		// Stop transmission
		I2C_Stop();
	}
	
	// If user wants to read some data
	if(ReadLength || (Buffer[0] & 0x01)) {
		
		// Start transmission
		if(I2C_Start(Buffer[0] | 0x01)) {
			Print("NACK, adr ");
			Print_Hex(uint8_t(Buffer[0] | 0x01));
			Print_NL();
		}
		
		// Read as many bytes as specified in argument 2
		uint8_t i=0;
		for(; i<ReadLength; i++) {
			Buffer[i] = I2C_Read();
		}
		
		// Stop transmission
		I2C_Stop();
		
		// Print result
		Print("Read[");
		Print_Dec(i);
		Print("]: ");
		Print_HexString(Buffer, i, ' ');
	}
}

#endif
#endif