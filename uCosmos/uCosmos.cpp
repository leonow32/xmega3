// Wersja 1.18

#if COMPONENT_UCOSMOS

#include "../config/config.h"
#include "uCosmos_defines.h"
#include "uCosmos_config.h"
#include "uCosmos.h"

#if C_LOG
	#include "log.h"
#endif

// Task table
static volatile TaskControlBlock_t Task[OS_TASK_MAXCOUNT];

// Globals
volatile uint8_t Os_Ticks = 0;

// CSystem time
#if OS_USE_TIME
	volatile time_t Os_Time = 0;
#endif

#if OS_USE_SLEEP
	volatile OS_SLEEP_TIMER_TYPE Os_SleepTimer = 0;
#endif

#if (OS_TASK_MONITOR_MIN_MAX || OS_TASK_MONITOR_AVG_PROC) && OS_TASK_MONITOR_USE
	volatile uint8_t Os_DebugTimer = 0;
#endif

#if OS_TASK_MONITOR_TASKMAXCNT
	uint8_t Os_DebugMaxTaskCnt;
#endif


// ===================
// Zarz¹dzanie taskami
// ===================


// Incijalizacja systemu i zegara RTC
void Os_Init(void) {

	// Jeœli wybrano generator kwarcowy 32kHz
	#if OS_GENERATOR_XOSC32
		CCP						=	CCP_IOREG_gc;					// Odblokowanie chronionych rejestrow
		CLKCTRL.XOSC32KCTRLA	=	CLKCTRL_CLKSEL_XOSC32K_gc|		// Wybór kwarc 32kHz (mo¿na wybraæ jeszcze Ÿród³o sygna³u prostok¹tnego)
 									CLKCTRL_CSUT_1K_gc |			// Czas rozruchu
									CLKCTRL_RUNSTDBY_bm |			// Dzia³aj podczas uœpienia
 									CLKCTRL_ENABLE_bm;				// W³¹cz
		RTC.CLKSEL				=	RTC_CLKSEL_TOSC32K_gc;	
	#endif
	
	// Jeœli wybrano generator ULP
	#if OS_GENERATOR_ULP
		RTC.CLKSEL				=	RTC_CLKSEL_INT32K_gc;			// Taktowanie zegarem ULP 
	#endif
	
	// Konfiguracja RTC do Tickera systemowego
	RTC.INTFLAGS				=	RTC_OVF_bm;						// Kasowanie flagi przerwania
	RTC.PER						=	(OS_TICK_DELAY * 32768 / 1000);	// Okres timera systemowego
	RTC.CNT						=	0;								// Zerowanie lciznika RTC
	while(RTC.STATUS);												// Oczekiwanie na synchronizacjê rejestrów CNT i PER z zegarem asynchronicznym
	RTC.INTCTRL					=	RTC_OVF_bm;						// W³¹czenie przerwanie tylko od overflow
	RTC.CTRLA					=	RTC_RUNSTDBY_bm |				// Mo¿e dzia³aæ w standby
									RTC_PRESCALER_DIV1_gc |			// Przeskaler 1, czyli taktowanie 32768
									RTC_RTCEN_bm;					// W³¹czenie RTC
	
	// Konfiguracja PIT do zegara czasu - przerwanie dok³adnie co 1 sekundê
	#if OS_USE_TIME
		RTC.PITCTRLA			=	RTC_PITEN_bm |					// Periodic Interrupt Timer Enable
									RTC_PERIOD_CYC32768_gc;			// Preskaler 32768 czyli przerwanie bêdzie generowane co 1 sekundê	
		RTC.PITINTCTRL			=	RTC_PI_bm;						// Periodic interrupt is enabled
	#endif
	
	// Inicjalizacja tablicy tasków
	for(uint8_t i=0; i<OS_TASK_MAXCOUNT; i++) {
		TaskClear(i);
	}
	
	// Watchdog
	#if OS_USE_WATCHDOG
		CCP						=	CCP_IOREG_gc;					// Odblokowanie chronionych rejestrow
		WDT.CTRLA				=	WDT_PERIOD_1KCLK_gc;
		while(WDT.STATUS & WDT_SYNCBUSY_bm);
	#endif
	
	// Przerwania
	CPUINT.CTRLA |=	CPUINT_LVL0RR_bm;			// Algorytm round-robin dla przerwañ o tym samym priorytecie
	sei();
	
	// Spash screen
	Print_Format(ForegroundGreen);
	#if OS_SHOW_SPLASH_SCREEN_AT_START
		Os_SplashScreen();
	#endif
	
	// ród³o resetu
	#if OS_SHOW_RESET_SOURCE_AT_START
		Print_Format(ForegroundCyanBright);
		Print("Reset source: ");
		Print_Format(ForegroundCyan);
		Os_ResetSourceShow(RSTCTRL.RSTFR);
		Print_Format(FormatReset);
		Os_ResetSourceClear();
	#endif
	
	Print_NL();
}


