#ifndef INTERPRETER_COMMANDS_H_
#define INTERPRETER_COMMANDS_H_

// ========================================
// Includes
// ========================================

#include		"console.h"

#if COMPONENT_CONSOLE
	#include	"../console/console_demo.h"
#endif

#if COMPONENT_DISPLAY_SH1106
	#include	"../display_sh1106/display_sh1106_demo.h"
#endif

#if COMPONENT_DISPLAY_SSD1351
	#include	"../display_ssd1351/display_ssd1351_demo.h"
#endif

#if COMPONENT_DISPLAY_SSD1681
	#include	"../display_ssd1681/display_ssd1681_demo.h"
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
// Display SH1106 demo
// ========================================

#if SH1106_USE_DEMO_COMMANDS
	{"init",			SH1106_CmdInit},
	{"clr",				SH1106_CmdClear},
	{"fill",			SH1106_CmdFill},
	{"slash",			SH1106_CmdDrawSlash},
	{"chess",			SH1106_CmdDrawChessboard},
 	{"cont",			SH1106_CmdContrast},
 	{"pix",				SH1106_CmdPixel},
 	{"lin",				SH1106_CmdLine},
 	{"rec",				SH1106_CmdRectangle},
 	{"recf",			SH1106_CmdRectangleFill},
 	{"cir",				SH1106_CmdDrawCircle},
 	{"cur",				SH1106_CmdCursor},
 	{"color",			SH1106_CmdColor},
	{"txt",				SH1106_CmdText},
	{"font",			SH1106_CmdFont},
	{"fonts",			SH1106_CmdFontDemo},
	
	// Font demos
	#if SH1106_FONT_DOS8x8
		{"dos8",		SH1106_CmdDemoFontDos8x8},
	#endif
	
	#if SH1106_FONT_DOS16x8
		{"dos16",		SH1106_CmdDemoFontDos16x8},
	#endif
	
	// Bitmaps
	{"bitmap",			SH1106_CmdBitmap},
	
	// Animated demos
	{"snake",			SH1106_CmdSnake},
	{"pixels",			SH1106_CmdPixels},
	{"face",			SH1106_CmdFace},
	
	// Benchmark
	{"circles",			SH1106_CmdCircles},
#endif

// ========================================
// Display SSD1351 demo
// ========================================

#if SSD1351_USE_DEMO_COMMANDS
	{"clr",				SSD1351_CmdClear},
	{"chess",			SSD1351_CmdDrawChessboard},
	{"cont",			SSD1351_CmdContrast},
	{"pix",				SSD1351_CmdPixel},
	{"lin",				SSD1351_CmdLine},
	{"rec",				SSD1351_CmdRectangle},
	{"recf",			SSD1351_CmdRectangleFill},
	{"cir",				SSD1351_CmdDrawCircle},
	{"cur",				SSD1351_CmdCursor},
	{"cf",				SSD1351_CmdColorFront},
	{"cb",				SSD1351_CmdColorBack},
	{"txt",				SSD1351_CmdText},
	{"font",			SSD1351_CmdFont},
	
	// Font demos
	#if SSD1351_FONT_DOS8x8
		{"dos8",		SSD1351_CmdDemoFontDos8x8},
	#endif
	
	#if SSD1351_FONT_DOS16x8
		{"dos16",		SSD1351_CmdDemoFontDos16x8},
	#endif
	
	{"rainbow",			SSD1351_CmdDemoColorPalette},
	{"fonts",			SSD1351_CmDDemoFontTest},
	{"align",			SSD1351_CmdDemoTextAlign},
	
	// Bitmaps
	{"bitmap",			SSD1351_CmdBitmap},
	
	// Animated demos
	{"snake",			SSD1351_CmdSnake},
	
	#if SSD1351_FONT_DOS8x8 || SSD1351_FONT_DOS16x8
		{"face",		SSD1351_CmdFace},
	#endif
#endif

// ========================================
// Display SSD1681 demo
// ========================================

#if SSD1681_USE_DEMO_COMMANDS
	{"cmd",				SSD1681_CmdCommand},
	{"data",			SSD1681_CmdData},
	{"init",			SSD1681_CmdInit},
	{"r",				SSD1681_CmdRefresh},
	{"clr",				SSD1681_CmdClear},
	{"fill",			SSD1681_CmdFill},
	{"chess",			SSD1681_CmdChessboard},
	
	{"cur",				SSD1681_CmdCursor},
	{"area",			SSD1681_CmdActiveArea},
	
	{"color",			SSD1681_CmdColor},
	
	{"pix",				SSD1681_CmdPixel},
	{"lin",				SSD1681_CmdLine},
	{"rec",				SSD1681_CmdRectangle},
	{"recf",			SSD1681_CmdRectangleFill},
	{"cir",				SSD1681_CmdDrawCircle},
	
	{"test",			SSD1681_CmdTest},
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

