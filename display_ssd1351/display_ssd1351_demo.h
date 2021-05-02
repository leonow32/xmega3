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

void SSD1351_CmdClear(uint8_t argc, uint8_t * argv[]);
void SSD1351_CmdDrawChessboard(uint8_t argc, uint8_t * argv[]);
void SSD1351_CmdContrast(uint8_t argc, uint8_t * argv[]);
void SSD1351_CmdDrawPixel(uint8_t argc, uint8_t * argv[]);
void SSD1351_CmdDrawLine(uint8_t argc, uint8_t * argv[]);
void SSD1351_CmdDrawRectangle(uint8_t argc, uint8_t * argv[]);
void SSD1351_CmdDrawRectangleFill(uint8_t argc, uint8_t * argv[]);
void SSD1351_CmdDrawCircle(uint8_t argc, uint8_t * argv[]);
void SSD1351_CmdCursor(uint8_t argc, uint8_t * argv[]);
#endif /* DISPLAY_SSD1351_DEMO_H_ */
