// Version 2.0.0

#if COMPONENT_MEM24

#include "mem24.h"

// Nothing to init
void Mem24_Init(void) {
	return;
}

// Loop as long as chip isn't ready for new commands (good idea to have watchdog enabled)
void Mem24_WaitForReady(void) {
	while(I2C_Start(MEM24_ADDRESS_WRITE));
	I2C_Stop();
}

// Read fragment of memory
void Mem24_Read(uint16_t Address, uint8_t * Buffer, uint16_t Length) {	
	Mem24_WaitForReady();
	I2C_Start(MEM24_ADDRESS_WRITE);
	I2C_Write((Address & 0xFF00) >> 8);
	I2C_Write((Address & 0x00FF) >> 0);
	I2C_Start(MEM24_ADDRESS_READ);
	while(Length--) {
		*Buffer++ = I2C_Read();
	}
	I2C_Stop();
}

// Write buffer to the memory
#if MEM24_MULTIPLE_PAGE_WRITE
	
	// Write with automatic page handling
	void Mem24_Write(uint16_t Address, uint8_t * Buffer, uint16_t Length) {
		uint16_t AddressEnd = Address + Length - 1;
		uint16_t PageStart = Address / MEM24_PAGE_SIZE;
		uint16_t PageEnd = AddressEnd / MEM24_PAGE_SIZE;
		uint16_t ActualPage = PageStart;
		uint16_t ActualPageEnd;
		uint16_t ActualStart = Address;
		uint16_t ActualEnd;
		uint16_t ActualLength;
		
		// Loop through all pages
		while(ActualPage <= PageEnd) {
			ActualPageEnd = MEM24_PAGE_SIZE * (ActualPage+1) - 1;
			if(AddressEnd <= ActualPageEnd) {
				ActualEnd = AddressEnd;
				} 
				else {
				ActualEnd = ActualPageEnd;
			}
			ActualLength = ActualEnd - ActualStart + 1;
			
			Mem24_WaitForReady();
			
			I2C_Start(MEM24_ADDRESS_WRITE);
			I2C_Write((ActualStart & 0xFF00) >> 8);
			I2C_Write((ActualStart & 0x00FF) >> 0);
			for(uint8_t i = 0; i < ActualLength; i++) {
				I2C_Write(Buffer[i]);
			}
			I2C_Stop();
			
			Buffer = Buffer + ActualLength;
			
			ActualPage++;
			ActualStart = ActualEnd + 1;
		}
	}

#else
	// Write without automatic page handling
	void Mem24_Write(uint16_t Address, uint8_t * Buffer, uint16_t Length) {
		
		Mem24_WaitForReady();
		
		I2C_Start(MEM24_ADDRESS_WRITE);
		I2C_Write((Address & 0xFF00) >> 8);
		I2C_Write((Address & 0x00FF) >> 0);
		while(Length--) {
			I2C_Write(*Buffer++);
		}
		I2C_Stop();
		
	}
#endif

#endif 