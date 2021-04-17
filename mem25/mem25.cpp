// Version 2.0.0

#if COMPONENT_MEM25

#include "mem25.h"

// Init chip select pin
void Mem25_Init(void) {
	MEM25_CHIP_DESELECT;
	MEM25_CHIP_SELECT_INIT;
	
	#if MEM25_AUTO_SLEEP_MODE
		Mem25_Sleep();
	#endif
}

// Enable sleep mode, chip doesn't respond to any commands
void Mem25_Sleep(void) {
	Mem25_WaitForReady();
	MEM25_CHIP_SELECT;
	Spi_1(MEM25_SLEEP);
	MEM25_CHIP_DESELECT;
}

// Wake from sleep mode
void Mem25_Wake(void) {
	MEM25_CHIP_SELECT;
	Spi_1(MEM25_WAKE);
	MEM25_CHIP_DESELECT;
}

// Get ID
uint8_t Mem25_GetID(void) {
	
	#if MEM25_AUTO_SLEEP_MODE
		Mem25_Wake();
	#endif
	
	Mem25_WaitForReady();
	
	uint8_t ID;
	MEM25_CHIP_SELECT;
	ID = Spi_4(MEM25_WAKE, 0, 0, 0);
	MEM25_CHIP_DESELECT;
	
	#if MEM25_AUTO_SLEEP_MODE
		Mem25_Sleep();
	#endif
	
	return ID;
}

// Erase whole memory
void Mem25_ChipErase(void) {
	
	#if MEM25_AUTO_SLEEP_MODE
		Mem25_Wake();
	#endif
	
	Mem25_WaitForReady();
	
	MEM25_CHIP_SELECT;
	Spi_1(MEM25_WRITE_ENABLE);
	MEM25_CHIP_DESELECT;
	MEM25_CHIP_SELECT;
	Spi_1(MEM25_ERASE_CHIP);
	MEM25_CHIP_DESELECT;
	
	#if MEM25_AUTO_SLEEP_MODE
		Mem25_Sleep();
	#endif
}

// Get status
uint8_t Mem25_StatusRead(void) {
	uint8_t Status;
	MEM25_CHIP_SELECT;
	Status = Spi_2(MEM25_STATUS_READ, 0);
	MEM25_CHIP_DESELECT;
	return Status;
}

// Write status (to set Write Enable Latch use MEM25_WRITE_ENABLE command)
void Mem25_StatusWrite(uint8_t Status) {
	MEM25_CHIP_SELECT;
	Status = Spi_2(MEM25_STATUS_WRITE, Status);
	MEM25_CHIP_DESELECT;
}

// Loop as long as chip isn't ready for new commands (good idea to have watchdog enabled)
void Mem25_WaitForReady(void) {
	MEM25_CHIP_SELECT;
	while(Spi_2(MEM25_STATUS_READ, 0) & 0b00000001);
	MEM25_CHIP_DESELECT;
}

// Read fragment of memory
void Mem25_Read(uint16_t Address, uint8_t * Buffer, uint16_t Length) {
	
	#if MEM25_AUTO_SLEEP_MODE
		Mem25_Wake();
	#endif
	
	Mem25_WaitForReady();
	
	MEM25_CHIP_SELECT;
	Spi_3(MEM25_READ, (Address & 0xFF00) >> 8, Address & 0x00FF);
	Spi_Transmit(Buffer, Buffer, Length);
	MEM25_CHIP_DESELECT;
	
	#if MEM25_AUTO_SLEEP_MODE
		Mem25_Sleep();
	#endif
}

// Write buffer to the memory
#if MEM25_MULTIPLE_PAGE_WRITE
	
	// Write with automatic page handling
	void Mem25_Write(uint16_t Address, uint8_t * Buffer, uint16_t Length) {
		uint16_t AddressEnd = Address + Length - 1;
		uint16_t PageStart = Address / MEM25_PAGE_SIZE;
		uint16_t PageEnd = AddressEnd / MEM25_PAGE_SIZE;
		uint16_t ActualPage = PageStart;
		uint16_t ActualPageEnd;
		uint16_t ActualStart = Address;
		uint16_t ActualEnd;
		uint16_t ActualLength;
		
		#if MEM25_AUTO_SLEEP_MODE
			Mem25_Wake();
		#endif
		
		// Loop through all pages
		while(ActualPage <= PageEnd) {
			ActualPageEnd = MEM25_PAGE_SIZE * (ActualPage+1) - 1;
			if(AddressEnd <= ActualPageEnd) {
				ActualEnd = AddressEnd;
				} 
				else {
				ActualEnd = ActualPageEnd;
			}
			ActualLength = ActualEnd - ActualStart + 1;
			
			Mem25_WaitForReady();
			
			MEM25_CHIP_SELECT;
			Spi_1(MEM25_WRITE_ENABLE);
			MEM25_CHIP_DESELECT;
			
			MEM25_CHIP_SELECT;
			Spi_3(MEM25_WRITE, (ActualStart & 0xFF00) >> 8, ActualStart & 0x00FF);
			Spi_Write(Buffer, ActualLength);
			MEM25_CHIP_DESELECT;
			
			Buffer = Buffer + ActualLength;
			
			ActualPage++;
			ActualStart = ActualEnd + 1;
		}
		
		#if MEM25_AUTO_SLEEP_MODE
			Mem25_Sleep();
		#endif
	}

#else
	// Write without automatic page handling
	void Mem25_Write(uint16_t Address, uint8_t * Buffer, uint16_t Length) {
		// Nie uwzglêdnia stronicowania pamiêci!!!
		
		#if MEM25_AUTO_SLEEP_MODE
			Mem25_Wake();
		#endif
		
		Mem25_WaitForReady();
		
		MEM25_CHIP_SELECT;
		Spi_1(MEM25_WRITE_ENABLE);
		MEM25_CHIP_DESELECT;
		
		MEM25_CHIP_SELECT;
		Spi_3(MEM25_WRITE, (Address & 0xFF00) >> 8, Address & 0x00FF);
		Spi_Write(Buffer, Length);
		MEM25_CHIP_DESELECT;
		
		#if MEM25_AUTO_SLEEP_MODE
			Mem25_Sleep();
		#endif
	}
#endif

#endif 