// Scheduler wywo³ywany z funkcji main()
void TaskScheduler(void) {
	
	#if (OS_TASK_MONITOR_MIN_MAX || OS_TASK_MONITOR_AVG_PROC) && OS_TASK_MONITOR_USE
		uint16_t RTC_Before;
		uint16_t RTC_After;
		uint16_t TaskTime;
	#endif
	
	#if OS_TASK_MONITOR_AVG_PROC && OS_TASK_MONITOR_USE
		uint32_t IIR;
	#endif
	
	for(uint8_t i=0; i<OS_TASK_MAXCOUNT; i++) {
		if(Task[i].Pending) {
			if(Task[i].Pending != OS_RUN_EVERY_CYCLE) {
				Task[i].Pending--;
			}
			
			// Zapisanie zegara RTC przed wywo³aniem procesu
			#if (OS_TASK_MONITOR_MIN_MAX || OS_TASK_MONITOR_AVG_PROC) && OS_TASK_MONITOR_USE
				cli();
				Os_DebugTimer = 0;
				RTC_Before = RTC.CNT; 
				sei();
			#endif
			
			// Wywo³anie tasku
			if(Task[i].TaskPtr(Run) == TaskDone) {			// Wywo³anie procesu
								
				// Debug
				#if OS_DEBUG_MESSAGES_SHOW
					Print_NL();
					
					#if OS_DEBUG_MESSAGES_TIMESTAMP && OS_USE_TIME
						Print_Time();
					#endif
					
					Print("Task(");
					
					#if OS_USE_TASK_IDENTIFY
						Task[i].TaskPtr(Identify);
					#else
						Print_Hex((uint16_t)Task[i].TaskPtr);
					#endif
					
					Print(") = Done");
				#endif
				
				TaskClear(i);							// Je¿eli proces siê zakoñczy³ to czyœcimy jego slot
				
				#if (OS_TASK_MONITOR_MIN_MAX || OS_TASK_MONITOR_AVG_PROC) && OS_TASK_MONITOR_USE
					continue;								// Aby przejœæ do kolejnego obiegu pêtli z pominiêciem oblicznia czasów, skoro task ju¿ siê zakoñczy³
				#endif
			}
			
			// Obliczenie czasu, który zaj¹³ proces
			#if (OS_TASK_MONITOR_MIN_MAX || OS_TASK_MONITOR_AVG_PROC) && OS_TASK_MONITOR_USE
				
				cli();
				RTC_After = RTC.CNT;
				
				if(RTC_After >= RTC_Before) {
					TaskTime = Os_DebugTimer * RTC.PER + (RTC_After - RTC_Before);
				}
				else {
					TaskTime = (Os_DebugTimer - 1) * RTC.PER + (32768 - RTC_Before + RTC_After);
				}
				sei();
				
				// Pomiar czasu maksymalnego i minimalnego
				#if OS_TASK_MONITOR_MIN_MAX && OS_TASK_MONITOR_USE
					if(TaskTime > Task[i].TimeMax) Task[i].TimeMax = TaskTime;
					if(TaskTime < Task[i].TimeMin) Task[i].TimeMin = TaskTime;
				#endif
				
				// Filtr IIR dla czasu œredniego
				#if OS_TASK_MONITOR_AVG_PROC
					IIR = Task[i].TimeAvg;
					IIR = IIR * 7;
					IIR = IIR + TaskTime;
					IIR = IIR / 8;
					Task[i].TimeAvg = (uint16_t)IIR;
				#endif
			#endif
		}
		
		// Je¿eli jest u¿ywany Watchdog, to powinien byæ on resetowany tylko w tym miejscu
		#if OS_USE_WATCHDOG
			asm volatile("wdr");
		#endif
	}

	// W konfiguracji mo¿na ustawiæ, by sleep uruchomiæ w Schedularze, zamiast w main()
	#if OS_USE_SLEEP && OS_SLEEP_INDISE_SCHEDULER
		cli();
		if(OS_SLEEP_GPIOR == 0) {
			SLPCTRL.CTRLA	=	SLPCTRL_SEN_bm |							// Zezwolenie na uœpienie
								SLPCTRL_SMODE_IDLE_gc;						// Tryb uœpienia IDLE
//								SLPCTRL_SMODE_STDBY_gc;						// Tryb uœpienia STANDBY (!! dodaæ najpierw kontrolê programowego zezwolenia na uœpienie)
//								SLPCTRL_SMODE_PDOWN_gc;						// Tryb uœpienia POWER DOWN (!! powoduje reset od Watchdoga)
							
			sei();
			asm volatile("sleep");											// Œpimy
		}
		
		// !! wywo³ywane tylko je¿eli nie mo¿na by³o wejœæ w tryb uœpienia
// 		else {
// 			PWM_ON;
// 			_delay_us(10);
// 			PWM_OFF;
// 		}
		sei();
		
	#endif
}


