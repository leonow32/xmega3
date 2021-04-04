// Version 2.0.0

#include "peripherals.h"


// ========================================
// Dev Board AVR-IoT
// ========================================

#if P_AVRIOT

void Peripherals_Init(void) {
	
	// LED diodes
	LED_RED_INIT;
	LED_YELLOW_INIT;
	LED_GREEN_INIT;
	LED_BLUE_INIT;
	
	// Buttons
	KEY_SW0_INIT;
	KEY_SW1_INIT;
	
	// Piny IO
	PWM_INIT;
	INT_INIT;
	
}


#if PERIPHERALS_USE_DEMO_TASKS
// Demonstration task to blink LEDs
task_t Peripherals_TaskRed(runmode_t RunMode) {
	
	// Call mode
	switch(RunMode) {
		
		// Identification
		#if OS_USE_TASK_IDENTIFY
		case Identify:
			Print("LedR");
			return TaskOK;
		#endif
	
		// Normal execution
		default:
			LED_RED_TGL;
			return TaskOK;
	}

	return TaskOK;
}


// Demonstration task to blink LEDs
task_t Peripherals_TaskYellow(runmode_t RunMode) {
	
	// Call mode
	switch(RunMode) {
		
		// Identification
		#if OS_USE_TASK_IDENTIFY
		case Identify:
			Print("LedY");
			return TaskOK;
		#endif
	
		// Normal execution
		default:
			LED_YELLOW_TGL;
			return TaskOK;
	}
	
	return TaskOK;
}


// Demonstration task to blink LEDs
task_t Peripherals_TaskGreen(runmode_t RunMode) {
	
	// Call mode
	switch(RunMode) {
		
		// Identification
		#if OS_USE_TASK_IDENTIFY
		case Identify:
			Print("LedG");
			return TaskOK;
		#endif
	
		// Normal execution
		default:
			LED_GREEN_TGL;
			return TaskOK;
	}
	
	return TaskOK;
}


// Demonstration task to blink LEDs
task_t Peripherals_TaskBlue(runmode_t RunMode) {
	
	// Call mode
	switch(RunMode) {
		
		// Identification
		#if OS_USE_TASK_IDENTIFY
		case Identify:
			Print("LedB");
			return TaskOK;
		#endif
	
		// Normal execution
		default:
			LED_BLUE_TGL;
			return TaskOK;
	}
	
	return TaskOK;
} 
#endif


#if PERIPHERALS_USE_DEMO_COMMANDS
// Setting of GPIOs
void Peripherals_Demo_ioset(uint8_t argc, uint8_t * argv[]) {
	
	if(argc == 1) {
		Print("ioset peripheral[ASC1] state[0/1]");
		return;
	}
	
	switch(*argv[1]) {
		case 'r':		if(*argv[2] == '1')		{LED_RED_ON;}				else 	LED_RED_OFF;	break;
		case 'y':		if(*argv[2] == '1')		{LED_YELLOW_ON;}			else 	LED_YELLOW_OFF;	break;
		case 'g':		if(*argv[2] == '1')		{LED_GREEN_ON;}				else 	LED_GREEN_OFF;	break;
		case 'b':		if(*argv[2] == '1')		{LED_BLUE_ON;}				else 	LED_BLUE_OFF;	break;
		case 'i':		if(*argv[2] == '1')		{INT_ON;}					else 	INT_OFF;		break;
		case 'p':		if(*argv[2] == '1')		{PWM_ON;}					else 	PWM_OFF;		break;
		default:		Print("Wrong arg");															return;
	}
}


// Reading GPIOs
void Peripherals_Demo_ioget(uint8_t argc, uint8_t * argv[]) {
	
	Print("SW0\t=\t");
	Print(KEY_SW0_READ ? '1' : '0');
	
	Print("\r\nSW1\t=\t");
	Print(KEY_SW1_READ ? '1' : '0');
}

#endif
#endif


// ========================================
// Dev Board Curiosity ATmega4809
// ========================================

#if P_CURIOSITY_M4809
void Peripherals_Init(void) {
	
	// LED diodes
	LED_YELLOW_INIT;
	
	// Buttons
	KEY_SW0_INIT;
}

#if PERIPHERALS_USE_DEMO_TASKS
// Demonstration task to blink LEDs
task_t Peripherals_TaskYellow(runmode_t RunMode) {

	// Call mode
	switch(RunMode) {
		
		// Identification
		#if OS_USE_TASK_IDENTIFY
		case Identify:
			Print("LedY");
			return TaskOK;
		#endif
	
		// Normal execution
		default:
			LED_YELLOW_TGL;
			return TaskOK;
	}
	
	return TaskOK;
} 
#endif


#if PERIPHERALS_USE_DEMO_COMMANDS
// Setting of GPIOs
void Peripherals_Demo_ioset(uint8_t argc, uint8_t * argv[]) {
	
	if(argc == 1) {
		Print("ioset peripheral[ASC1] state[0/1]");
		return;
	}
	
	switch(*argv[1]) {
		case 'y':		if(*argv[2] == '1')		{LED_YELLOW_ON;}			else 	LED_YELLOW_OFF;	break;
		default:		Print("Wrong arg");															return;
	}
}


// Reading GPIOs
void Peripherals_Demo_ioget(uint8_t argc, uint8_t * argv[]) {
	Print("SW0\t=\t");
	Print(KEY_SW0_READ ? '1' : '0');
}

#endif
#endif


// ========================================
// Dev Board XNANO
// ========================================


#if P_XNANO

void Peripherals_Init(void) {
	
	// LED diodes
	LED_YELLOW_INIT;
	
	// Buttons
	KEY_SW0_INIT;
}

#if PERIPHERALS_USE_DEMO_TASKS
// Demonstration task to blink LEDs
task_t Peripherals_TaskYellow(runmode_t RunMode) {
	
	// Call mode
	switch(RunMode) {
		
		// Identification
		#if OS_USE_TASK_IDENTIFY
		case Identify:
			Print("LedY");
			return TaskOK;
		#endif
	
		// Normal execution
		default:
			LED_YELLOW_TGL;
			return TaskOK;
	}
	
	return TaskOK;
} 
#endif


#if PERIPHERALS_USE_DEMO_COMMANDS
// Setting of GPIOs
void Peripherals_Demo_ioset(uint8_t argc, uint8_t * argv[]) {
	
	if(argc == 1) {
		Print("ioset peripheral[ASC1] state[0/1]");
		return;
	}
	
	switch(*argv[1]) {
		case 'y':		if(*argv[2] == '1')		{LED_YELLOW_ON;}			else 	LED_YELLOW_OFF;	break;
		default:		Print("Wrong arg");															return;
	}
}


// Reading GPIOs
void Peripherals_Demo_ioget(uint8_t argc, uint8_t * argv[]) {
	Print("SW0\t=\t");
	Print(KEY_SW0_READ ? '1' : '0');
}

#endif

#endif