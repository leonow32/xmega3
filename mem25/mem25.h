#ifndef SPIMEM_H_
#define SPIMEM_H_
#if COMPONENT_MEM25

// ========================================
// Includes
// ========================================

#include	<avr/io.h>
#include	"spi_mem_config.h"

#if COMPONENT_SPI_MASTER
	#include	"../spi_master/spi_master.h"
#else
	#error		"This module requires SPI_MASTER component"
#endif

// ========================================
// Commands
// ========================================

#define		SPIMEM_READ						0x03		// Read data from memory array beginning at selected address
#define		SPIMEM_WRITE					0x02		// Write data to memory array beginning at selected address
#define		SPIMEM_WRITE_ENABLE				0x06		// Set the write enable latch (enable write operations)
#define		SPIMEM_WRITE_DISABLE			0x04		// Reset the write enable latch (disable write operations)
#define		SPIMEM_STATUS_READ				0x05		// Read STATUS register
#define		SPIMEM_STATUS_WRITE				0x01		// Write STATUS register
#define		SPIMEM_ERASE_PAGE				0x42		// Page Erase – erase one page in memory array
#define		SPIMEM_ERASE_SECTOR				0xD8		// Sector Erase – erase one sector in memory array
#define		SPIMEM_ERASE_CHIP				0xC7		// Chip Erase – erase all sectors in memory array
#define		SPIMEM_WAKE						0xAB		// Release from Deep power-down and read electronic signature
#define		SPIMEM_SLEEP					0xB9		// Deep Power-Down mode

// ========================================
// Functions
// ========================================

void		SpiMem_Init(void);
void		SpiMem_Sleep(void);
void		SpiMem_Wake(void);
void		SpiMem_WriteEnable(void);
void		SpiMem_WriteDisble(void);
void		SpiMem_ChipErase(void);
uint8_t		SpiMem_StatusRead(void);
void		SpiMem_StaturWrite(uint8_t Status);
bool		SpiMem_IsBusy(void);
void		SpiFlash_WaitForReady(void);
uint8_t		SpiMem_Read(uint16_t Address);
void		SpiMem_Read(uint16_t Address, uint8_t * Buffer, uint16_t Length);
void		SpiMem_WriteMultiPage(uint16_t Address, const uint8_t * Buffer, uint16_t Length);
void		SpiMem_Write(uint16_t Address, uint8_t Byte);
void		SpiMem_Write(uint16_t Address, const uint8_t * Buffer, uint16_t Length);
void		SpiMem_Dump(uint16_t Start, uint16_t Length);

#endif
#endif /* SPIMEM_H_ */