// Dodawanie tasku do tablicy tasków
// - TaskPtr - wskaŸnik do tasku
// - Period - czas (w tickach systemowych) z jak¹ czêstotliwoœci¹ task ma byæ wykonywany
// - InitCounter - pocz¹tkowa liczba timera tasku, jeœli 0 to task zostanie wykonany przy najbli¿szym obiegu Schedulera
// - ReturnSlotNumber - wskaŸnik do zmiennej w której zostanie zwrócony numer slotu, w którym zosta³ utworzony task
os_t TaskAdd(task_t (*TaskPtr)(runmode_t), Os_Timer_t Period, Os_Timer_t InitCounter, uint8_t * ReturnSlotNumber) { 
	
	// Wyœwietlanie komunikatów
	#if OS_DEBUG_MESSAGES_SHOW
		Print_NL();
		#if OS_DEBUG_MESSAGES_TIMESTAMP && OS_USE_TIME
			Print_Time();
		#endif
		Print("TaskAdd(");
		#if OS_USE_TASK_IDENTIFY
			TaskPtr(Identify);
		#else
			Print_Hex((uint16_t)TaskPtr);
		#endif
		Print(',');
		Print_Dec(Period);
		Print(',');
		Print_Dec(InitCounter);
		Print(") = ");
	#endif
	
	// Ca³oœæ jest wykonywana przy wy³¹czonych przerwaniach
	cli();
	
	// Szukanie czy task ju¿ istnieje
	#if !OS_MULTIPLE_TASKS_ALLOWED
	if(TaskFind(TaskPtr) != OsNotFound) {
		sei();
		
		// Debug - task zosta³ ju¿ utworzony wczeœniej
		#if OS_DEBUG_MESSAGES_SHOW
			Print("TaskAlreadyCreated");
		#endif
	
		return OsTaskAlreadyCreated;
	}
	#endif
	
	// Szukanie pierwszego wolnego slotu
	uint8_t SlotNumber;
	if(TaskFindFreeSlot(&SlotNumber) == OsNoFreeSlot) {
		sei();
		
		// Debug
		#if OS_DEBUG_MESSAGES_SHOW
			Print("NoFreeSlot");
		#endif
		
		return OsNoFreeSlot;
	}
	
	// Zwracanie numeru slotu przez wskaŸnik
	if(ReturnSlotNumber != NULL) {
		*ReturnSlotNumber = SlotNumber;
	}
	
	// Wpisywanie nowego procesu (slot jest ju¿ wczeœniej wyczyszczony przez Os_Init() lub TaskClear() podczas kasowania poprzedniego tasku
	Task[SlotNumber].TaskPtr	=	TaskPtr;
	if(Period) {
		// Proces ma siê wywo³ywaæ co zadany czas
		Task[SlotNumber].Counter	=	InitCounter ? InitCounter : Period-1;
		Task[SlotNumber].Period		=	Period;
	}
	else {
		// Proces ma siê wywo³ywaæ w ka¿dym obiegu Schedulera
		Task[SlotNumber].Pending	=	OS_RUN_EVERY_CYCLE;
	}
	
	// Zliczanie procesów - aby w task monitorze pokazywaæ najwiêksz¹ liczbê procesów dzia³aj¹cych jednoczeœnie
	#if OS_TASK_MONITOR_TASKMAXCNT
		uint8_t TaskCount = 0;
		
		for(uint8_t i=0; i<OS_TASK_MAXCOUNT; i++) {
			if(Task[i].TaskPtr != NULL) {
				TaskCount++;
			}
		}
		
		if(TaskCount > Os_DebugMaxTaskCnt) {
			Os_DebugMaxTaskCnt = TaskCount;
		}
	#endif
	
	// W³¹czenie przerwañ
	sei();
	
	// Wywo³anie inicjalizacyjne (konstruktor tasku)
	// Podczas inicjalizacji task mo¿e zwróciæ TaskOK (czyli utworzy³ siê prawid³owo), 
	// TaskDone (czyli zakoñczy³ siê podczas wywo³ania konstruktora) lub TaskError
	switch(TaskPtr(FirstRun)) {
		
		case TaskOK:
			#if OS_DEBUG_MESSAGES_SHOW
				Print_ResponseOK();
			#endif
		
			return OsOK;			
			
		case TaskDone:
			TaskClear(SlotNumber);
			#if OS_DEBUG_MESSAGES_SHOW
				Print("TaskDone");
			#endif			
			return OsTaskDoneWhenFirstRun;
			
		case TaskError:
			TaskClear(SlotNumber);
			#if OS_DEBUG_MESSAGES_SHOW
				Print("Error");
			#endif			
			return OsTaskErrorWhenFirstRun;			
	}
	
	return OsError;
}


// Usuwanie tasku bez wywo³ania destruktora - uwa¿aæ jeœli task wykorzystuje dynamiczn¹ alokacjê pamiêci
os_t TaskClear(uint8_t SlotNumber) {

	// Kontrola poprawnoœci danych
	if(SlotNumber >= OS_TASK_MAXCOUNT) {
		return OsSlotNumberOverRange;
	}
	
	cli();
	Task[SlotNumber].TaskPtr		=	0;
	Task[SlotNumber].Counter		=	0;
	Task[SlotNumber].Period			=	0;
	Task[SlotNumber].Pending		=	0;	
	
	#if OS_TASK_MONITOR_MIN_MAX && OS_TASK_MONITOR_USE
		Task[SlotNumber].TimeMax	=	0;
		Task[SlotNumber].TimeMin	=	0xFFFF;
	#endif
	
	#if OS_TASK_MONITOR_AVG_PROC
		Task[SlotNumber].TimeAvg	=	0;
	#endif
	
	sei();
	return OsOK;
}


