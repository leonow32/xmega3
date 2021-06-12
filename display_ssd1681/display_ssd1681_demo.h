#ifndef DISPLAY_SSD1681_DEMO_H_
#define DISPLAY_SSD1681_DEMO_H_

// ========================================
// Includes
// ========================================

#include		"display_ssd1681.h"

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

void SSD1681_CmdCommand(uint8_t argc, uint8_t * argv[]);
void SSD1681_CmdData(uint8_t argc, uint8_t * argv[]);
void SSD1681_CmdInit(uint8_t argc, uint8_t * argv[]);
void SSD1681_CmdRefresh(uint8_t argc, uint8_t * argv[]);
void SSD1681_CmdTest(uint8_t argc, uint8_t * argv[]);
void SSD1681_CmdClear(uint8_t argc, uint8_t * argv[]);
void SSD1681_CmdFill(uint8_t argc, uint8_t * argv[]);
void SSD1681_CmdChessboard(uint8_t argc, uint8_t * argv[]);
void SSD1681_CmdCursor(uint8_t argc, uint8_t * argv[]);
void SSD1681_CmdActiveArea(uint8_t argc, uint8_t * argv[]);

// ========================================
// Colors
// ========================================

void SSD1681_CmdColor(uint8_t argc, uint8_t * argv[]);
void SSD1681_CmdPixel(uint8_t argc, uint8_t * argv[]);
void SSD1681_CmdLine(uint8_t argc, uint8_t * argv[]);
void SSD1681_CmdRectangle(uint8_t argc, uint8_t * argv[]);
void SSD1681_CmdRectangleFill(uint8_t argc, uint8_t * argv[]);
void SSD1681_CmdDrawCircle(uint8_t argc, uint8_t * argv[]);

// ========================================
// Bitmaps
// ========================================

void SSD1681_CmdBitmap(uint8_t argc, uint8_t * argv[]);

// ========================================
// Fonts and text
// ========================================

void SSD1681_CmdText(uint8_t argc, uint8_t * argv[]);
void SSD1681_CmdFont(uint8_t argc, uint8_t * argv[]);
void SSD1681_CmdFontDemo(uint8_t argc, uint8_t * argv[]);

#if SSD1681_FONT_DOS8x8
	void SSD1681_CmdDemoFontDos8x8(uint8_t argc, uint8_t * argv[]);
#endif

#if SSD1681_FONT_DOS16x8
	void SSD1681_CmdDemoFontDos16x8(uint8_t argc, uint8_t * argv[]);
#endif

#endif /* DISPLAY_SSD1681_DEMO_H_ */
