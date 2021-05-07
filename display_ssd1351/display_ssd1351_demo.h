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

#if COMPONENT_PRINT
	#include	"../uCosmos/uCosmos.h"
#else
	#error		"This module requires uCOSMOS component"
#endif

// ========================================
// Basic commands
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

// ========================================
// Fonts and text
// ========================================

void SSD1351_CmdText(uint8_t argc, uint8_t * argv[]);
void SSD1351_CmdFont(uint8_t argc, uint8_t * argv[]);
void SSD1351_CmdDemoFontDos8x8(uint8_t argc, uint8_t * argv[]);
void SSD1351_CmDDemoFontTest(uint8_t argc, uint8_t * argv[]);
void SSD1351_CmdDemoTextAlign(uint8_t argc, uint8_t * argv[]);
void SSD1351_CmdDemoFontDos16x8(uint8_t argc, uint8_t * argv[]);
void SSD1351_CmdDemoColorPalette(uint8_t argc, uint8_t * argv[]);

// ========================================
// Bitmaps
// ========================================

void SSD1351_CmdBitmap(uint8_t argc, uint8_t * argv[]);

// ========================================
// Animated demos
// ========================================
void SSD1351_CmdSnake(uint8_t argc, uint8_t * argv[]);
task_t SSD1351_TaskSnake(runmode_t RunMode);
void SSD1351_CmdFace(uint8_t argc, uint8_t * argv[]);
task_t SSD1351_TaskFace1(runmode_t RunMode);
task_t SSD1351_TaskFace2(runmode_t RunMode);
task_t SSD1351_TaskFace3(runmode_t RunMode);
task_t SSD1351_TaskFace4(runmode_t RunMode);
#endif /* DISPLAY_SSD1351_DEMO_H_ */