// Zakoñczenie tasku. Przed usuniêciem task jest wywo³ywany z argumentem Runmode.Close i oczekiwane jest zwrócenie wyniku TaskDone.
// W przeciwym wypadku funkcja zwraca OsCloseNotConfirmed
os_t TaskClose(task_t (*TaskPtr)(runmode_t)) {
	
	#if OS_DEBUG_MESSAGES_SHOW
		Print_NL();
		
		#if OS_DEBUG_MESSAGES_TIMESTAMP && OS_USE_TIME
			Print_Time();
		#endif
		
		Print("TaskClose(");
		
		#if OS_USE_TASK_IDENTIFY
			TaskPtr(Identify);
		#else
			Print_Hex((uint16_t)TaskPtr);
		#endif
		
		Print(") = ");
	#endif
	
	// Szukanie tasku - wersja jeœli nie dozwolone dodawanie wielu tych samych tasków
	#if OS_MULTIPLE_TASKS_ALLOWED == 0
		uint8_t SlotNumber;
		if(TaskFind(TaskPtr, &SlotNumber)) {
			
			// Debug
			#if OS_DEBUG_MESSAGES_SHOW
				Print("NotFound");
			#endif
			
			return OsNotFound;
		}
	#endif
	
	// Szukanie tasku - wersja jeœli dozwolone dodawanie wielu tych samych tasków
	#if OS_MULTIPLE_TASKS_ALLOWED == 1
		uint8_t SlotNumber;
		if(TaskFind(TaskPtr, &SlotNumber) == OsNotFound) {
			
			// Debug
			#if OS_DEBUG_MESSAGES_SHOW
				Print("NotFound");
			#endif
			
			return OsNotFound;
		}
	#endif
	
	// Wywo³anie tasku z argumentem Close
	task_t CloseResult = Task[SlotNumber].TaskPtr(Close);
	if(CloseResult == TaskDone || CloseResult == TaskOK) {
	//if(CloseResult == TaskOK) {
		// Je¿eli task potwierdzi³ swoje zakoñczenie
		
		// Debug
		#if OS_DEBUG_MESSAGES_SHOW
			Print_ResponseOK();
		#endif
		
		return TaskClear(SlotNumber);
	}
	else {
		// Je¿eli task nie potwierdzi³, ¿e mo¿na go usun¹æ
		
		// Debug
		#if OS_DEBUG_MESSAGES_SHOW
			Print("NotConfirmed");
		#endif
		
		return OsCloseNotConfirmed;
	}
}


// Zmiana czasów 
// - SlotNumber - numer slotu, w którym bêdzie zmiana
// - Period - nowy okres mierzony w tickach systemowych, wartoœæ musi byæ >0
// - Counter - parametr opcjonalny, nowa wartoœæ licznika, jeœli nie podano to licznik zostanie wyzerowany
os_t TaskPeriodChange(uint8_t SlotNumber, Os_Timer_t Period, Os_Timer_t Counter) {
	
	// Kontrola czy w podanym slocie istnieje jakiœ task 
	if(Task[SlotNumber].TaskPtr == NULL) {
		return OsNotFound;
	}
	
	// Zmiana timingu - wszystkie operacje przy wy³¹czonych przerwaniach
	cli();
	if(Period) {
		Task[SlotNumber].Period		=	Period;
	}
	else {
		Task[SlotNumber].Period		=	0;
		Task[SlotNumber].Pending	=	OS_RUN_EVERY_CYCLE;
	}
	
	if(Counter == 0) {
		Task[SlotNumber].Counter = Period;
	}
	else {
		Task[SlotNumber].Counter = Counter;
	}
	sei();
	
	// Debug
	#if OS_DEBUG_MESSAGES_SHOW
		
		Print_NL();
		
		#if OS_DEBUG_MESSAGES_TIMESTAMP && OS_USE_TIME
			Print_Time();
		#endif
		
		Print("TaskPeriodChange(");
		
		#if OS_USE_TASK_IDENTIFY
			Task[SlotNumber].TaskPtr(Identify);
		#else
			Print_Hex((uint16_t)Task[SlotNumber].TaskPtr);
		#endif
		
		Print(',');
		Print_Dec(Period);
		Print(',');
		Print_Dec(Counter);
		Print(")");
	#endif
	
	return OsOK;
}


// Zmiana czasów
// - TaskPtr - wskaŸnik do procesu, który ma byæ zmieniony
// - Period - nowy okres mierzony w tickach systemowych, wartoœæ musi byæ >0
// - Counter - parametr opcjonalny, nowa wartoœæ licznika, jeœli nie podano to licznik zostanie wyzerowany
os_t TaskPeriodChange(task_t (*TaskPtr)(runmode_t), Os_Timer_t Period, Os_Timer_t Counter) {
	uint8_t Slot;
	if(TaskFind(TaskPtr, &Slot) == OsOK) {
		return TaskPeriodChange(Slot, Period, Counter);
	}
	else {
		return OsNotFound;
	}
}


