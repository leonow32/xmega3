#ifndef MEM23_H_
#define MEM23_H_
#if COMPONENT_MEM23

// ========================================
// Includes
// ========================================

#include	<avr/io.h>
#include	"mem23_config.h"

#if COMPONENT_SPI_MASTER
	#include	"../spi_master/spi_master.h"
#else
	#error		"This module requires SPI_MASTER component"
#endif

// ========================================
// Commands
// ========================================

#define		MEM23_READ						0x03		// Read data from memory array beginning at selected address
#define		MEM23_WRITE						0x02		// Write data to memory array beginning at selected address
#define		MEM23_STATUS_READ				0x05		// Read STATUS register
#define		MEM23_STATUS_WRITE				0x01		// Write STATUS register

// Arguments of MEM23_STATUS_WRITE command
#define		MEM23_MODE_BYTE					0x00		// Only in single byte read and write operations
#define		MEM23_MODE_PAGE					0x80		// Only single page byte read and write operations
#define		MEM23_MODE_SEQUENTIAL			0x40		// All memory available without any pagination

// ========================================
// Functions
// ========================================

void		Mem23_Init(void);
uint8_t		Mem23_StatusRead(void);
void		Mem23_StatusWrite(uint8_t Status);
void		Mem23_Read(uint16_t Address, uint8_t * Buffer, uint16_t Length);
void		Mem23_Write(uint16_t Address, uint8_t * Buffer, uint16_t Length);

#endif
#endif /* MEM23_H_ */
