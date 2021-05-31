#ifndef DISPLAY_SSD1309_DEMO_H_
#define DISPLAY_SSD1309_DEMO_H_

// ========================================
// Includes
// ========================================

#include		"display_ssd1309.h"

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

void SSD1309_CmdInit(uint8_t argc, uint8_t * argv[]);
void SSD1309_CmdClear(uint8_t argc, uint8_t * argv[]);
void SSD1309_CmdFill(uint8_t argc, uint8_t * argv[]);
void SSD1309_CmdDrawChessboard(uint8_t argc, uint8_t * argv[]);
void SSD1309_CmdDrawSlash(uint8_t argc, uint8_t * argv[]);
void SSD1309_CmdContrast(uint8_t argc, uint8_t * argv[]);
void SSD1309_CmdColor(uint8_t argc, uint8_t * argv[]);
void SSD1309_CmdPixel(uint8_t argc, uint8_t * argv[]);
void SSD1309_CmdLine(uint8_t argc, uint8_t * argv[]);
void SSD1309_CmdRectangle(uint8_t argc, uint8_t * argv[]);
void SSD1309_CmdRectangleFill(uint8_t argc, uint8_t * argv[]);
void SSD1309_CmdDrawCircle(uint8_t argc, uint8_t * argv[]);
void SSD1309_CmdCursor(uint8_t argc, uint8_t * argv[]);
void SSD1309_CmdText(uint8_t argc, uint8_t * argv[]);
void SSD1309_CmdFont(uint8_t argc, uint8_t * argv[]);
void SSD1309_CmdFontDemo(uint8_t argc, uint8_t * argv[]);
void SSD1309_CmdBitmap(uint8_t argc, uint8_t * argv[]);

// Animated demos
void SSD1309_CmdSnake(uint8_t argc, uint8_t * argv[]);
task_t SSD1309_TaskSnake(runmode_t RunMode);
void SSD1309_CmdPixels(uint8_t argc, uint8_t * argv[]);
task_t SSD1309_TaskPixels(runmode_t RunMode);
void SSD1309_CmdFace(uint8_t argc, uint8_t * argv[]);
task_t SSD1309_TaskFace1(runmode_t RunMode);

#if SSD1309_FONT_DOS8x8
	void SSD1309_CmdDemoFontDos8x8(uint8_t argc, uint8_t * argv[]);
#endif

#if SSD1309_FONT_DOS16x8
	void SSD1309_CmdDemoFontDos16x8(uint8_t argc, uint8_t * argv[]);
#endif

// Benchmark
void SSD1309_CmdCircles(uint8_t argc, uint8_t * argv[]);


#endif /* DISPLAY_SSD1309_DEMO_H_ */