// Funkcja znajduje pierwszy wolny slot i zwraca jego numer przez wskaŸnik
// Jeœli brak wolnych slotów to zwraca OS_RES_NO_FREE_SLOT
os_t TaskFindFreeSlot(uint8_t * SlotNumber) {
	
	// Przesukiwanie tablicy slotów
	for(uint8_t i=0; i<OS_TASK_MAXCOUNT; i++) {
		
		// Szukanie pierwszego wolnego slotu, w którym wskaŸnik do tasku jest NULL
		if(Task[i].TaskPtr == NULL) {
			*SlotNumber = i;
			return OsOK;
		}
	}
	
	// Brak wolnych slotów
	return OsNoFreeSlot;
}


// Szukanie slotu, w któym znajduje siê funkcja o podanym wskaŸniku TaskPtr
// - TaskPtr - wskaŸnik do szukaniego tasku
// - SlotNumber - wskaŸnik do zmiennej w której bêdzie zwrócony wynik
// Funkcja zwraca jedn¹ z trzech wartoœci:
// - OsOK - znaleziono jedno wyst¹pienia tasku
// - OsError - nie znaleziono
// - OsMultipleFound - znaleziono wiêcej ni¿ jedno wyst¹pienie tasku, we wzkaŸniku SlotNumber zwrócono ostatnie ze znalezionych
os_t TaskFind(task_t (*TaskPtr)(runmode_t), uint8_t * SlotNumber) {
	uint8_t FoundCount = 0;
	for(uint8_t i=0; i<OS_TASK_MAXCOUNT; i++) {
		if(Task[i].TaskPtr == TaskPtr) {
			if(SlotNumber != NULL) {				// SlotNumber to argument opcjonalny, jeœli nie podano to NULL
				*SlotNumber = i;
			}
			FoundCount++;
		}
	}
	
	// Zwracanie wyniku
	#if OS_MULTIPLE_TASKS_ALLOWED
		if(FoundCount == 0) {
			return OsNotFound;
		}
		else if(FoundCount == 1) {
			return OsOK;
		}
		else {
			return OsMultipleFound;
		}
	#else	
		if(FoundCount) {
			return OsOK;
		}
		else {
			return OsNotFound;
		}
	#endif
}


// Pobranie numeru slotu
// Alternatywa dla TaskFind() gdzie numer jest zwracany przez wskaŸnik, a przez wartoœæ status funkcji
// Ta funkcja zwraca numer slotu przez wartoœæ, ale UWAGA musimy byæ pewni, ¿e task jest ju¿ utworzony w tablicy procesów
// i wystêpuje on tylko jeden raz
uint8_t TaskGetSlotNumber(task_t (*TaskPtr)(runmode_t)) {
	for(uint8_t i=0; i<OS_TASK_MAXCOUNT; i++) {
		if(Task[i].TaskPtr == TaskPtr) {
			return i;
		}
	}
	
	// Nic nie znaleziono
	return 0;
}


// Przeliczanie milisekund na ticki systemowe
Os_Timer_t TaskMsToTicks(uint16_t Time_ms) {
	Os_Timer_t Ticks = Time_ms / OS_TICK_DELAY;
	if(Ticks == 0) Ticks = 1;
	return Ticks;
}


// ===========
// Diagnostyka
// ===========


#if (OS_TASK_MONITOR_AVG_PROC || OS_TASK_MONITOR_MIN_MAX) && OS_TASK_MONITOR_USE

static uint32_t Os__DebugConvertTicksToMicroseconds(uint16_t Ticks) {
	uint64_t Res = Ticks;
	if(Ticks == 0xFFFF) return 0;
	Res = Res * 1000000;
	Res = Res / 32768;
	return Res;
}


// Zerowanie czasów
void Os_DebugTimeClear(void) {
	
	for(uint8_t i=0; i<OS_TASK_MAXCOUNT; i++) {
		
		#if OS_TASK_MONITOR_MIN_MAX && OS_TASK_MONITOR_USE
			Task[i].TimeMax	=	0;
			Task[i].TimeMin	=	0xFFFF;
		#endif

		#if OS_TASK_MONITOR_AVG
			Task[i].TimeAvg	=	0;
		#endif
	}

	Os_DebugMaxTaskCnt = 0;
}
#endif


#if OS_TASK_MONITOR_AVG_PROC && OS_TASK_MONITOR_USE
static uint32_t Os__DebugShowPercentUsage(uint8_t SlotNumber) {
	uint16_t CallsPerSecond = 1000 / (Task[SlotNumber].Period * OS_TICK_DELAY);					// Ile wywo³añ na sekundê
	uint32_t AverageTime = Os__DebugConvertTicksToMicroseconds(Task[SlotNumber].TimeAvg);		// Wynik w mikrosekundach
	uint32_t TimeInSecond = CallsPerSecond * AverageTime;										// Sumaryczny czas zajêty przez task w ci¹gu sekundy (podany w us)
	TimeInSecond = TimeInSecond / 1000;															// Sumaryczny czas zajêty przez task w ci¹gu sekundy (podany w ms)
	
	Print_Dec(TimeInSecond / 10);
	Print('.');
	Print_Dec(TimeInSecond % 10);

	return TimeInSecond;
}
#endif


