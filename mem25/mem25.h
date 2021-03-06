#ifndef MEM25_H_
#define MEM25_H_
#if COMPONENT_MEM25

// ========================================
// Includes
// ========================================

#include	<avr/io.h>
#include	<util/delay.h>
#include	"mem25_config.h"

#if COMPONENT_SPI_MASTER
	#include	"../spi_master/spi_master.h"
#else
	#error		"This module requires SPI_MASTER component"
#endif

// ========================================
// Result type
// ========================================

enum Mem25_t {
	Mem25_OK = 0,	// Success
	Mem25_Error,	// Timeout
};

// ========================================
// Commands
// ========================================

#define		MEM25_READ						0x03		// Read data from memory array beginning at selected address
#define		MEM25_WRITE						0x02		// Write data to memory array beginning at selected address
#define		MEM25_WRITE_ENABLE				0x06		// Set the write enable latch (enable write operations)
#define		MEM25_WRITE_DISABLE				0x04		// Reset the write enable latch (disable write operations)
#define		MEM25_STATUS_READ				0x05		// Read STATUS register
#define		MEM25_STATUS_WRITE				0x01		// Write STATUS register
#define		MEM25_ERASE_PAGE				0x42		// Page Erase ? erase one page in memory array
#define		MEM25_ERASE_SECTOR				0xD8		// Sector Erase ? erase one sector in memory array
#define		MEM25_ERASE_CHIP				0xC7		// Chip Erase ? erase all sectors in memory array
#define		MEM25_WAKE						0xAB		// Release from Deep power-down and read electronic signature
#define		MEM25_SLEEP						0xB9		// Deep Power-Down mode

// ========================================
// Functions
// ========================================

void		Mem25_Init(void);
void		Mem25_Sleep(void);
void		Mem25_Wake(void);
Mem25_t		Mem25_GetID(uint8_t * ID);
Mem25_t		Mem25_ChipErase(void);
uint8_t		Mem25_StatusRead(void);
void		Mem25_StatusWrite(uint8_t Status);
Mem25_t		Mem25_WaitForReady(void);
Mem25_t		Mem25_Read(uint16_t Address, uint8_t * Buffer, uint16_t Length);
Mem25_t		Mem25_Write(uint16_t Address, uint8_t * Buffer, uint16_t Length);

#endif
#endif /* MEM25_H_ */
