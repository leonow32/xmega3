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

// Struct with command buffers
struct Interpreter_Struct {
	uint16_t			ReceivedCnt;							// Aktualna liczba znaków w tablicy Buffer
	uint8_t 			Buffer[INTERPRETER_COMMAND_LENGTH];		// Buffer for currently processed command
	uint8_t				Buffer2[INTERPRETER_COMMAND_LENGTH];	// Buffer for last processed command, recalled with CTRL-Z
};

// Struct used to build table of commands and pointers to specified functions
struct Interpreter_NamePointer_t {
	const char *Name;
	void	(*Pointer)(uint8_t argc, uint8_t * argv[]);
};

// Command list
extern const Interpreter_NamePointer_t	Interpreter_CommandList[];


// Functions

void	Interpreter_Init(void);
task_t	Interpreter_Task(runmode_t RunMode);


void Interpreter_PromptShow(void);
void Interpreter_BufferFlush(void);

#endif
#endif /* INTERPRETER_H_ */
