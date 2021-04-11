#ifndef INTERPRETER_COMMANDS_H_
#define INTERPRETER_COMMANDS_H_

// ========================================
// Includes
// ========================================

#include		"console.h"

#if COMPONENT_CONSOLE
	#include	"../console/console_demo.h"
#endif

#if COMPONENT_EEPROM
	#include	"../eeprom/eeprom_demo.h"
#endif

#if COMPONENT_I2C_MASTER
	#include	"../i2c_master/i2c_master_demo.h"
#endif

#if COMPONENT_MCP9808
	#include	"../mcp9808/mcp9808_demo.h"
#endif

#if COMPONENT_MEM25
	#include	"../mem25/mem25_demo.h"
#endif

#if COMPONENT_PRINT
	#include	"../print/print_demo.h"
#endif

#if COMPONENT_SPI_MASTER
	#include	"../spi_master/spi_master_demo.h"
#endif

#if COMPONENT_UART_MONITOR
	#include	"../uart_monitor/uart_monitor.h"
#endif

#if COMPONENT_UCOSMOS
	#include	"../uCosmos/uCosmos.h"
#endif

// ========================================
// Command names and function pointers
// ========================================

const Console_NamePointer_t Console_CommandList[] = {

// ========================================
// Console demo
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
	{"ascchr",			Console_CmdAsciiCharacter},
#endif

// ========================================
// Internal EEPROM demo
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
// I2C Master demo
// ========================================

#if I2C_MASTER_USE_DEMO_COMMANDS
	{"i2c",				I2C_CmdTransmit},
	{"i2c-scan",		I2C_CmdScan},
#endif

// ========================================
// MCP9808 demo
// ========================================

#if MCP9808_USE_DEMO_COMMANDS
	{"mcp9808",			MCP9808_CmdTemperature},
	{"mcp9808-r",		MCP9808_CmdRead},
	{"mcp9808-w",		MCP9808_CmdWrite},
	{"mcp9808-dump",	MCP9808_CmdDump},
#endif

// ========================================
// MEM25 demo
// ========================================

#if MEM25_USE_DEMO_COMMANDS
	{"mem25-r",			Mem25_CmdRead},
	{"mem25-dump",		Mem25_CmdDump},
	{"mem25-s",			Mem25_CmdStatus},
	{"mem25-we",		Mem25_CmdWriteEnableDisable},
#endif

// ========================================
// Print demo
// ========================================

#if PRINT_USE_DEMO_COMMANDS
	{"color",			Print_CmdColor},
	{"ascii",			Print_CmdAscii},
	{"dump",			Print_CmdDump},
#endif

// ========================================
// SPI Master demo
// ========================================

#if SPI_MASTER_USE_DEMO_COMMANDS
	{"spi",					Spi_CmdTransmit},
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

// ========================================
// UART Monitor
// ========================================

#if COMPONENT_UART_MONITOR
	{"uart-h",			UartMonitor_CmdSendHex},
	{"uart-a",			UartMonitor_CmdSendAscii},
#endif

};

#endif /* INTERPRETER_COMMANDS_H_ */

