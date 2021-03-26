#ifndef INTERPRETER_COMMANDS_H_
#define INTERPRETER_COMMANDS_H_

#include	"console.h"

#if C_UCOSMOS
	#include	"../uCosmos/uCosmos.h"
#endif

// Tablica wszystkich poleceñ obs³ugiwanych przez interpreter
const Console_NamePointer_t Console_CommandList[] = {

// ========================================
// Console demo commands
// ========================================

#if CONSOLE_USE_COMMAND_ALL
	{"all",				Console_All},
#endif

#if CONSOLE_USE_DEMO_COMMANDS
	{"args",			Console_Args},
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
	
	//	{"lr",				Test_LongReply},
	//	{"echo",			DemoCmd_Echo},
};

#endif /* INTERPRETER_COMMANDS_H_ */