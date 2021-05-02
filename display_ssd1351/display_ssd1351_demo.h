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
void SSD1351_CmdPixel(uint8_t argc, uint8_t * argv[]);
void SSD1351_CmdLine(uint8_t argc, uint8_t * argv[]);
void SSD1351_CmdRectangle(uint8_t argc, uint8_t * argv[]);
void SSD1351_CmdRectangleFill(uint8_t argc, uint8_t * argv[]);
void SSD1351_CmdDrawCircle(uint8_t argc, uint8_t * argv[]);
void SSD1351_CmdCursor(uint8_t argc, uint8_t * argv[]);
void SSD1351_CmdColorFront(uint8_t argc, uint8_t * argv[]);
void SSD1351_CmdColorBack(uint8_t argc, uint8_t * argv[]);
void SSD1351_CmdText(uint8_t argc, uint8_t * argv[]);
#endif /* DISPLAY_SSD1351_DEMO_H_ */
