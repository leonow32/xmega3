#ifndef SPI_MEM23_DEMO_H_
#define SPI_MEM23_DEMO_H_

// ========================================
// Includes
// ========================================

#include		"mem23.h"

#if COMPONENT_SPI_MASTER
	#include		"../spi_master/spi_master.h"
#else
	#error		"This module requires SPI_MASTER component"
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

void Mem23_CmdStatus(uint8_t argc, uint8_t * argv[]);
void Mem23_CmdRead(uint8_t argc, uint8_t * argv[]);
void Mem23_CmdWrite(uint8_t argc, uint8_t * argv[]);
void Mem23_CmdDump(uint8_t argc, uint8_t * argv[]);

#endif /* SPI_MEM_DEMO_H_ */
