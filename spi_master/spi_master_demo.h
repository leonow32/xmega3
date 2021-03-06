#ifndef SPI_MASTER_DEMO_H_
#define SPI_MASTER_DEMO_H_

// ========================================
// Includes
// ========================================

#include		"spi_master.h"

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

#if SPI_MASTER_USE_DEMO_COMMANDS
	void Spi_CmdTransmit(uint8_t argc, uint8_t * argv[]);
#endif

#endif /* SPI_MASTER_DEMO_H_ */
