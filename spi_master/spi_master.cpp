// Version 3.0.0

#if COMPONENT_SPI_MASTER

#include "spi_master.h"


// Initialization of SPI peripheral
void Spi_Init(void) {
	
	// GPIO config
	#if (HW_CPU_ATtinyXX16 || HW_CPU_ATtinyXX17) && SPI_PORTA_13
		VPORTA.DIR			|=		PIN1_bm;						// MOSI
		VPORTA.DIR			&=	~	PIN2_bm;						// MISO
		VPORTA.DIR			|=		PIN3_bm;						// SCK
	#endif
	
	#if (HW_CPU_ATtinyXX16 || HW_CPU_ATtinyXX17) && SPI_PORTC_02
		PORTMUX.CTRLB		|=		PORTMUX_SPI0_ALTERNATE_gc;		// Alternative GPIO
		VPORTC.DIR			|=		PIN0_bm;						// SCK
		VPORTC.DIR			&=	~	PIN1_bm;						// MISO
		VPORTC.DIR			|=		PIN2_bm;						// MOSI
	#endif
	
	#if (HW_CPU_ATmegaXX09 || HW_CPU_ATmegaXX08_28pin || HW_CPU_ATmegaXX08_32pin) && SPI_PORTA_46
		VPORTA.DIR			|=		PIN4_bm;						// MOSI
		VPORTA.DIR			&=	~	PIN5_bm;						// MISO
		VPORTA.DIR			|=		PIN6_bm;						// SCK
	#endif
	
	#if (HW_CPU_ATmegaXX09 || HW_CPU_ATmegaXX08_28pin || HW_CPU_ATmegaXX08_32pin) && SPI_PORTC_02
		PORTMUX.TWISPIROUTEA |= PORTMUX_SPI0_ALT1_gc;				// Alternative GPIO
		VPORTC.DIR			|=		PIN0_bm;						// MOSI
		VPORTC.DIR			&=	~	PIN1_bm;						// MISO
		VPORTC.DIR			|=		PIN2_bm;						// SCK
	#endif
	
	#if (HW_CPU_ATmegaXX09) && SPI_PORTE_02
		PORTMUX.TWISPIROUTEA |= PORTMUX_SPI0_ALT2_gc;				// Alternative GPIO
		VPORTE.DIR			|=		PIN0_bm;						// MOSI
		VPORTE.DIR			&=	~	PIN1_bm;						// MISO
		VPORTE.DIR			|=		PIN2_bm;						// SCK
	#endif
	
	// SPI peripheral config
	SPI0.CTRLB				=		SPI_BUFEN_bm |					// Buffer Mode Enable
								//	SPI_BUFWR_bm |					// Buffer Mode Wait for Receive
									SPI_SSD_bm |					// Slave Select Disable
									SPI_MODE_0_gc 					// SPI Mode
									;
	SPI0.CTRLA				=	//	SPI_DORD_bm |					// Data order
									SPI_MASTER_bm |					// SPI Master mode selected
									SPI_CLK2X_bm |					// Clock Double
									SPI_PRESC_DIV4_gc |				// F_SCK = F_CPU/2
									SPI_ENABLE_bm					// SPI Enable
									;
	
	// Initialization of CS pin for demo commands
	// All SPI devices should have init of cCS pin in their own Init() function
	#if SPI_MASTER_USE_DEMO_COMMANDS
		SPI_DEMO_DIR_SET;
		SPI_DEMO_CHIP_DESELECT;
	#endif
}	


// Send 1 byte and return a byte received while sending
uint8_t Spi_1(const uint8_t Byte) {
	asm volatile("cli");											// Disable interrupts
	SPI0.INTFLAGS			=		SPI_TXCIF_bm;					// Clear flags
	SPI0.DATA				=		Byte;							// Put data to the buffer and send immediately
	while(!(SPI0.INTFLAGS & SPI_TXCIF_bm));							// Wait for end of transmission
	asm volatile("sei");											// Enable interrupts
	return SPI0.DATA;												// Return a byte received while sending
} 


// Send 2 bytes and return a byte received while sending 2nd byte
uint8_t Spi_2(const uint8_t Byte1, const uint8_t Byte2) {
	asm volatile("cli");											// Disable interrupts
	SPI0.INTFLAGS			=		SPI_TXCIF_bm;					// Clear flags
	SPI0.DATA				=		Byte1;							// Put data to the buffer without witing for anything
	SPI0.DATA				=		Byte2;
	while(!(SPI0.INTFLAGS & SPI_TXCIF_bm));							// Wait for end of transmission
	(void)SPI0.DATA;												// Dummy read of 1st received byte
	asm volatile("sei");											// Enable interrupts
	return SPI0.DATA;												// Return 2nd received byte
}


