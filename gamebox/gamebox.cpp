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

// Keyboard reading task
task_t GB_KeyboardTask(runmode_t RunMode) {
	
	// Variables
	static uint8_t Previous;
	uint8_t Actual = GB_KEY_VPORT.IN;
	
	
	// Normal execution
	if(RunMode == Run) {
		if((Actual & GB_KEY_UP) && !(Previous & GB_KEY_UP)) {
			Print("UP");
		}
		
		if((Actual & GB_KEY_DOWN) && !(Previous & GB_KEY_DOWN)) {
			Print("DOWN");
		}
		
		if((Actual & GB_KEY_LEFT) && !(Previous & GB_KEY_LEFT)) {
			Print("GB_KEY_LEFT");
		}
		
		if((Actual & GB_KEY_RIGHT) && !(Previous & GB_KEY_RIGHT)) {
			Print("GB_KEY_RIGHT");
		}
		
		if((Actual & GP_KEY_OK) && !(Previous & GP_KEY_OK)) {
			Print("GP_KEY_OK");
		}
		
		if((Actual & GB_KEY_ESCAPE) && !(Previous & GB_KEY_ESCAPE)) {
			Print("GB_KEY_ESCAPE");
		}
		
		if((Actual & GB_KEY_A) && !(Previous & GB_KEY_A)) {
			Print("GB_KEY_A");
		}
		
		if((Actual & GB_KEY_B) && !(Previous & GB_KEY_B)) {
			Print("GB_KEY_B");
		}
		
		Previous = Actual;
	}
	
	// Constructor
	else if(RunMode == FirstRun) {
		
	}
	
	// Destructor
	else if(RunMode == Close) {
		
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