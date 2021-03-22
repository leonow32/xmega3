// Wersja 0.01

#if C_INTERPRETER

#include "interpreter.h"

// Command list
#include "interpreter_commands.h"

Interpreter_Struct Inter;


// Initialization
void Interpreter_Init(void) {
	TaskAdd(Interpreter_Task, 0);
}


// System task to periodicaly execute interpreter routine
task_t Interpreter_Task(runmode_t RunMode) {
	
	// Normaln execution
	if(RunMode == Run) {
		//Console_TaskHandler(&Os_Console);
	}
	
	// Constructor
	else if(RunMode == FirstRun) {
		
		//memset(&Os_Console, 0, sizeof(Os_Console));  
		//Os_Console.UartInstance = &OS_CONSOLE_UART_INSTANCE;
		//Console_PromptShow(&Os_Console);						// !! zrobiæ coœ, ¿eby prompt nie pokazywa³ siê w trakcie wysy³ania komunikatu o utworzeniu tasku
	}
	
	// Destructor
	else if(RunMode == Close) {
	}
	
	// Identification
	#if OS_USE_TASK_IDENTIFY
	else if(RunMode == Identify) {
		Print("Interpreter");
	}
	#endif
	
	return TaskOK;
}


// Display command line prompt
void Interpreter_PromptShow(void) {
	Print("\r\n > ");
}


//
//
//

// Clean all buffers
void Interpreter_BufferFlush(void) {
	memset(&Inter, 0, sizeof(Inter));
};

#endif
