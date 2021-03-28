#if C_I2C_MASTER 
#include "i2c_master_commands.h"
#if I2C_MASTER_USE_COMMANDS

void I2C_CmdScan(uint8_t argc, uint8_t * argv[]) {
	uint8_t i=0;
	while(1) {
		TWI0.MCTRLB		=	TWI_ACKACT_NACK_gc | TWI_MCMD_STOP_gc;	// TWI Stop
		TWI0.MADDR = i;
		while(!(TWI0.MSTATUS & (TWI_RIF_bm | TWI_WIF_bm)));			// Czekanie na flage odczytu/zapisu
		if(!(TWI0.MSTATUS & TWI_RXACK_bm)) {
			// Jeœli RXACK = 0 to badany uk³ad odpowiedzia³, jeœli 1 to brak odpowiedzi
			Print_Hex(i, ' ');
		}
		
		if(i==255) {
			TWI0.MCTRLB		=	TWI_ACKACT_NACK_gc | TWI_MCMD_STOP_gc;		// Master wysy³a NACK i koñczy sygna³ stopu
			return;
		}
		i++;
	}
}

#endif
#endif