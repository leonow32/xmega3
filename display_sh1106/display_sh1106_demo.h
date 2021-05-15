#ifndef DISPLAY_SH1106_DEMO_H_
#define DISPLAY_SH1106_DEMO_H_

// ========================================
// Includes
// ========================================

#include		"display_sh1106.h"

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

#if COMPONENT_PRINT
	#include	"../uCosmos/uCosmos.h"
#else
	#error		"This module requires uCOSMOS component"
#endif

// ========================================
// Basic commands
// ========================================

void SH1106_CmdInit(uint8_t argc, uint8_t * argv[]);
void SH1106_CmdClear(uint8_t argc, uint8_t * argv[]);
void SH1106_CmdDrawSlash(uint8_t argc, uint8_t * argv[]);



#endif /* DISPLAY_SH1106_DEMO_H_ */
