/*
CHANGELOG
1.0.0		Comments translated to English
		
HARDWARE
		-	UART
*/

#ifndef PRINT_H_
#define PRINT_H_

#if C_PRINT

#include "print_config.h"
#include "../common/ascii.h"

// Includes
#if C_UART_SINGLE
	#include	"../uart/uart_single.h"
#elif C_UART_MULTI
	#include	"../uart/uart_multi.h"
#else
	#error		"This module requires UART component"
#endif

// ANSI format codes
enum PrintFormat_t {
	FormatReset = 0,
	FormatBold = 1,
	FormatFaint = 2,
	FormatItalic = 3,
	FormatUnderline = 4,
	FormatBlinkSlow = 5,
	FormatBlinkFast = 6,
	ForegroundBlack = 30,
	ForegroundRed = 31,
	ForegroundGreen = 32,
	ForegroundYellow = 33,
	ForegroundBlue = 34,
	ForegroundMagenta = 35,
	ForegroundCyan = 36,
	ForegroundWhite = 37,
	BackgroundBlack = 40,
	BackgroundRed = 41,
	BackgroundGreen = 42,
	BackgroundYellow = 43,
	BackgroundBlue = 44,
	BackgroundMagenta = 45,
	BackgroundCyan = 46,
	BackgroundWhite = 47,
	ForegroundBlackBright = 90,
	ForegroundRedBright = 91,
	ForegroundGreenBright = 92,
	ForegroundYellowBright = 93,
	ForegroundBlueBright = 94,
	ForegroundMagentaBright = 95,
	ForegroundCyanBright = 96,
	ForegroundWhiteBright = 97,
	BackgroundBlackBright = 100,
	BackgroundRedBright = 101,
	BackgroundGreenBright = 102,
	BackgroundYellowBright = 103,
	BackgroundBlueBright = 104,
	BackgroundMagentaBright = 105,
	BackgroundCyanBright = 106,
	BackgroundWhiteBright = 107,
};

// Set output stream pointer. If NULL then set to default (see config)
void Print_SetStream(void (*NewPrintPointer)(const uint8_t Data) = NULL);

// Functions to print various types of data
void Print(const uint8_t Data);
void Print(const char * Text);
void Print_NL(void);
void Print_Dec(uint32_t Value);
void Print_DecSigned(int32_t Value);
void Print_Bin(uint8_t Data, const uint8_t Separator = 0);
void Print_Hex(const uint8_t Data, const uint8_t Separator = 0);
void Print_Hex(const uint16_t Data, const uint8_t Separator = 0);
void Print_Hex(const uint32_t Data, const uint8_t Separator = 0);
void Print_HexString(const uint8_t * String, const uint16_t Length, const uint8_t Separator = 0, const uint8_t BytesInRow = 16);
void Print_Dump(const uint8_t * String, uint16_t Length);

// Chane text format, bolt, italic, underline, color of foreground and background (https://en.wikipedia.org/wiki/ANSI_escape_code)
void Print_Format(PrintFormat_t Code);

#endif /* C_PRINT */
#endif /* PRINT_H_ */