// Send 3 bytes and return a byte received while sending 3rd byte
uint8_t Spi_3(const uint8_t Byte1, const uint8_t Byte2, const uint8_t Byte3) {
	asm volatile("cli");											// Disable interrupts
	SPI0.INTFLAGS			=		SPI_TXCIF_bm;					// Clear flags
	SPI0.DATA				=		Byte1;							// Put data to the buffer without witing for anything
	SPI0.DATA				=		Byte2;
	while(!(SPI0.INTFLAGS & SPI_DREIF_bm));
	SPI0.DATA				=		Byte3;
	(void)SPI0.DATA;												// Dummy read of 1st received byte
	while(!(SPI0.INTFLAGS & SPI_TXCIF_bm));							// Wait for end of transmission
	(void)SPI0.DATA;												// Dummy read of 2nd received byte
	asm volatile("sei");											// Enable interrupts
	return SPI0.DATA;												// Return 3rd received byte
}


// Send 4 bytes and return a byte received while sending 4th byte
uint8_t Spi_4(const uint8_t Byte1, const uint8_t Byte2, const uint8_t Byte3, const uint8_t Byte4) {
	asm volatile("cli");											// Disable interrupts
	SPI0.INTFLAGS			=		SPI_TXCIF_bm;					// Clear flags
	SPI0.DATA				=		Byte1;							// Put data to the buffer without witing for anything
	SPI0.DATA				=		Byte2;
	while(!(SPI0.INTFLAGS & SPI_DREIF_bm));
	SPI0.DATA				=		Byte3;
	(void)SPI0.DATA;												// Dummy read of 1st received byte
	while(!(SPI0.INTFLAGS & SPI_DREIF_bm));
	SPI0.DATA				=		Byte4;
	(void)SPI0.DATA;												// Dummy read of 2nd received byte
	while(!(SPI0.INTFLAGS & SPI_TXCIF_bm));							// Wait for end of transmission
	(void)SPI0.DATA;												// Dummy read of 3rd received byte
	asm volatile("sei");											// Enable interrupts
	return SPI0.DATA;												// Return 4th received byte
}


// Send 5 bytes and return a byte received while sending 5th byte
uint8_t Spi_5(const uint8_t Byte1, const uint8_t Byte2, const uint8_t Byte3, const uint8_t Byte4, const uint8_t Byte5) {
	asm volatile("cli");											// Disable interrupts
	SPI0.INTFLAGS			=		SPI_TXCIF_bm;					// Clear flags
	SPI0.DATA				=		Byte1;							// Put data to the buffer without witing for anything
	SPI0.DATA				=		Byte2;
	while(!(SPI0.INTFLAGS & SPI_DREIF_bm));
	SPI0.DATA				=		Byte3;
	(void)SPI0.DATA;												// Dummy read of 1st received byte
	while(!(SPI0.INTFLAGS & SPI_DREIF_bm));
	SPI0.DATA				=		Byte4;
	(void)SPI0.DATA;												// Dummy read of 2nd received byte
	while(!(SPI0.INTFLAGS & SPI_DREIF_bm));
	SPI0.DATA				=		Byte5;
	(void)SPI0.DATA;												// Dummy read of 3rd received byte
	while(!(SPI0.INTFLAGS & SPI_TXCIF_bm));							// Wait for end of transmission
	(void)SPI0.DATA;												// Dummy read of 4th received byte
	asm volatile("sei");											// Enable interrupts
	return SPI0.DATA;												// Return 5th received byte
}


// Send and receive array of bytes. It has sense only when Length > 2
void Spi_Transmit(uint8_t * TxBuffer, uint8_t * RxBuffer, const uint16_t Length) {
	
	// Disable interrupts
	asm volatile("cli");	
	
	// Sanity check
	if(Length == 0) {
		return;
	}
	else if(Length < 2) {
		*RxBuffer = Spi_1(*TxBuffer);
		return;
	}
	
	// Clear flags
	SPI0.INTFLAGS			=		SPI_RXCIF_bm;
	
	// Limiter
	uint8_t * Limit			=		TxBuffer + Length;
	
	// Put first two bytes to hardware buffer without witing for anything
	SPI0.DATA				=		*TxBuffer++;
	SPI0.DATA				=		*TxBuffer++;

	// Transmit in a loop
	while(TxBuffer != Limit) {
		while(!(SPI0.INTFLAGS & SPI_DREIF_bm));
		SPI0.DATA			=		*TxBuffer++;
		*RxBuffer++			=		SPI0.DATA;
	}
	
	// Read two last bytes after RXC flag is set
	while(!(SPI0.INTFLAGS & SPI_RXCIF_bm));
	*RxBuffer++				=		SPI0.DATA;
	
	while(!(SPI0.INTFLAGS & SPI_RXCIF_bm));
	*RxBuffer++				=		SPI0.DATA;
	
	// Enable interrupts
	asm volatile("sei");
}


