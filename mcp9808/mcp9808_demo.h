#ifndef MCP9808_COMMANDS_H_
#define MCP9808_COMMANDS_H_

// ========================================
// Includes
// ========================================

#include		"mcp9808.h"

#if COMPONENT_I2C_MASTER
	#include		"../i2c_master/i2c_master.h"
#else
	#error		"This module requires I2C_MASTER component"
#endif

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

// ========================================
// Console Commands
// ========================================

void MCP9808_CmdRead(uint8_t argc, uint8_t * argv[]);
void MCP9808_CmdWrite(uint8_t argc, uint8_t * argv[]);
void MCP9808_CmdDump(uint8_t argc, uint8_t * argv[]);
void MCP9808_CmdTemperature(uint8_t argc, uint8_t * argv[]);

#endif /* MCP9808_COMMANDS_H_ */