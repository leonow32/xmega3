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
void SH1106_CmdFill(uint8_t argc, uint8_t * argv[]);
void SH1106_CmdDrawChessboard(uint8_t argc, uint8_t * argv[]);
void SH1106_CmdDrawSlash(uint8_t argc, uint8_t * argv[]);
void SH1106_CmdContrast(uint8_t argc, uint8_t * argv[]);
void SH1106_CmdPixel(uint8_t argc, uint8_t * argv[]);
void SH1106_CmdLine(uint8_t argc, uint8_t * argv[]);
void SH1106_CmdRectangle(uint8_t argc, uint8_t * argv[]);
void SH1106_CmdRectangleFill(uint8_t argc, uint8_t * argv[]);
void SH1106_CmdDrawCircle(uint8_t argc, uint8_t * argv[]);
void SH1106_CmdCursor(uint8_t argc, uint8_t * argv[]);
void SH1106_CmdText(uint8_t argc, uint8_t * argv[]);
void SH1106_CmdFont(uint8_t argc, uint8_t * argv[]);
void SH1106_CmdBitmap(uint8_t argc, uint8_t * argv[]);

// Animated demos
void SH1106_CmdSnake(uint8_t argc, uint8_t * argv[]);
task_t SH1106_TaskSnake(runmode_t RunMode);
#endif /* DISPLAY_SH1106_DEMO_H_ */
