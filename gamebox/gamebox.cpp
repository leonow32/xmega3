#if COMPONENT_GAMEBOX

// ========================================
// Includes
// ========================================

#include	"gamebox.h"

// ========================================
// Global variables
// ========================================



// ========================================
// Functions
// ========================================

void GB_Init(void) {
	
	GB_KEY_PORT.DIR		=	GB_KEY_UP |
							GB_KEY_DOWN |
							GB_KEY_LEFT |
							GB_KEY_RIGHT |
							GP_KEY_OK|
							GB_KEY_ESCAPE |
							GB_KEY_A |
							GB_KEY_B;
	
// 	for(register8_t * Pointer = &GB_KEY_PORT.PIN0CTRL; Pointer > &GB_KEY_PORT.PIN7CTRL; Pointer++) {
// 		*Pointer = PORT_PULLUPEN_bm | PORT_ISC_INTDISABLE_gc;
// 	}
	
	GB_KEY_PORT.PIN0CTRL = PORT_INVEN_bm | PORT_PULLUPEN_bm | PORT_ISC_INTDISABLE_gc;
	GB_KEY_PORT.PIN1CTRL = PORT_INVEN_bm | PORT_PULLUPEN_bm | PORT_ISC_INTDISABLE_gc;
	GB_KEY_PORT.PIN2CTRL = PORT_INVEN_bm | PORT_PULLUPEN_bm | PORT_ISC_INTDISABLE_gc;
	GB_KEY_PORT.PIN3CTRL = PORT_INVEN_bm | PORT_PULLUPEN_bm | PORT_ISC_INTDISABLE_gc;
	GB_KEY_PORT.PIN4CTRL = PORT_INVEN_bm | PORT_PULLUPEN_bm | PORT_ISC_INTDISABLE_gc;
	GB_KEY_PORT.PIN5CTRL = PORT_INVEN_bm | PORT_PULLUPEN_bm | PORT_ISC_INTDISABLE_gc;
	GB_KEY_PORT.PIN6CTRL = PORT_INVEN_bm | PORT_PULLUPEN_bm | PORT_ISC_INTDISABLE_gc;
	GB_KEY_PORT.PIN7CTRL = PORT_INVEN_bm | PORT_PULLUPEN_bm | PORT_ISC_INTDISABLE_gc;
	
	TaskAdd(GB_KeyboardTask, TaskMsToTicks(10));
}

// ========================================
// Keyboard
// ========================================

volatile GB_KeyEvent_t GB_KeyQueue[GB_KEY_QUEUE_LENGTH];

// Clear queue
void GB_KeyboarQueueClear(void) {
	for(uint8_t i = 0; i < GB_KEY_QUEUE_LENGTH; i++) {
		GB_KeyQueue[i] = GB_None;
	}
}

// Add event to the queue
void GB_KeyboardQueuePush(GB_KeyEvent_t Event) {
	for(uint8_t i = 0; i < GB_KEY_QUEUE_LENGTH; i++) {
		if(GB_KeyQueue[i] == GB_None) {
			GB_KeyQueue[i] = Event;
			return;
		}
	}
	
	Print("Queue full");
}

// Get event from the queue
GB_KeyEvent_t GB_KeyboardQueuePop(void) {
	GB_KeyEvent_t Result = GB_KeyQueue[0];
	for(uint8_t i = 0; i < GB_KEY_QUEUE_LENGTH-1; i++) {
		GB_KeyQueue[i] = GB_KeyQueue[i+1];
	}
	GB_KeyQueue[GB_KEY_QUEUE_LENGTH-1] = GB_None;
	return Result;
}

// Print all events in the queue
void GB_KeyboardCmdShowQueue(uint8_t argc, uint8_t * argv[]) {
	for(uint8_t i = 0; i < GB_KEY_QUEUE_LENGTH; i++) {
		Print_Dec(i);
		Print('\t');
		Print_Hex(uint8_t(GB_KeyQueue[i]));
		Print_NL();
	}
}

// Debug - pop event from queue and print
void GB_KeyboardCmdPopEvent(uint8_t argc, uint8_t * argv[]) {
	Print_Hex(uint8_t(GB_KeyboardQueuePop()));
}

// Keyboard reading task
task_t GB_KeyboardTask(runmode_t RunMode) {
	
	// Variables
	static uint8_t Previous;
	uint8_t Actual = GB_KEY_VPORT.IN;
	
	// Normal execution
	if(RunMode == Run) {
		if((Actual & GB_KEY_UP) && !(Previous & GB_KEY_UP)) {
			Print("UP");
			GB_KeyboardQueuePush(GB_KeyUpPress);
		}
		
		if((Actual & GB_KEY_DOWN) && !(Previous & GB_KEY_DOWN)) {
			Print("DOWN");
			GB_KeyboardQueuePush(GB_KeyDownPress);
		}
		
		if((Actual & GB_KEY_LEFT) && !(Previous & GB_KEY_LEFT)) {
			Print("GB_KEY_LEFT");
			GB_KeyboardQueuePush(GB_KeyLeftPress);
		}
		
		if((Actual & GB_KEY_RIGHT) && !(Previous & GB_KEY_RIGHT)) {
			Print("GB_KEY_RIGHT");
			GB_KeyboardQueuePush(GB_KeyRightPress);
		}
		
		if((Actual & GP_KEY_OK) && !(Previous & GP_KEY_OK)) {
			Print("GP_KEY_OK");
			GB_KeyboardQueuePush(GB_KeyOKPress);
		}
		
		if((Actual & GB_KEY_ESCAPE) && !(Previous & GB_KEY_ESCAPE)) {
			Print("GB_KEY_ESCAPE");
			GB_KeyboardQueuePush(GB_KeyEscapePress);
		}
		
		if((Actual & GB_KEY_A) && !(Previous & GB_KEY_A)) {
			Print("GB_KEY_A");
			GB_KeyboardQueuePush(GB_KeyAPress);
		}
		
		if((Actual & GB_KEY_B) && !(Previous & GB_KEY_B)) {
			Print("GB_KEY_B");
			GB_KeyboardQueuePush(GB_KeyBPress);
		}
		
		Previous = Actual;
	}
	
	// Constructor
	else if(RunMode == FirstRun) {
		GB_KeyboarQueueClear();
	}
	
	// Destructor
	else if(RunMode == Close) {
		GB_KeyboarQueueClear();
	}
	
	// Identification
	#if OS_USE_TASK_IDENTIFY
	else if(RunMode == Identify) {
		Print("GB_Key");
	}
	#endif
	
	return TaskOK;
}

#endif