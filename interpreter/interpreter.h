/*


CHANGELOG
0.00	+	Pocz¹tki
		
REQUIREMENTS
		-	Print
		-	UART
*/

#ifndef INTERPRETER_H_
#define INTERPRETER_H_
#if C_INTERPRETER

#include <avr/io.h>
#include <string.h>
#include "interpreter_config.h"

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

//  Result type
enum Interpreter_Res_t {
	Interpreter_OK = 0,													// Zwracane przez wszystkie funkcje, je¿eli zakoñczy³y siê prawid³owo
	Interpreter_ReceivedCommand,										// Console_UartInput() - odebrano pe³ne polecenie gotowe do dalszej analizy
	Interpreter_BufferFull,												// Console_UartInput() - przepe³nienie bufora
	Interpreter_InputCancelled,											// Console_UartInput() - wciœniêto ESC, trzeba wyœwietliæ ponownie znak zachêty wiersza poleceñ
	Interpreter_NotReady,								// Zwracane przez Command_LineInput(), kiedy nie podano znaku ENTER
	Interpreter_UnknownCommand,							// Zwracane przez Command_Interpreter(), kiedy nie rozpozna polecenia
	Interpreter_NoInput,
	Interpreter_MissingArgument,
	Interpreter_Overflow,
	Interpreter_Underflow,
	Interpreter_ParseError,
	Interpreter_ExpectedHex,
	Interpreter_ExpectedDec,
	Interpreter_ReceivedACK,							// Zwracane przez Command_Interpreter(), kiedy zostanie otrzymane potwierdzenie odebrania polecenia z po³¹czonego uk³adu
	Interpreter_ReceivedNAK,							// Zwracane przez Command_Interpreter(), kiedy NIE zostanie otrzymane potwierdzenie odebrania polecenia z po³¹czonego uk³adu
	Interpreter_ErrorToFix = 255,										// Tylko do celów deweloperskich, normalnie ¿adna funkcja nie powinna zwracaæ czegoœ takiego
};

// Struct with command buffers
struct Interpreter_Struct {
	uint16_t			ReceivedCnt;							// Aktualna liczba znaków w tablicy Buffer
	uint8_t 			Buffer[INTERPRETER_COMMAND_LENGTH];		// Buffer for currently processed command
	uint8_t				Buffer2[INTERPRETER_COMMAND_LENGTH];	// Buffer for last processed command, recalled with CTRL-Z
};

// Struct used to build table of commands and pointers to specified functions
struct Interpreter_NamePointer_t {
	const char *Name;
	void (*Pointer)(uint8_t argc, uint8_t * argv[]);
};

// Command list
extern const Interpreter_NamePointer_t	Interpreter_CommandList[];


// Functions

void	Interpreter_Init(void);
task_t	Interpreter_Task(runmode_t RunMode);


void Interpreter_PromptShow(void);
void Interpreter_BufferFlush(void);

// Interpretowanie danych
void		Console_Debug(const Interpreter_Res_t Result, const uint8_t * Argument);

Interpreter_Res_t	Parse_Hex8(const uint8_t * Argument, uint8_t * Output);
Interpreter_Res_t	Parse_Hex16(const uint8_t * Argument, uint16_t * Output);
Interpreter_Res_t	Parse_Hex32(const uint8_t * Argument, uint32_t * Output);
Interpreter_Res_t	Parse_Hex64(const uint8_t * Argument, uint64_t * Output);
Interpreter_Res_t	Parse_HexString(const uint8_t * InputString, uint8_t * OutputString, uint8_t * OutputLength, const uint8_t MaxLength = 255, const uint8_t MinLength = 0);

Interpreter_Res_t	Parse_AsciiString(const uint8_t * InputString, uint8_t * OutputString, uint8_t * OutputLength, const uint8_t MaxLength = 255, const uint8_t MinLength = 0);

Interpreter_Res_t	Parse_Dec8(const uint8_t * Argument, uint8_t * Output, const uint8_t MaxValue = 255);
Interpreter_Res_t	Parse_Dec16(const uint8_t * Argument, uint16_t * Output, const uint16_t MaxValue = 65535);
Interpreter_Res_t	Parse_Dec32(const uint8_t * Argument, uint32_t * Output, const uint32_t MaxValue = 4294967295UL);
Interpreter_Res_t	Parse_Dec64(const uint8_t * Argument, uint64_t * Output, const uint64_t MaxValue = 18446744073709551615UL);
Interpreter_Res_t	Parse_Dec32S(const uint8_t * Argument, int32_t * Output); //, const int32_t MaxValue = 268435455L);

#endif
#endif /* INTERPRETER_H_ */
