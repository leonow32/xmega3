#ifndef INTERPRETER_COMMANDS_H_
#define INTERPRETER_COMMANDS_H_

// ========================================
// Includes
// ========================================

#include		"console.h"

#if COMPONENT_CONSOLE
	#include	"../console/console_demo.h"
#endif

#if COMPONENT_DISPLAY_SSD1351
	#include	"../display_ssd1351/display_ssd1351_demo.h"
#endif

#if COMPONENT_DS3231
	#include	"../ds3231/ds3231_demo.h"
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

#if COMPONENT_MEM23
	#include	"../mem23/mem23_demo.h"
#endif

#if COMPONENT_MEM24
	#include	"../mem24/mem24_demo.h"
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
// Display SSD1350 demo
// ========================================

#if SSD1351_USE_DEMO_COMMANDS
	{"d-clr",			SSD1351_CmdClear},
	{"d-chess",			SSD1351_CmdDrawChessboard},
	{"d-cont",			SSD1351_CmdContrast},
	{"d-pix",			SSD1351_CmdPixel},
	{"d-lin",			SSD1351_CmdLine},
	{"d-rec",			SSD1351_CmdRectangle},
	{"d-recf",			SSD1351_CmdRectangleFill},
	{"d-cir",			SSD1351_CmdDrawCircle},
	{"d-cur",			SSD1351_CmdCursor},
	{"d-cf",			SSD1351_CmdColorFront},
	{"d-cb",			SSD1351_CmdColorBack},
	{"d-t",				SSD1351_CmdText},
	{"d-f",				SSD1351_CmdFont},
	
	// Font demos
	#if SSD1351_FONT_DOS8x8
		{"d-dos8",		SSD1351_CmdDemoFontDos8x8},
	#endif
	
	#if SSD1351_FONT_DOS16x8
		{"d-dos16",		SSD1351_CmdDemoFontDos16x8},
	#endif
	
	{"d-rainbow",		SSD1351_CmdDemoColorPalette},
	{"d-fonts",			SSD1351_CmDDemoFontTest},
	{"d-align",			SSD1351_CmdDemoTextAlign},
	
	// Bitmaps
	{"d-b",				SSD1351_CmdBitmap},
	
	// Animated demos
	{"d-snake",			SSD1351_CmdSnake},
	
	#if SSD1351_FONT_DOS8x8 || SSD1351_FONT_DOS16x8
		{"d-face",		SSD1351_CmdFace},
	#endif
#endif

// ========================================
// DS3231 demo
// ========================================

#if DS3231_USE_DEMO_COMMANDS
	{"ds3231",			DS3231_CmdRead},
	{"ds3231-w",		DS3231_CmdWrite},
#endif

// ========================================
// Internal EEPROM demo
// ========================================

#if EEPROM_USE_COMMAND_DUMP
	{"ee",				EEPROM_Demo_Dump},
#endif

#if EEPROM_USE_DEMO_COMMANDS
	{"ee-w",			EEPROM_CmdWrite},
	{"ee-E",			EEPROM_CmdErase},
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
// MEM23 demo (SPI RAM)
// ========================================

#if MEM23_USE_DEMO_COMMANDS
	{"mem23",			Mem23_CmdDump},
	{"mem23-s",			Mem23_CmdStatus},
	{"mem23-r",			Mem23_CmdRead},
	{"mem23-w",			Mem23_CmdWrite},
#endif

// ========================================
// MEM24 demo (I2C EEPROM)
// ========================================

#if MEM24_USE_DEMO_COMMANDS
	{"mem24",			Mem24_CmdDump},
	{"mem24-r",			Mem24_CmdRead},
	{"mem24-w",			Mem24_CmdWrite},
#endif

// ========================================
// MEM25 demo (SPI EEPROM)
// ========================================

#if MEM25_USE_DEMO_COMMANDS
	{"mem25",			Mem25_CmdDump},
	{"mem25-id",		Mem25_CmdGetID},
	{"mem25-s",			Mem25_CmdStatus},
	{"mem25-sleep",		Mem25_CmdSleep},
	{"mem25-wake",		Mem25_CmdWake},
	{"mem25-r",			Mem25_CmdRead},
	{"mem25-w",			Mem25_CmdWrite},
	{"mem25-we",		Mem25_CmdWriteEnable},
	{"mem25-wd",		Mem25_CmdWriteDisable},
	{"mem25-E",			Mem25_CmdChipErase},
#endif

// ========================================
// Print demo
// ========================================

#if PRINT_USE_DEMO_COMMANDS
	{"color",			Print_CmdColor},
	{"ascii",			Print_CmdAscii},
	{"dump",			Print_CmdDump},
	{"timet",			Print_CmdTimet},
	{"times",			Print_CmdTimes},
#endif

// ========================================
// SPI Master demo
// ========================================

#if SPI_MASTER_USE_DEMO_COMMANDS
	{"spi",				Spi_CmdTransmit},
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
	{"uart",			UartMonitor_CmdSend},
#endif

};

#endif /* INTERPRETER_COMMANDS_H_ */

