// Version 2.0.0

#if COMPONENT_MEM23

#include "mem23.h"

// Init chip and set mode of operation
void Mem23_Init(void) {
	MEM23_CHIP_DESELECT;
	MEM23_CHIP_SELECT_INIT;
	Mem23_StatusWrite(MEM23_MODE_SEQUENTIAL);
}

// Get status
uint8_t Mem23_StatusRead(void) {
	uint8_t Status;
	MEM23_CHIP_SELECT;
	Status = Spi_2(MEM23_STATUS_READ, 0);
	MEM23_CHIP_DESELECT;
	return Status;
}

// Write status (to set Write Enable Latch use MEM23_WRITE_ENABLE command)
void Mem23_StatusWrite(uint8_t Status) {
	MEM23_CHIP_SELECT;
	Status = Spi_2(MEM23_STATUS_WRITE, Status);
	MEM23_CHIP_DESELECT;
}

// Read fragment of memory
void Mem23_Read(uint16_t Address, uint8_t * Buffer, uint16_t Length) {
	MEM23_CHIP_SELECT;
	Spi_3(MEM23_READ, (Address & 0xFF00) >> 8, Address & 0x00FF);
	Spi_Read(Buffer, Length);
	MEM23_CHIP_DESELECT;
}

// Write without automatic page handling
void Mem23_Write(uint16_t Address, uint8_t * Buffer, uint16_t Length) {
	MEM23_CHIP_SELECT;
	Spi_3(MEM23_WRITE, (Address & 0xFF00) >> 8, Address & 0x00FF);
	Spi_Write(Buffer, Length);
	MEM23_CHIP_DESELECT;
}

#endif 