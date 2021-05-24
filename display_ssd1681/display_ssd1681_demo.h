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

// void SSD1681_CmdContrast(uint8_t argc, uint8_t * argv[]);
// void SSD1681_CmdPixel(uint8_t argc, uint8_t * argv[]);
// void SSD1681_CmdLine(uint8_t argc, uint8_t * argv[]);
// void SSD1681_CmdRectangle(uint8_t argc, uint8_t * argv[]);
// void SSD1681_CmdRectangleFill(uint8_t argc, uint8_t * argv[]);
// void SSD1681_CmdDrawCircle(uint8_t argc, uint8_t * argv[]);
// 
// void SSD1681_CmdColorFront(uint8_t argc, uint8_t * argv[]);
// void SSD1681_CmdColorBack(uint8_t argc, uint8_t * argv[]);

// ========================================
// Fonts and text
// ========================================

// void SSD1681_CmdText(uint8_t argc, uint8_t * argv[]);
// void SSD1681_CmdFont(uint8_t argc, uint8_t * argv[]);
// void SSD1681_CmDDemoFontTest(uint8_t argc, uint8_t * argv[]);
// void SSD1681_CmdDemoTextAlign(uint8_t argc, uint8_t * argv[]);
// void SSD1681_CmdDemoColorPalette(uint8_t argc, uint8_t * argv[]);
// 
// #if SSD1681_FONT_DOS8x8
// 	void SSD1681_CmdDemoFontDos8x8(uint8_t argc, uint8_t * argv[]);
// #endif
// 
// #if SSD1681_FONT_DOS16x8
// 	void SSD1681_CmdDemoFontDos16x8(uint8_t argc, uint8_t * argv[]);
// #endif

// ========================================
// Bitmaps
// ========================================

//void SSD1681_CmdBitmap(uint8_t argc, uint8_t * argv[]);

// ========================================
// Animated demos
// ========================================

// void SSD1681_CmdSnake(uint8_t argc, uint8_t * argv[]);
// task_t SSD1681_TaskSnake(runmode_t RunMode);
// 
// #if SSD1681_FONT_DOS8x8 || SSD1681_FONT_DOS16x8
// 	void SSD1681_CmdFace(uint8_t argc, uint8_t * argv[]);
// #endif
// 
// #if SSD1681_FONT_DOS8x8
// 	task_t SSD1681_TaskFace1(runmode_t RunMode);
// 	task_t SSD1681_TaskFace2(runmode_t RunMode);
// #endif
// 
// #if SSD1681_FONT_DOS16x8
// 	task_t SSD1681_TaskFace3(runmode_t RunMode);
// 	task_t SSD1681_TaskFace4(runmode_t RunMode);
// #endif

#endif /* DISPLAY_SSD1681_DEMO_H_ */
