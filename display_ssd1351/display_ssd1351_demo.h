#ifndef DISPLAY_SSD1351_DEMO_H_
#define DISPLAY_SSD1351_DEMO_H_

// ========================================
// Includes
// ========================================

#include		"display_ssd1351.h"

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



#endif /* DISPLAY_SSD1351_DEMO_H_ */