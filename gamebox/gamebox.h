#if COMPONENT_GAMEBOX
#ifndef GAMEBOX_H_
#define GAMEBOX_H_

// ========================================
// Includes
// ========================================

#include		"gamebox_config.h"
#include		"gamebox_defines.h"

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

void GB_Init(void);

// ========================================
// Keyboard
// ========================================

void GB_KeyboarQueueClear(void);
void GB_KeyboardQueuePush(GB_KeyEvent_t Event);
GB_KeyEvent_t GB_KeyboardQueuePop(void);
void GB_KeyboardCmdShowQueue(uint8_t argc, uint8_t * argv[]);
void GB_KeyboardCmdPopEvent(uint8_t argc, uint8_t * argv[]);
task_t GB_KeyboardTask(runmode_t RunMode);

// ========================================
// Macros
// ========================================



#endif /* GAMEBOX_H_ */
#endif
