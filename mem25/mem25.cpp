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
Mem25_t Mem25_GetID(uint8_t * ID) {
	
	#if MEM25_AUTO_SLEEP_MODE
		Mem25_Wake();
	#endif
	
	Mem25_t Result;
	Result = Mem25_WaitForReady();
	if(Result) {
		return Result;
	}
	
	MEM25_CHIP_SELECT;
	*ID = Spi_4(MEM25_WAKE, 0, 0, 0);
	MEM25_CHIP_DESELECT;
	
	#if MEM25_AUTO_SLEEP_MODE
		Mem25_Sleep();
	#endif
	
	return Mem25_OK;
}

// Erase whole memory
Mem25_t Mem25_ChipErase(void) {
	
	#if MEM25_AUTO_SLEEP_MODE
		Mem25_Wake();
	#endif
	
	Mem25_t Result;
	Result = Mem25_WaitForReady();
	if(Result) {
		return Result;
	}
	
	MEM25_CHIP_SELECT;
	Spi_1(MEM25_ERASE_CHIP);
	MEM25_CHIP_DESELECT;
	
	#if MEM25_AUTO_SLEEP_MODE
		Mem25_Sleep();
	#endif
	
	return Mem25_OK;
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
Mem25_t Mem25_WaitForReady(void) {
	
	for(uint8_t i = 0; i < MEM25_TRY_TIMES; i++) {
		
		// Set write enable latch
		MEM25_CHIP_SELECT;
		Spi_1(MEM25_WRITE_ENABLE);
		MEM25_CHIP_DESELECT;
		
		// Read status register
		MEM25_CHIP_SELECT;
		uint8_t Test = Spi_2(MEM25_STATUS_READ, 0);
		MEM25_CHIP_DESELECT;
		
		// Check if Write In Progress bit = 0 and Write Enable = 1
		if((Test & 0b00000011) == 0b00000010) {
			return Mem25_OK;
		}
		
		// Sleep
		_delay_ms(MEM25_TRY_PERIOD_MS);
	}
	
	return Mem25_Error;
}

// Read fragment of memory
Mem25_t Mem25_Read(uint16_t Address, uint8_t * Buffer, uint16_t Length) {
	
	#if MEM25_AUTO_SLEEP_MODE
		Mem25_Wake();
	#endif
	
	Mem25_t Result;
	Result = Mem25_WaitForReady();
	if(Result) {
		return Result;
	}
	
	MEM25_CHIP_SELECT;
	Spi_3(MEM25_READ, (Address & 0xFF00) >> 8, Address & 0x00FF);
	Spi_Read(Buffer, Length);
	MEM25_CHIP_DESELECT;
	
	#if MEM25_AUTO_SLEEP_MODE
		Mem25_Sleep();
	#endif
	
	return Mem25_OK;
}

// Write buffer to the memory
#if MEM25_MULTIPLE_PAGE_WRITE
	
	// Write with automatic page handling
	Mem25_t Mem25_Write(uint16_t Address, uint8_t * Buffer, uint16_t Length) {
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
			
			Mem25_t Result;
			Result = Mem25_WaitForReady();
			if(Result) {
				return Result;
			}
			
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
		
		return Mem25_OK;
	}

#else
	// Write without automatic page handling
	Mem25_t Mem25_Write(uint16_t Address, uint8_t * Buffer, uint16_t Length) {
		
		#if MEM25_AUTO_SLEEP_MODE
			Mem25_Wake();
		#endif
		
		Mem25_t Result;
		Result = Mem25_WaitForReady();
		if(Result) {
			return Result;
		}
		
		MEM25_CHIP_SELECT;
		Spi_3(MEM25_WRITE, (Address & 0xFF00) >> 8, Address & 0x00FF);
		Spi_Write(Buffer, Length);
		MEM25_CHIP_DESELECT;
		
		#if MEM25_AUTO_SLEEP_MODE
			Mem25_Sleep();
		#endif
		
		return Mem25_OK;
	}
#endif

#endif 