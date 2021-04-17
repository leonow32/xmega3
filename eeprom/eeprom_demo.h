// Wersja 1.08

#ifndef EEPROM_DEMO_H_
#define EEPROM_DEMO_H_

// ========================================
// Includes
// ========================================

#include		"eeprom.h"

#if COMPONENT_CONSOLE
	#include	"../console/console.h"
#else
	#error		"This module requires CONSOLE component"
#endif

#if COMPONENT_PRINT
	#include	"../print/print.h"
#else
	#error		"This module requires PRINT component"
#endif

// ========================================
// Console commands
// ========================================

#if EEPROM_USE_COMMAND_DUMP
	void EEPROM_Demo_Dump(uint8_t argc, uint8_t * argv[]);
#endif

#if EEPROM_USE_DEMO_COMMANDS
	void EEPROM_CmdErase(uint8_t argc, uint8_t * argv[]);
	void EEPROM_CmdWrite(uint8_t argc, uint8_t * argv[]);
#endif

#endif /* EEPROM_DEMO_H_ */