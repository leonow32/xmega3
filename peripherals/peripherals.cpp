// Wersja 1.18

#include "peripherals.h"


// =======
// AVR-IoT 
// =======


#if B_AVRIOT

void Peripherals_Init(void) {
	
	// Diody LED
	LED_RED_INIT;
	LED_YELLOW_INIT;
	LED_GREEN_INIT;
	LED_BLUE_INIT;

	// Przyciski
	KEY_SW0_INIT;
	KEY_SW1_INIT;

	// Piny IO
	PWM_INIT;
	INT_INIT;
	
}

// ==========================
// PERIPHERALS_USE_DEMO_TASKS
// ==========================

#if PERIPHERALS_USE_DEMO_TASKS
// Task demonstracyjny do mrugania diodami
task_t Peripherals_TaskRed(runmode_t RunMode) {

	// Tryb wywo³ania
	switch(RunMode) {
		
		// Wywo³anie identyfikacyjne
		#if OS_USE_TASK_IDENTIFY
		case Identify:
			Uart_Write("LedR");
			return TaskOK;
		#endif

		// Normalne wywo³anie przez Scheduler
		default:
			LED_RED_TGL;
			return TaskOK;
	}

	return TaskOK;
} 


// Task demonstracyjny do mrugania diodami
task_t Peripherals_TaskYellow(runmode_t RunMode) {

	// Tryb wywo³ania
	switch(RunMode) {
		
		// Wywo³anie identyfikacyjne
		#if OS_USE_TASK_IDENTIFY
		case Identify:
			Uart_Write("LedY");
			return TaskOK;
		#endif

		// Normalne wywo³anie przez Scheduler
		default:
			LED_YELLOW_TGL;
			return TaskOK;
	}

	return TaskOK;
} 


// Task demonstracyjny do mrugania diodami
task_t Peripherals_TaskGreen(runmode_t RunMode) {

	// Tryb wywo³ania
	switch(RunMode) {
		
		// Wywo³anie identyfikacyjne
		#if OS_USE_TASK_IDENTIFY
		case Identify:
			Uart_Write("LedG");
			return TaskOK;
		#endif

		// Normalne wywo³anie przez Scheduler
		default:
			LED_GREEN_TGL;
			return TaskOK;
	}

	return TaskOK;
} 


// Task demonstracyjny do mrugania diodami
task_t Peripherals_TaskBlue(runmode_t RunMode) {

	// Tryb wywo³ania
	switch(RunMode) {
		
		// Wywo³anie identyfikacyjne
		#if OS_USE_TASK_IDENTIFY
		case Identify:
			Uart_Write("LedB");
			return TaskOK;
		#endif

		// Normalne wywo³anie przez Scheduler
		default:
			LED_BLUE_TGL;
			return TaskOK;
	}

	return TaskOK;
} 
#endif


// =============================
// PERIPHERALS_USE_DEMO_COMMANDS
// =============================


#if PERIPHERALS_USE_DEMO_COMMANDS
// Ustawienie pinów wyjœciowych
void Peripherals_Demo_ioset(uint8_t argc, uint8_t * argv[]) {
	
	if(argc == 1) {
		Uart_Write("ioset peripheral[ASC1] state[0/1]");
		return;
	}
	
	switch(*argv[1]) {
		case 'r':		if(*argv[2] == '1')		{LED_RED_ON;}				else 	LED_RED_OFF;	break;
		case 'y':		if(*argv[2] == '1')		{LED_YELLOW_ON;}			else 	LED_YELLOW_OFF;	break;
		case 'g':		if(*argv[2] == '1')		{LED_GREEN_ON;}				else 	LED_GREEN_OFF;	break;
		case 'b':		if(*argv[2] == '1')		{LED_BLUE_ON;}				else 	LED_BLUE_OFF;	break;
		case 'i':		if(*argv[2] == '1')		{INT_ON;}					else 	INT_OFF;		break;
		case 'p':		if(*argv[2] == '1')		{PWM_ON;}					else 	PWM_OFF;		break;
		default:		Uart_Write("Wrong arg");													return;
	}
}


// Odczytanie stanu pinów
void Peripherals_Demo_ioget(uint8_t argc, uint8_t * argv[]) {
	
	Uart_Write("SW0\t=\t");
	Uart_Write(KEY_SW0_READ ? '1' : '0');
	
	Uart_Write("\r\nSW1\t=\t");
	Uart_Write(KEY_SW1_READ ? '1' : '0');
}


// Testowe odbijanie pierwszego argumentu
void Peripherals_Echo(uint8_t argc, uint8_t * argv[]) {
	Uart_Write((const char *)argv[1]);
}
#endif
#endif

// =====
// XNANO
// =====


#if B_XNANO

void Peripherals_Init(void) {
	
	// Diody LED
	LED_YELLOW_INIT;
	
	// Przyciski
	KEY_SW0_INIT;
}

// ==========================
// PERIPHERALS_USE_DEMO_TASKS
// ==========================

#if PERIPHERALS_USE_DEMO_TASKS
// Task demonstracyjny do mrugania diodami
task_t Peripherals_TaskYellow(runmode_t RunMode) {

	// Tryb wywo³ania
	switch(RunMode) {
		
		// Wywo³anie identyfikacyjne
		#if OS_USE_TASK_IDENTIFY
		case Identify:
			Uart_Write("LedY");
			return TaskOK;
		#endif

		// Normalne wywo³anie przez Scheduler
		default:
			LED_YELLOW_TGL;
			return TaskOK;
	}

	return TaskOK;
} 
#endif


// =============================
// PERIPHERALS_USE_DEMO_COMMANDS
// =============================


#if PERIPHERALS_USE_DEMO_COMMANDS
// Ustawienie pinów wyjœciowych
void Peripherals_Demo_ioset(uint8_t argc, uint8_t * argv[]) {
	
	if(argc == 1) {
		Uart_Write("ioset peripheral[ASC1] state[0/1]");
		return;
	}
	
	switch(*argv[1]) {
		case 'y':		if(*argv[2] == '1')		{LED_YELLOW_ON;}			else 	LED_YELLOW_OFF;	break;
		default:		Uart_Write("Wrong arg");													return;
	}
}


// Odczytanie stanu pinów
void Peripherals_Demo_ioget(uint8_t argc, uint8_t * argv[]) {
	Uart_Write("SW0\t=\t");
	Uart_Write(KEY_SW0_READ ? '1' : '0');
}


// Testowe odbijanie pierwszego argumentu
void Peripherals_Echo(uint8_t argc, uint8_t * argv[]) {
	Uart_Write((const char *)argv[1]);
}
#endif

#endif