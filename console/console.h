#ifndef CONSOLE_H_
#define CONSOLE_H_
#if COMPONENT_CONSOLE

#include		<time.h>
#include		<avr/io.h>
#include		<string.h>
#include		"console_config.h"
#include		"../common/ascii.h"

#if COMPONENT_UCOSMOS
	#include	"../uCosmos/uCosmos.h"
#else 
	#error		"Component CONSOLE requires uCSOMOS" 
#endif

#if COMPONENT_PRINT
	#include	"../print/print.h"
#else
	#error		"This module requires PRINT component"
#endif

//  Result type for command interpreter
enum Console_t {
	Console_OK = 0,													// Zwracane przez wszystkie funkcje, je?eli zako?czy?y si? prawid?owo
	Console_ReceivedCommand,										// Console_UartInput() - odebrano pe?ne polecenie gotowe do dalszej analizy
	Console_BufferFull,												// Console_UartInput() - przepe?nienie bufora
	Console_InputCancelled,											// Console_UartInput() - wci?ni?to ESC, trzeba wy?wietli? ponownie znak zach?ty wiersza polece?
	Console_ErrorToFix = 255,										// Tylko do cel?w deweloperskich, normalnie ?adna funkcja nie powinna zwraca? czego? takiego
};

// Result type for argument parser
enum Parse_t {
	Parse_OK = 0,									// Zwracane przez wszystkie funkcje, je?eli zako?czy?y si? prawid?owo
	Parse_UnknownCommand,							// Zwracane przez Command_Interpreter(), kiedy nie rozpozna polecenia
	Parse_NoInput,
	Parse_MissingArgument,
	Parse_Overflow,
	Parse_Underflow,
	Parse_ParseError,
	Parse_ExpectedHex,
	Parse_ExpectedDec,
};

// Struct with command buffers
struct Console_Struct {
	uint16_t			ReceivedCnt;							// Aktualna liczba znak?w w tablicy Buffer
	uint8_t 			Buffer[CONSOLE_COMMAND_LENGTH];		// Buffer for currently processed command
	#if CONSOLE_USE_CTRL_Z
		uint8_t			Buffer2[CONSOLE_COMMAND_LENGTH];	// Buffer for last processed command, recalled with CTRL-Z
	#endif
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
Parse_t		Parse_Dec8(const uint8_t * Argument, uint8_t * Output, const uint8_t MaxValue = 255);
Parse_t		Parse_Dec16(const uint8_t * Argument, uint16_t * Output, const uint16_t MaxValue = 65535);
Parse_t		Parse_Dec32(const uint8_t * Argument, uint32_t * Output, const uint32_t MaxValue = 4294967295UL);
Parse_t		Parse_Dec32S(const uint8_t * Argument, int32_t * Output); //, const int32_t MaxValue = 268435455L);
Parse_t		Parse_HexString(const uint8_t * InputString, uint8_t * OutputString, uint8_t * OutputLength, const uint8_t MaxLength = 255, const uint8_t MinLength = 0);
Parse_t		Parse_AsciiString(const uint8_t * InputString, uint8_t * OutputString, uint8_t * OutputLength, const uint8_t MaxLength = 255, const uint8_t MinLength = 0);
Parse_t		Parse_AsciiCharacter(const uint8_t * Argument, uint8_t * Output);
Parse_t		Parse_Time(const uint8_t * Argument, time_t * Output);

// Demo commands
#if CONSOLE_USE_COMMAND_ALL
	void	Console_CmdAll(uint8_t argc, uint8_t * argv[]);
#endif



#endif
#endif /* CONSOLE_H_ */
