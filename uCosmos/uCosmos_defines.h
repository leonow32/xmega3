// Wersja 1.16

#ifndef UCOSMOS_DEFINES_H_
#define UCOSMOS_DEFINES_H_

#include	<avr/io.h>
#include	<avr/interrupt.h>
#include	"uCosmos_config.h"


// Wynik zwracany przez task
enum task_t {
	TaskOK = 0,
	TaskDone,
	TaskError,
};


// Rodzaj wywo³ania tasku, przekazywany jako argument
enum runmode_t {
	Run = 0,
	FirstRun,
	Close,
	#if OS_USE_TASK_IDENTIFY
		Identify,
	#endif
};


// Wynik zwracany przez funkcje, kodu b³êdów, itp
enum os_t {
	OsOK = 0,									// Funkcja zakoñczy³a siê prawid³owo
	OsError,									// Bli¿ej nieokreœlony b³¹d
	OsNoFreeSlot,								// Brak wolnych slotów
	OsNotFound,									// Os__FindTask(), TaskPeriodChange(), nie znaleziono tasku
	OsMultipleFound,							// Os__FindTask(), TaskClose(), znaleziono wiêcej ni¿ jedno wyst¹pienie tasku
	OsCloseNotConfirmed,						// TaskClose(), task nie chce siê zamkn¹æ
	OsTaskAlreadyCreated,						// TaskAdd(), próba utworzenia tego samego tasku po raz drugi
	OsSlotNumberOverRange,						// TaskKill(), podano numer slotu wiêkszy ni¿ dopuszczalny
	OsTaskDoneWhenFirstRun,						// TaskAdd(), task sam siê zakoñczy³ podczas wywo³ania konstruktora
	OsTaskErrorWhenFirstRun,					// TaskAdd(), task zwróci³ wartoœæ error podczas wywo³ania konstruktora
};


// Status walidacji
enum os_valid_t {
	Os_Invalid	= 0xF0,							// Brak walidacji
	Os_Valid	= 0x55,							// Jest walidacja
};


// Struktura definicji tasku
typedef struct _TaskControlBlock {
	task_t (*TaskPtr)(runmode_t);				// WskaŸnik do procesu
	Os_Timer_t Counter;							// Timer tasku
	Os_Timer_t Period;							// Okres wywo³ywania tasku
	uint8_t Pending;							// Iloœæ zaleg³ych wywo³añ do wykonania

	// Diagnostyka czasu, jest 1/32768 sekundy, w Os_Monitor jest to przeliczane na us przez Os__DebugConvertTicksToMicroseconds()
	#if OS_TASK_MONITOR_MIN_MAX
		uint16_t	TimeMax;					
		uint16_t	TimeMin;
	#endif

	#if OS_TASK_MONITOR_AVG_PROC
		uint16_t	TimeAvg;
	#endif
} TaskControlBlock_t;

#define			OS_RUN_EVERY_CYCLE		255


// Tryb uœpienia
#if OS_USE_SLEEP
 #define		OS_SLEEP_DISABLE		if(OS_SLEEP_GPIOR != 255)	{OS_SLEEP_GPIOR++;}
 #define		OS_SLEEP_ENABLE			if(OS_SLEEP_GPIOR)			{OS_SLEEP_GPIOR--;}
#endif


// Definicja u³atwiaj¹ca tworzenie tasków - automatycznie przelicza czas na ticki systemowe
#define			TaskAddMs(TaskPtr, Period)	TaskAdd(TaskPtr, Os_Timer_t(Period / OS_TICK_DELAY), 0, NULL)
#define			TaskAddSec(TaskPtr, Period)	TaskAdd(TaskPtr, Os_Timer_t(Period * 1000 / OS_TICK_DELAY), 0, NULL)
#define			TaskAddMin(TaskPtr, Period)	TaskAdd(TaskPtr, Os_Timer_t(Period * 60000 / OS_TICK_DELAY), 0, NULL)

#endif /* UCOSMOS_DEFINES_H_ */