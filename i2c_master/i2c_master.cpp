// Version 3.00

#if C_I2C_MASTER

#include "i2c_master.h"

// Initialization of I2C peripheral
void I2C_Init(void) {
	
	// GPIO config
	#if (HW_CPU_ATtinyXX12 || HW_CPU_ATtinyXX14 || HW_CPU_ATtinyXX16 || HW_CPU_ATtinyXX17) && I2C_PORTB_01
		PORTMUX.CTRLB			&= ~PORTMUX_TWI0_bm;
		PORTB.PIN0CTRL			 =	PORT_PULLUPEN_bm;
		PORTB.PIN1CTRL			 =	PORT_PULLUPEN_bm;
	#endif
	
	#if (HW_CPU_ATtinyXX12 || HW_CPU_ATtinyXX14 || HW_CPU_ATtinyXX16 || HW_CPU_ATtinyXX17) && I2C_PORTA_12
		PORTMUX.CTRLB			|=  PORTMUX_TWI0_bm;
		PORTA.PIN1CTRL			 =	PORT_PULLUPEN_bm;
		PORTA.PIN2CTRL			 =	PORT_PULLUPEN_bm;
	#endif
	
	#if (HW_CPU_ATmegaXX09 || HW_CPU_ATmegaXX08_28pin || HW_CPU_ATmegaXX08_32pin) && I2C_PORTA_23
		PORTMUX.TWISPIROUTEA	&= ~PORTMUX_TWI0_gm;
		PORTA.PIN2CTRL			 =	PORT_PULLUPEN_bm;
		PORTA.PIN3CTRL			 =	PORT_PULLUPEN_bm;
	#endif
	
	#if (HW_CPU_ATmegaXX09 || HW_CPU_ATmegaXX08_28pin || HW_CPU_ATmegaXX08_32pin) && I2C_PORTC_23
		PORTMUX.TWISPIROUTEA	|=	PORTMUX_TWI0_ALT2_gc;
		PORTC.PIN2CTRL			 =	PORT_PULLUPEN_bm;
		PORTC.PIN3CTRL			 =	PORT_PULLUPEN_bm;
	#endif
	
	// TWI peripheral config
	TWI0.DBGCTRL			=	TWI_DBGRUN_bm;
	TWI0.MBAUD				=	(F_CPU / (2*I2C_MASTER_SCL_FREQUENCY)) - 10;
	TWI0.CTRLA				=	TWI_ENABLE_bm;
	TWI0.MCTRLA				=	TWI_ENABLE_bm;
	TWI0.MCTRLB				=	TWI_FLUSH_bm;
	TWI0.MSTATUS			=	TWI_RIF_bm |						// Clean read interrupt flag
								TWI_WIF_bm |						// Clean write interrupt flag
								TWI_BUSSTATE_IDLE_gc;				// Set bus state
}


// Start of transmission
// result=0 - correct
// result>0 - error
uint8_t I2C_Start(uint8_t Address) {
	TWI0.MSTATUS			=	TWI_RIF_bm |						// Clean read interrupt flag
								TWI_WIF_bm |						// Clean write interrupt flag
								TWI_BUSSTATE_IDLE_gc;				// Set bus state
	TWI0.MADDR = Address;
	while(!(TWI0.MSTATUS & (TWI_RIF_bm | TWI_WIF_bm))); 			// Wait until done
	return TWI0.MSTATUS & TWI_RXACK_bm;								// 0 means correct start
}


// Write data to the bus
void I2C_Write(uint8_t Data) {
	TWI0.MDATA = Data;
	while (!(TWI0.MSTATUS & TWI_WIF_bm));							// Wait until done
}


// Read data from the bus
uint8_t I2C_Read(void) {
	if(TWI0.MSTATUS & (TWI_RIF_bm | TWI_RXACK_bm)) {				// If something has been received during execution of Start() then return it now
		return TWI0.MDATA;
	}
	
	TWI0.MCTRLB		=	TWI_MCMD_RECVTRANS_gc;
	while(!(TWI0.MSTATUS & (TWI_RIF_bm | TWI_RXACK_bm)));			// Wait until done
	return TWI0.MDATA;
}


// End of transmission
void I2C_Stop(void) {
	TWI0.MCTRLB		=	TWI_ACKACT_NACK_gc | TWI_MCMD_STOP_gc;		// Master sends NACK and finishes the transmission
}


#endif