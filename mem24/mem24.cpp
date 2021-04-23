// Version 2.0.0

#if COMPONENT_MEM24

#include "mem24.h"


// Nothing to init
void Mem24_Init(void) {
	return;
}


// Read fragment of memory
Mem24_t Mem24_Read(uint16_t Address, uint8_t * Buffer, uint16_t Length) {	
	
	// Try to call memory address
	uint8_t TryTimes = MEM24_TRY_TIMES;
	while(TryTimes--) {
		if(TryTimes == 0) {
			I2C_Stop();
			return Mem24_Error;
		}
		
		if(I2C_Start(MEM24_ADDRESS_WRITE) == 0) {
			break;
		}
		
		_delay_ms(MEM24_TRY_PERIOD_MS);
	}
	
	// Try to write 1st byte of address
	if(I2C_Write((Address & 0xFF00) >> 8)) {
		I2C_Stop();
		return Mem24_Error;
	}
	
	// Try to write 2nd byte of address
	if(I2C_Write((Address & 0x00FF) >> 0)) {
		I2C_Stop();
		return Mem24_Error;
	}
	
	// Call read address
	if(I2C_Start(MEM24_ADDRESS_READ)) {
		I2C_Stop();
		return Mem24_Error;
	}
	
	// Rad data to the buffer
	while(Length--) {
		*Buffer++ = I2C_Read();
	}
	
	// Finish transmission
	I2C_Stop();
	return Mem24_OK;
	
}

// Write buffer to the memory
#if MEM24_MULTIPLE_PAGE_WRITE
	
	// Write with automatic page handling
	Mem24_t Mem24_Write(uint16_t Address, uint8_t * Buffer, uint16_t Length) {
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
			
			// Try to call memory address
			uint8_t TryTimes = MEM24_TRY_TIMES;
			while(TryTimes--) {
				if(TryTimes == 0) {
					I2C_Stop();
					return Mem24_Error;
				}
				
				if(I2C_Start(MEM24_ADDRESS_WRITE) == 0) {
					break;
				}
				
				_delay_ms(MEM24_TRY_PERIOD_MS);
			}
			
			// Try to write 1st byte of address
			if(I2C_Write((ActualStart & 0xFF00) >> 8)) {
				I2C_Stop();
				return Mem24_Error;
			}
			
			// Try to write 2nd byte of address
			if(I2C_Write((ActualStart & 0x00FF) >> 0)) {
				I2C_Stop();
				return Mem24_Error;
			}
			
			// Send buffer
			for(uint8_t i = 0; i < ActualLength; i++) {
				if(I2C_Write(Buffer[i])) {
					I2C_Stop();
					return Mem24_Error;
				}
			}
			
			// Finish transmission
			I2C_Stop();
			
			Buffer = Buffer + ActualLength;
			ActualPage++;
			ActualStart = ActualEnd + 1;
		}
		
		return Mem24_OK;
	}

#else
	// Write without automatic page handling
	Mem24_t Mem24_Write(uint16_t Address, uint8_t * Buffer, uint16_t Length) {
		
		// Try to call memory address
		uint8_t TryTimes = MEM24_TRY_TIMES;
		while(TryTimes--) {
			if(TryTimes == 0) {
				I2C_Stop();
				return Mem24_Error;
			}
			
			if(I2C_Start(MEM24_ADDRESS_WRITE) == 0) {
				break;
			}
			
			_delay_ms(MEM24_TRY_PERIOD_MS);
		}
		
		// Try to write 1st byte of address
		if(I2C_Write((Address & 0xFF00) >> 8)) {
			I2C_Stop();
			return Mem24_Error;
		}
		
		// Try to write 2nd byte of address
		if(I2C_Write((Address & 0x00FF) >> 0)) {
			I2C_Stop();
			return Mem24_Error;
		}
		
		// Send buffer
		while(Length--) {
			if(I2C_Write(*Buffer++)) {
				I2C_Stop();
				return Mem24_Error;
			}
		}
		
		// Finish transmission
		I2C_Stop();
		return Mem24_OK;
	}

#endif

#endif 
