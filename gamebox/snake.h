#if COMPONENT_GAMEBOX
#ifndef SNAKE_H_
#define SNAKE_H_

// ========================================
// Includes
// ========================================

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

void Snake_CmdRun(uint8_t argc, uint8_t * argv[]);
void Snake_DrawCanvas(void);
void Snake_DrawBlock(uint8_t x, uint8_t y, Snake_BlockColor_t Color);
void Snake_CmdDrawBlock(uint8_t argc, uint8_t * argv[]);

void Snake_NewFood(void);
void Snake_CmdNewFood(uint8_t argc, uint8_t * argv[]);

// ========================================
// Tasks
// ========================================

task_t Snake_MainTask(runmode_t RunMode);

#endif /* SNAKE_H_ */
#endif
