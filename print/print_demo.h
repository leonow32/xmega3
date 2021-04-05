#ifndef PRINT_DEMO_H_
#define PRINT_DEMO_H_

// ========================================
// Includes
// ========================================

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

void Print_CmdColor(uint8_t argc, uint8_t * argv[]);
void Print_CmdAscii(uint8_t argc, uint8_t * argv[]);
void Print_CmdDump(uint8_t argc, uint8_t * argv[]);

#endif /* PRINT_DEMO_H_ */
