/*


CHANGELOG
0.00	+	Pocz¹tki
		
REQUIREMENTS
		-	Print
		-	UART
*/

#ifndef CONSOLE_H_
#define CONSOLE_H_
#if C_CONSOLE

#include <avr/io.h>
#include <string.h>
#include "console_config.h"

#include "../common/ascii.h"

#if C_UCOSMOS
	#include	"../uCosmos/uCosmos.h"
#else 
	#error		"Component CONSOLE requires uCSOMOS" 
#endif

#if C_PRINT
	#include	"../print/print.h"
#else
	#error		"This module requires PRINT component"
#endif

//  Result type for command interpreter
enum Console_t {
	Console_OK = 0,													// Zwracane przez wszystkie funkcje, je¿eli zakoñczy³y siê prawid³owo
	Console_ReceivedCommand,										// Console_UartInput() - odebrano pe³ne polecenie gotowe do dalszej analizy
	Console_BufferFull,												// Console_UartInput() - przepe³nienie bufora
	Console_InputCancelled,											// Console_UartInput() - wciœniêto ESC, trzeba wyœwietliæ ponownie znak zachêty wiersza poleceñ
	Console_ErrorToFix = 255,										// Tylko do celów deweloperskich, normalnie ¿adna funkcja nie powinna zwracaæ czegoœ takiego
};

// Result type for argument parser
enum Parse_t {
	Parse_OK = 0,									// Zwracane przez wszystkie funkcje, je¿eli zakoñczy³y siê prawid³owo
	Parse_NotReady,								// Zwracane przez Command_LineInput(), kiedy nie podano znaku ENTER
	Parse_UnknownCommand,							// Zwracane przez Command_Interpreter(), kiedy nie rozpozna polecenia
	Parse_NoInput,
	Parse_MissingArgument,
	Parse_Overflow,
	Parse_Underflow,
	Parse_ParseError,
	Parse_ExpectedHex,
	Parse_ExpectedDec,
	Parse_ReceivedACK,							// Zwracane przez Command_Interpreter(), kiedy zostanie otrzymane potwierdzenie odebrania polecenia z po³¹czonego uk³adu
	Parse_ReceivedNAK,							// Zwracane przez Command_Interpreter(), kiedy NIE zostanie otrzymane potwierdzenie odebrania polecenia z po³¹czonego uk³adu
};

// Struct with command buffers
struct Console_Struct {
	uint16_t			ReceivedCnt;							// Aktualna liczba znaków w tablicy Buffer
	uint8_t 			Buffer[CONSOLE_COMMAND_LENGTH];		// Buffer for currently processed command
	uint8_t				Buffer2[CONSOLE_COMMAND_LENGTH];	// Buffer for last processed command, recalled with CTRL-Z
};

// Struct used to build table of commands and pointers to specified functions
struct Console_NamePointer_t {
	const char *Name;
	void (*Pointer)(uint8_t argc, uint8_t * argv[]);
};

// Command list
extern const Console_NamePointer_t	Console_CommandList[];


// Command line interpreter

void		Console_Init(void);
task_t		Console_Task(runmode_t RunMode);
void		Console_PromptShow(void);
void		Console_BufferFlush(void);

// Argument parsers
void		Parse_Debug(const Parse_t Result, const uint8_t * Argument);
Parse_t		Parse_Hex8(const uint8_t * Argument, uint8_t * Output);
Parse_t		Parse_Hex16(const uint8_t * Argument, uint16_t * Output);
Parse_t		Parse_Hex32(const uint8_t * Argument, uint32_t * Output);
Parse_t		Parse_Hex64(const uint8_t * Argument, uint64_t * Output);

Parse_t		Parse_Dec8(const uint8_t * Argument, uint8_t * Output, const uint8_t MaxValue = 255);
Parse_t		Parse_Dec16(const uint8_t * Argument, uint16_t * Output, const uint16_t MaxValue = 65535);
Parse_t		Parse_Dec32(const uint8_t * Argument, uint32_t * Output, const uint32_t MaxValue = 4294967295UL);
Parse_t		Parse_Dec64(const uint8_t * Argument, uint64_t * Output, const uint64_t MaxValue = 18446744073709551615UL);
Parse_t		Parse_Dec32S(const uint8_t * Argument, int32_t * Output); //, const int32_t MaxValue = 268435455L);

Parse_t		Parse_HexString(const uint8_t * InputString, uint8_t * OutputString, uint8_t * OutputLength, const uint8_t MaxLength = 255, const uint8_t MinLength = 0);
Parse_t		Parse_AsciiString(const uint8_t * InputString, uint8_t * OutputString, uint8_t * OutputLength, const uint8_t MaxLength = 255, const uint8_t MinLength = 0);



#endif
#endif /* CONSOLE_H_ */
