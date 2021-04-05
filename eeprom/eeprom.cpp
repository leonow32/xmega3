// Version 2.0.0

#if COMPONENT_EEPROM

#include "eeprom.h"


// Nothing to init
void EEPROM_Init(void) {
	return;
}


// Read byte from internal EEPROM
uint8_t EEPROM_Read(uint8_t Address) {
	return *((uint8_t*)(EEPROM_START + Address));
}


// Read array from internal EEPROM
void EEPROM_Read(uint8_t Address, uint8_t * Array, size_t ArrayLength) {
	while(ArrayLength--) {
		*Array++ = EEPROM_Read(Address++);
	}
}


// Write byte to internal EEPROM
void EEPROM_Write(uint8_t Address, uint8_t Data) {
	eeprom_update_byte((uint8_t*)(uint16_t)Address, Data);
}


// Write array to internal EEPROM
void EEPROM_Write(uint8_t Address, uint8_t * Array, size_t ArrayLength) {
	while(ArrayLength--) {
		EEPROM_Write(Address++, *Array++);
	}
}


// Erase whole internal EEPROM
void EEPROM_Erase(void) {
	cli();
	CCP				= CCP_SPM_gc;
	NVMCTRL.CTRLA	= NVMCTRL_CMD_EEERASE_gc;
	sei();
}


// Fill whole internal EEPROM with byte pattern
void EEPROM_Fill(uint8_t Pattern) {
	uint8_t Address = EEPROM_SIZE - 1;
	do {
		eeprom_write_byte((uint8_t*)(uint16_t)Address, Pattern);
		asm volatile("wdr");
	} while(Address--);
}


#endif