// Pokazywanie tablicy tasków
#if OS_TASK_MONITOR_USE
void Os_Monitor(uint8_t argc, uint8_t * argv[]) {
	
	#if OS_TASK_MONITOR_AVG_PROC
		uint32_t Percentage;
		uint32_t PercentageSum = 0;			// Procentowe zajêtoœæ procesora sumarycznie dla wszystkich tasków
	#endif
	
	// Nag³ówek tabeli
	Print_Format(ForegroundWhiteBright);
	Print("No\tPtr\tPend\t");
	
	#if OS_TASK_MONITOR_CNT
		Print("Cnt\t");
	#endif
	
	Print("Per\t");
	
	#if OS_TASK_MONITOR_MIN_MAX
		Print("Tmax\tTmin\t");
	#endif
	
	#if OS_TASK_MONITOR_AVG_PROC
		Print("Tavg\tProc\t");
	#endif
	
	#if OS_USE_TASK_IDENTIFY
		Print("Id");
	#endif
	
	Print_Format(FormatReset);
	
	for(uint8_t i=0; i<OS_TASK_MAXCOUNT; i++) {
		Print_NL();
		Print_Dec(i); 
		Print("\t");
		Print_Hex((uint16_t)(Task[i].TaskPtr));
		Print("\t");
		Print_Dec(Task[i].Pending);
		Print("\t");
		
		#if OS_TASK_MONITOR_CNT
			Print_Dec(Task[i].Counter);
			Print("\t");
		#endif
		
		//Print_Dec(Task[i].Period * OS_TICK_DELAY);
		Print_Dec(Task[i].Period);
		Print("\t");
		
		#if OS_TASK_MONITOR_MIN_MAX
			Print_Dec(Os__DebugConvertTicksToMicroseconds(Task[i].TimeMax));
			Print("\t");
			Print_Dec(Os__DebugConvertTicksToMicroseconds(Task[i].TimeMin));
			Print("\t");
		#endif
		
		#if OS_TASK_MONITOR_AVG_PROC
			Print_Dec(Os__DebugConvertTicksToMicroseconds(Task[i].TimeAvg));
			Print("\t");
			Percentage = Os__DebugShowPercentUsage(i);
			PercentageSum += Percentage;
			Print("\t");
		#endif 
		
		#if OS_USE_TASK_IDENTIFY
			if(Task[i].TaskPtr != NULL) Task[i].TaskPtr(Identify);
		#endif
	}
	
	Print_Format(ForegroundWhiteBright);
	Print("\r\nF_CPU:\t\t");
	Print_Format(FormatReset);
	Print_Dec(F_CPU);
	Print("Hz");
	
	Print_Format(ForegroundWhiteBright);
	Print("\r\nTickTime:\t");
	Print_Format(FormatReset);
	Print_Dec(OS_TICK_DELAY);
	Print("ms");
	
	#if OS_TASK_MONITOR_TASKMAXCNT
		Print_Format(ForegroundWhiteBright);
		Print("\r\nMaxTasks:\t");
		Print_Format(FormatReset);
		Print_Dec(Os_DebugMaxTaskCnt);
	#endif
	
	#if OS_TASK_MONITOR_AVG_PROC
		Print_Format(ForegroundWhiteBright);
		Print("\r\nCPU usage:\t");
		Print_Format(FormatReset);
		Print_Dec(PercentageSum / 10);
		Print('.');
		Print_Dec(PercentageSum % 10);
		Print('%');
	#endif
}

#endif


// Przerwanie RTC u¿ywane do Tickera systemowego
ISR(RTC_CNT_vect) {													// Przerwanie wywo³ywane na koniec uœpienia przez SleepTimer

	// Kasowanie flagi przerwania
	RTC.INTFLAGS	=	RTC_OVF_bm;			
	
	// Inkrementacja licznika ticków systemowych
	Os_Ticks++;
	
	// Sprawdzenie wszystkich procesów
	for(uint8_t i=0; i<OS_TASK_MAXCOUNT; i++) {
		
		// Je¿eli w badanym slocie jest wpisany jakiœ task
		if(Task[i].TaskPtr != NULL) {
			
			// Je¿eli aktualnie teraz licznik ma wartoœæ zero (task mo¿e byæ zainicjalizowany z licznikiem 0)
			if(Task[i].Counter == 0) {
				
				// Je¿eli Pending = 255 to task ma siê wykonywaæ w ka¿dym obiegu Schedulera i nic mu nie zmieniamy
				if(Task[i].Pending == OS_RUN_EVERY_CYCLE) {
					continue;
				}
				
				// Inkrementuj pending jeœli nie dojdzie do przepe³nienia 
// 				if(Task[i].Pending < 255) {					
// 					Task[i].Pending++;
// 				}
				
				// Ustawienie flagi do wykonania tasku
				if(Task[i].Pending == 0) {
					Task[i].Pending++;
				}
				#if OS_DEBUG_MESSAGES_SHOW
				else {
					// Przepe³nienie zmiennej pending
					Print("\r\nPending overflow on slot ");
					Print_Dec(i);
					//asm volatile("break");
					// !! Domyœlny UART musi mieæ najwy¿szy priorytet, bo inaczej w tym miejscy mo¿e dojœæ do zawieszenia siê programu
				}
				#endif

				// Ponowne wpisanie czasu do odmierzenia pomniejszonego o 1 (z tego powodu Period nie mo¿e byæ zainicjalizowany jako 0)
				Task[i].Counter = Task[i].Period - 1;					
			}
			else {
				
				// Nic siê nie dzieje - odliczamy czas
				Task[i].Counter--;
			}
		}
	}						
	
	// Diagnostyka
	#if (OS_TASK_MONITOR_MIN_MAX || OS_TASK_MONITOR_AVG_PROC) && OS_TASK_MONITOR_USE
		Os_DebugTimer++;			// Zwiêkszanie z ka¿dym tickiem systemowym
	#endif
	
}


