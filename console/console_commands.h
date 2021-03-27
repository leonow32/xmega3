#ifndef INTERPRETER_COMMANDS_H_
#define INTERPRETER_COMMANDS_H_

#include	"console.h"

#if C_UCOSMOS
	#include	"../uCosmos/uCosmos.h"
#endif

// Tablica wszystkich poleceń obsługiwanych przez interpreter
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