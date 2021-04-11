#ifndef SPI_MEM_DEMO_H_
#define SPI_MEM_DEMO_H_

// ========================================
// Includes
// ========================================

#include		"mem25.h"

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

void Mem25_CmdStatus(uint8_t argc, uint8_t * argv[]);
void Mem25_CmdWriteEnableDisable(uint8_t argc, uint8_t * argv[]);
void Mem25_CmdRead(uint8_t argc, uint8_t * argv[]);
void Mem25_CmdDump(uint8_t argc, uint8_t * argv[]);
//void Mem25_Demo_Dump(uint8_t argc, uint8_t * argv[]);


#endif /* SPI_MEM_DEMO_H_ */
