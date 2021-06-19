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

void GB_SnakeCmdRun(uint8_t argc, uint8_t * argv[]);
void GB_SnakeCanvas(void);
void GB_SnakeDrawBlock(uint8_t x, uint8_t y, GB_SnakeBlockColor_t Color);
void GB_SnakeCmdDrawBlock(uint8_t argc, uint8_t * argv[]);

void GB_SnakeCmdNewFood(uint8_t argc, uint8_t * argv[]);
// ========================================
// Tasks
// ========================================

task_t GB_SnakeTask(runmode_t RunMode);

#endif /* SNAKE_H_ */
#endif
