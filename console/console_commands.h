#ifndef INTERPRETER_COMMANDS_H_
#define INTERPRETER_COMMANDS_H_

#include	"console.h"

#if C_UCOSMOS
	#include	"../uCosmos/uCosmos.h"
#endif

// Tablica wszystkich poleceñ obs³ugiwanych przez interpreter
const Console_NamePointer_t Console_CommandList[] = {

// Systemowe
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