// =============
// Splash screen
// =============


void Os_SplashScreen(void) {
	Print_Format(ForegroundYellow);
	Print_NL();
	Print_NL();
	Print("     ___ _    ______           __________  _____ __  _______  _____\r\n");
	Print("    /   | |  / / __ \\   __  __/ ____/ __ \\/ ___//  |/  / __ \\/ ___/\r\n");
	Print("   / /| | | / / /_/ /  / / / / /   / / / /\\__ \\/ /|_/ / / / /\\__ \\\r\n");
	Print("  / __| | |/ / _  _/  / /_/ / /___/ /_/ /___/ / /  / / /_/ /___/ /\r\n");
	Print(" /_/  |_|___/_/ |_|  / ____/\\____/\\____//____/_/  /_/\\____//____/\r\n");
	Print_Format(ForegroundCyan);
	for(uint8_t i=0; i<21; i++) {
		Print('-');
	}
	Print_Format(ForegroundYellow);
	Print("\\/");
	Print_Format(ForegroundCyan);
	for(uint8_t i=0; i<44; i++) {
		Print('-');
	}
	Print_NL();
}


// =============
// Obs³uga czasu
// =============

#if OS_USE_TIME

// Przerwanie od PIT co 1s (czas wykonania 28us @ 1MHz)
ISR(RTC_PIT_vect) {													// Przerwanie wywo³ywane co 1 sekundê
	RTC.PITINTFLAGS	=	RTC_PI_bm;									// Kasowanie flagi przerwania
	Os_Time++;														// Inkrementacja timera systemowego
	
	#if OS_USE_SLEEP
	if(Os_SleepTimer) {												// Je¿eli mamy zadany czas uœpienia
		Os_SleepTimer--;											// Zmniejszamy timer uœpienia do zera podczas snu
	}
	#endif
}


// Wyœwietlenie czasu w formacie YYYY-MM-DD hh:mm:ss
void Os_TimePrint(uint8_t argc, uint8_t * argv[]) {
	time_t TimeLocal = Os_Time;
	Print_Time(&TimeLocal);
}


// Ustawianie czasu w formacie 20YY-MM-DD hh:mm:ss
void Os_TimeSet(uint8_t YY, uint8_t MM, uint8_t DD, uint8_t hh, uint8_t mm, uint8_t ss) {
	tm NewTime;
	NewTime.tm_year = 100 + YY;
	NewTime.tm_mon = MM - 1;
	NewTime.tm_mday = DD;
	NewTime.tm_hour = hh;
	NewTime.tm_min = mm;
	NewTime.tm_sec = ss;
	
	cli();
	Os_Time = mk_gmtime(&NewTime);
	sei();
}

// Ustawianie czasu 
void Os_TimeSet(tm * NewTime) {
	cli();
	Os_Time = mk_gmtime(NewTime);
	sei();
}


#if OS_USE_TIME_RECOVERY
// Time Recovery
// Proces, który przy starcie odczytuje czas zapisany w EEPROM i wpisuje go do zmiennej Os_Time, a nastêpnie
// w ka¿dym wywo³aniu zapisuje aktualny czas do EEPROM. Nie wywo³ywaæ zbyt czêsto, bo ¿ywotnoœæ EEPROM w AVR to 100000 cykli.
// Wymaga ustawienia w eeprom_map.h gdzie ma byæ zapisywany czas, np.:
//	#define		OS_TIME3					81				// Czas dla procesu Os_TimeRecovery()
//	#define		OS_TIME2					82				// Czas dla procesu Os_TimeRecovery()
//	#define		OS_TIME1					83				// Czas dla procesu Os_TimeRecovery()
//	#define		OS_TIME0					84				// Czas dla procesu Os_TimeRecovery()

// Zapisywanie czasu w EEPROM, wywo³ywane przez Os_TimeRecovery() lub Os_TimeSet()
void Os_TimeRecoverySave(void) {
	time_t Time = Os_Time;
	EEPROM_Write(OS_TIME3, uint8_t((Time & 0xFF000000) >> 24));
	EEPROM_Write(OS_TIME2, uint8_t((Time & 0x00FF0000) >> 16));
	EEPROM_Write(OS_TIME1, uint8_t((Time & 0x0000FF00) >>  8));
	EEPROM_Write(OS_TIME0, uint8_t((Time & 0x000000FF) >>  0));
}


