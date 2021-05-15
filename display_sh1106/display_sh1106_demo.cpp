#if COMPONENT_DISPLAY_SH1106
#include "display_sh1106_demo.h"
#if SH1106_USE_DEMO_COMMANDS

// Init
void SH1106_CmdInit(uint8_t argc, uint8_t * argv[]) {
	SH1106_Init();
}

// Clear display
void SH1106_CmdClear(uint8_t argc, uint8_t * argv[]) {
	SH1106_Clear();
}

// Draw chessboard
void SH1106_CmdDrawSlash(uint8_t argc, uint8_t * argv[]) {
	SH1106_DrawSlash();
}

#endif
#endif