// Read array of bytes while sending dummy bytes. It has sense only when Length > 2
void Spi_Read(uint8_t * RxBuffer, const uint16_t Length, uint8_t DummyByte) {
	
	// Disable interrupts
	asm volatile("cli");
	
	// Sanity check
	if(Length == 0) {
		return;
	}
	else if(Length < 2) {
		*RxBuffer = Spi_1(DummyByte);
		return;
	}
	
	// Clear flags
	SPI0.INTFLAGS			=		SPI_RXCIF_bm;
	
	// Limiter
	uint8_t * Limit			=		RxBuffer + Length - 2;
	
	// Put first two bytes to hardware buffer without witing for anything
	SPI0.DATA				=		DummyByte;
	SPI0.DATA				=		DummyByte;

	// Transmit in a loop
	while(RxBuffer != Limit) {
		while(!(SPI0.INTFLAGS & SPI_DREIF_bm));
		SPI0.DATA			=		DummyByte;
		*RxBuffer++			=		SPI0.DATA;
	}
	
	// Read two last bytes after RXC flag is set
	while(!(SPI0.INTFLAGS & SPI_RXCIF_bm));
	*RxBuffer++				=		SPI0.DATA;
	
	while(!(SPI0.INTFLAGS & SPI_RXCIF_bm));
	*RxBuffer++				=		SPI0.DATA;
	
	// Enable interrupts
	asm volatile("sei");
}


// Send array of bytes. It has sense only when Length > 2
void Spi_Write(const uint8_t * TxBuffer, const uint16_t Length) {
	
	// Disable interrupts
	asm volatile("cli");
	
	// Sanity check
	if(Length == 0) {
		return;
	}
	else if(Length < 2) {
		Spi_1(*TxBuffer);
		return;
	}
	
	// Limiter
	const uint8_t * Limit	=		TxBuffer + Length;
	
	// Clear flags
	SPI0.INTFLAGS			=		SPI_RXCIF_bm;
	
	// Put first two bytes to hardware buffer without witing for anything
	SPI0.DATA				=		*TxBuffer++;
	SPI0.DATA				=		*TxBuffer++;
	
	// Transmit in a loop
	while(TxBuffer != Limit) {
		while(!(SPI0.INTFLAGS & SPI_DREIF_bm));
		SPI0.DATA			=		*TxBuffer++;
		(void)SPI0.DATA;
	}
	
	// Read two last bytes after RXC flag is set
	while(!(SPI0.INTFLAGS & SPI_RXCIF_bm));
	SPI0.INTFLAGS			=		SPI_RXCIF_bm;
	(void)SPI0.DATA;
	
	while(!(SPI0.INTFLAGS & SPI_RXCIF_bm));
	(void)SPI0.DATA;
	
	// Enable interrupts
	asm volatile("sei");
}


// Send the same 2 bytes multiple times
// Return after all the bytes are sent, so no worries about chip deselect too early
void Spi_Repeat(const uint8_t Byte, uint16_t Times) {
	
	if(Times == 0) return;
	
	// Disable interrupts
	asm volatile("cli");
	
	// Sanity check
	if(Times < 2) {
		Spi_1(Byte);
		return;
	}
	
	// Clear flags
	SPI0.INTFLAGS			=		SPI_RXCIF_bm;
	
	// Put first two bytes to hardware buffer without witing for anything
	SPI0.DATA				=		Byte;
	SPI0.DATA				=		Byte;
	
	// Ogranicznik
	Times = Times - 2;
	
	// Transmit in a loop
	while(Times--) {
		while(!(SPI0.INTFLAGS & SPI_DREIF_bm));
		SPI0.DATA			=		Byte;
		(void)SPI0.DATA;
	}
	
	// Read two last bytes after RXC flag is set
	while(!(SPI0.INTFLAGS & SPI_RXCIF_bm));
	(void)SPI0.DATA;
	SPI0.INTFLAGS			=		SPI_RXCIF_bm;
	
	while(!(SPI0.INTFLAGS & SPI_RXCIF_bm));
	(void)SPI0.DATA;
	
	// Enable interrupts
	asm volatile("sei");
}


// Send the same 2 bytes multiple times
// Return after all the bytes are sent, so no worries about chip deselect too early
void Spi_Repeat(const uint8_t Byte1, const uint8_t Byte2, uint16_t Times) {
	
	if(Times == 0) return;
	
	// Disable interrupts
	asm volatile("cli");
	
	// Clear flags
	SPI0.INTFLAGS			=		SPI_RXCIF_bm;
	
	// Put first two bytes to hardware buffer without witing for anything
	SPI0.DATA				=		Byte1;
	SPI0.DATA				=		Byte2;
	
	// Limiter
	Times = Times - 1;
	
	// Transmit in a loop
	while(Times--) {
		while(!(SPI0.INTFLAGS & SPI_DREIF_bm));
		SPI0.DATA			=		Byte1;
		(void)SPI0.DATA;
		while(!(SPI0.INTFLAGS & SPI_DREIF_bm));
		SPI0.DATA			=		Byte2;
		(void)SPI0.DATA;
	}
	
	// Read two last bytes after RXC flag is set
	while(!(SPI0.INTFLAGS & SPI_RXCIF_bm));
	(void)SPI0.DATA;
	SPI0.INTFLAGS			=		SPI_RXCIF_bm;
	
	while(!(SPI0.INTFLAGS & SPI_RXCIF_bm));
	(void)SPI0.DATA;
	
	// Enable interrupts
	asm volatile("sei");
}

#endif