// Proces do cyklicznego zapisywania czasu w pamiêci EEPROM
task_t Os_TimeRecovery(runmode_t RunMode) {
	
	// Zmienne
	
	// Normalne wywo³anie
	if(RunMode == Run) {	
		Os_TimeRecoverySave();
	}
	
	// Konstruktor
	else if(RunMode == FirstRun) {
		uint8_t Time3 = EEPROM_Read(OS_TIME3);
		uint8_t Time2 = EEPROM_Read(OS_TIME2);
		uint8_t Time1 = EEPROM_Read(OS_TIME1);
		uint8_t Time0 = EEPROM_Read(OS_TIME0);
		
		time_t Time = (uint32_t(Time3) << 24) | (uint32_t(Time2) << 16) | (uint32_t(Time1) << 8) | (uint32_t(Time0));
		if(Time != 0xFFFFFFFF) {
			Os_Time = Time;
		}
	}
	
	// Destruktor
	else if(RunMode == Close) {
		
	}
	
	// Identyfikacja
	#if OS_USE_TASK_IDENTIFY
	else if(RunMode == Identify) {
		Print("TimeRecov");
	}
	#endif
	
	return TaskOK;
}
#endif


// Ustawienie czasu z konsoli
#if OS_USE_TIMESET_COMMAND
void Os_TimeSet(uint8_t argc, uint8_t * argv[]) {
	
}
#endif


#endif


// ==========
// SleepTimer
// ==========

// Zatrzymanie pracy na zadany czas
// - SleepTime - czas w sekundach
// - SleepMode - tryb uœpienia zgodnie z ustawieniami Sleep Controller
//             - SLPCTRL_SMODE_IDLE_gc - ka¿de przerwanie mo¿e wybudziæ, wszystkie peryferia w³¹czone, zatrzymane jedynie CPU, taski siê nie wykonuj¹
//             - SLPCTRL_SMODE_STDBY_gc - tylko niektóre peryferia i przerwania mog¹ dzia³aæ, taski siê nie wykonuj¹
//             - SLPCTRL_SMODE_PDOWN_gc - dzia³a tylko zegar RTC + nieliczne przerwania, RTC_CNT_vect zatrzymane!!!
#if OS_USE_SLEEP
void Os_Sleep(OS_SLEEP_TIMER_TYPE SleepTime, uint8_t SleepMode) {
	
	cli();
	Os_SleepTimer	=	SleepTime;									// Wpisanie zadanego czasu do zmiennej globalnej, która bêdzie zmniejszana w przerwaniu od PIT
	SLPCTRL.CTRLA	=	SleepMode |									// Tryb uœpienia przekazywany przez argument
						SLPCTRL_SEN_bm;								// Zezwolenie na uœpienie
	sei();

	// !! zmieniæ na sprawdzanie flagi gotowoœci do uœpienia
	Uart_WaitForTxComplete();										// Czekanie na zakoñczenie wysy³ania danych przez UART (odbywa siê w przerwaniach)

	// Czekanie a¿ up³ynie czas uœpienia
	while(Os_SleepTimer) {											// Je¿eli jest zadany jakiœ czas uœpienia...
		asm volatile("sleep");										// ...to œpimy dalej
	}

}
#endif


// =====
// Reset
// =====


// Pokazuje Ÿród³o resetu. Po wywo³aniu tej funkji, je¿eli Ÿród³o resetu nie jest ju¿ potrzebne, nale¿y wywo³aæ Os_ResetSourceClear()
void Os_ResetSourceShow(uint8_t Register) {
	if(Register & RSTCTRL_PORF_bm)		Print("PWR ");
	if(Register & RSTCTRL_BORF_bm)		Print("BRO ");
	if(Register & RSTCTRL_EXTRF_bm)		Print("EXT ");
	if(Register & RSTCTRL_WDRF_bm)		Print("WDR ");
	if(Register & RSTCTRL_SWRF_bm)		Print("SOFT ");
	if(Register & RSTCTRL_UPDIRF_bm)	Print("UPDI ");
}


// Czyszczenie rejestru przechowuj¹cego informacjê o Ÿrod³e sygna³y resetuj¹cego
void Os_ResetSourceClear(void) {
	RSTCTRL.RSTFR	=	0xFF;
}




// Zapisywanie Ÿród³a resetu do logu
#if C_LOG
void Os_ResetSourceLog(void) {
	uint8_t Buffer[12];
	memset(Buffer, 0 , sizeof(Buffer));
	//Buffer[0] = LOG_OS_Reset;
	Buffer[0] = 0x01;
	Buffer[1] = RSTCTRL.RSTFR;
	Log_Add(Buffer);
}
#endif


// Reset wywo³ywany software'owo
void Os_ResetExecute(uint8_t argc, uint8_t * argv[]) {
	CCP				=	CCP_IOREG_gc;								// Odblokowanie chronionych rejestrow
	RSTCTRL.SWRR	=	RSTCTRL_SWRE_bm;
}


// ========
// Watchdog
// ========


// Wy³¹czenie watchdoga - tylko do celów debugowych
void Os_WatchdogDisable(uint8_t argc, uint8_t * argv[]) {
	#if OS_USE_WATCHDOG
		CCP						=	CCP_IOREG_gc;					// Odblokowanie chronionych rejestrow
		WDT.CTRLA				=	0;
		while(WDT.STATUS & WDT_SYNCBUSY_bm);
	#endif
}


#endif