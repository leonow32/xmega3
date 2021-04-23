#ifndef SPI_MEM24_DEMO_H_
#define SPI_MEM24_DEMO_H_

// ========================================
// Includes
// ========================================

#include		"mem24.h"

#if COMPONENT_SPI_MASTER
	#include		"../i2c_master/i2c_master.h"
#else
	#error		"This module requires I2C_MASTER component"
#endif

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
// Console Commands
// ========================================

void Mem24_Debug(Mem24_t Result);
void Mem24_CmdRead(uint8_t argc, uint8_t * argv[]);
void Mem24_CmdWrite(uint8_t argc, uint8_t * argv[]);
void Mem24_CmdDump(uint8_t argc, uint8_t * argv[]);

#endif /* SPI_MEM_DEMO_H_ */
