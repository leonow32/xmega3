#if COMPONENT_GAMEBOX
#ifndef SNAKE_H_
#define SNAKE_H_

// ========================================
// Includes
// ========================================

#include <avr/io.h>
#include <stdlib.h>
#include "snake_defines.h"
#include "snake_config.h"

#if COMPONENT_CONSOLE
	#include	"../console/console.h"
#else
	#error		"This module requires COMPONENT_CONSOLE"
#endif

#if COMPONENT_DISPLAY_SSD1351
	#include	"../display_ssd1351/display_ssd1351.h"
#else
	#error		"This module requires COMPONENT_DISPLAY_SSD1351"
#endif

#if COMPONENT_GAMEBOX
	#include	"gamebox.h"
#else
	#error		"This module requires COMPONENT_GAMEBOX"
#endif

#if COMPONENT_PRINT
	#include	"../print/print.h"
#else
	#error		"This module requires COMPONENT_PRINT"
#endif

#if COMPONENT_UCOSMOS
	#include	"../uCosmos/uCosmos.h"
#else
	#error		"This module requires COMPONENT_UCOSMOS"
#endif

// ========================================
// Functions
// ========================================

void Snake_GenerateRandomPoint(Snake_Point * Point);
bool Snake_ComparePoints(Snake_Point * Point1, Snake_Point * Point2);
void Snake_DrawCanvas(void);
void Snake_DrawBlock(Snake_Point * Point, Snake_BlockColor_t Color);
void Snake_NewFood(void);

// ========================================
// Tasks
// ========================================

task_t Snake_MainTask(runmode_t RunMode);

// ========================================
// Debug
// ========================================

void Snake_CmdRun(uint8_t argc, uint8_t * argv[]);
void Snake_CmdPrintStruct(uint8_t argc, uint8_t * argv[]);
void Snake_CmdDrawBlock(uint8_t argc, uint8_t * argv[]);
void Snake_CmdNewFood(uint8_t argc, uint8_t * argv[]);

#endif /* SNAKE_H_ */
#endif
