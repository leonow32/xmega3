#ifndef INTERPRETER_COMMANDS_H_
#define INTERPRETER_COMMANDS_H_

// ========================================
// Includes
// ========================================

#include		"console.h"

#if C_CONSOLE
	#include	"../console/console_demo.h"
#endif

#if C_EEPROM
	#include	"../eeprom/eeprom_demo.h"
#endif

#if C_I2C_MASTER
	#include	"../i2c_master/i2c_master_demo.h"
#endif

#if C_MCP9808
	#include	"../mcp9808/mcp9808_demo.h"
#endif

#if C_PRINT
	#include	"../print/print_demo.h"
#endif

#if C_UCOSMOS
	#include	"../uCosmos/uCosmos.h"
#endif

// ========================================
// Command names and function pointers
// ========================================

const Console_NamePointer_t Console_CommandList[] = {

// ========================================
// Console demo commands
// ========================================

#if CONSOLE_USE_COMMAND_ALL
	{"all",				Console_CmdAll},
#endif

#if CONSOLE_USE_DEMO_COMMANDS
	{"args",			Console_CmdArgs},
	{"echo",			Console_CmdEcho},
	{"hex8",			Console_CmdHex8},
	{"hex16",			Console_CmdHex16},
	{"hex32",			Console_CmdHex32},
	{"dec8",			Console_CmdDec8},
	{"dec16",			Console_CmdDec16},
	{"dec32",			Console_CmdDec32},
	{"hexstr",			Console_CmdHexString},
	{"ascstr",			Console_CmdAsciiString},
#endif

// ========================================
// Internal EEPROM demo commands
// ========================================

#if EEPROM_USE_COMMAND_DUMP
	{"ee",				EEPROM_Demo_Dump},
#endif

#if EEPROM_USE_DEMO_COMMANDS
	{"ee-r",			EEPROM_Demo_ReadByte},
	{"ee-rs",			EEPROM_Demo_ReadString},
	{"ee-w",			EEPROM_Demo_WriteByte},
	{"ee-ws",			EEPROM_Demo_WriteString},
	{"ee-er",			EEPROM_Demo_Erase},
	{"ee-fill",			EEPROM_Demo_Fill},
#endif

// ========================================
// I2C master demo commands
// ========================================

#if I2C_MASTER_USE_DEMO_COMMANDS
	{"i2c",				I2C_CmdTransmit},
	{"i2c-scan",		I2C_CmdScan},
#endif

// ========================================
// MCP9808 demo commands
// ========================================

#if MCP9808_USE_DEMO_COMMANDS
	{"mcp9808",			MCP9808_CmdTemperature},
	{"mcp9808-r",		MCP9808_CmdRead},
	{"mcp9808-w",		MCP9808_CmdWrite},
	{"mcp9808-dump",	MCP9808_CmdDump},
#endif

// ========================================
// Print demo commands
// ========================================

#if PRINT_USE_DEMO_COMMANDS
	{"color",			Print_CmdColor},
	{"ascii",			Print_CmdAscii},
#endif

// ========================================
// System AVR uCosmos
// ========================================

#if OS_TASK_MONITOR_USE
	{"`",				Os_Monitor},
#endif

#if OS_USE_TIME_COMMAND && OS_USE_TIME
	{"time",			Os_TimePrint},
#endif	

	{"reset",			Os_ResetExecute},
};

#endif /* INTERPRETER_COMMANDS_H_ */
