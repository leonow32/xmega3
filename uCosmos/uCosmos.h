/*
  
       ___ _    ______           __________  _____ __  _______  _____
      /   | |  / / __ \   __  __/ ____/ __ \/ ___//  |/  / __ \/ ___/
     / /| | | / / /_/ /  / / / / /   / / / /\__ \/ /|_/ / / / /\__ \ 
    / __| | |/ / _  _/  / /_/ / /___/ /_/ /___/ / /  / / /_/ /___/ / 
   /_/  |_|___/_/ |_|  / ____/\____/\____//____/_/  /_/\____//____/  
  ---------------------\/--------------------------------------------
 
  

 
UWAGI I POMYS£Y
		-	Dodaæ obs³ugê wszystkich trzech trybów uœpienia, póki co jest tylko IDLE

CHANGELOG
1.18	*	Zmiana w liczeniu Pending - je¿eli proces ju¿ jest zaplanowany do wykonania (Pending = 1) to nie
			mo¿na ju¿ mu zwiêkszaæ pendingów, aby unikn¹æ ryzyka skumulowania procesów i potem wykonywania ich zbyt czêsto
1.17	+	os_t TaskPeriodChange(task_t (*TaskPtr)(runmode_t), Os_Timer_t Period, Os_Timer_t Counter);
1.16	+	Dodanie dodatkowej zmiennej globalnej Os_Ticks do ³atwego mierzenia czasu, w szczególnoœci do timeoutów
1.15	+	Modyfikacja Os_TimePrint() aby nie pokazywa³o bzdur, kiedy podany czas = 0xFFFFFFFF
1.14	+	Konsola systemowa jako task przy pomocy biblioteki console.h
1.13	+	Mo¿liwoœæ zdefiniowania, by task uruchamia³ siê przy ka¿dym obiegu Schedulera. W tym celu nale¿y zrobiæ TaskAdd(ConsoleDemo_ConsoleTask, 0);
			Period ustawiony na 0 oznacza wywo³anie tasku przy ka¿dym obiegu. Pending zostaje ustawione na sztywno na 255 (OS_RUN_EVERY_CYCLE).
1.12	+	void Os_TimePrint(const time_t Time);
		+	Zmiana szablonu tasku na zajmuj¹cy mniej miejsca i bardziej czytelny
		+	Dodanie wyœwietlania F_CPU oraz OS_TICK_DELAY w Monitorze
		+	Funkcja Time Recovery do backupowania czasu w pamiêci EEPROM
		+	task_t Os_TimeRecovery(runmode_t RunMode);
		+	#define		TaskAddSec(TaskPtr, Period)	TaskAdd(TaskPtr, Os_Timer_t(Period * 1000 / OS_TICK_DELAY), 0, NULL)
		+	#define		TaskAddMin(TaskPtr, Period)	TaskAdd(TaskPtr, Os_Timer_t(Period * 60000 / OS_TICK_DELAY), 0, NULL)
1.11	*	Poprawka drobnego b³êdu - w linii #if OS_USE_TIMESET_COMMAND || OS_USE_TIME_COMMAND brakowa³o OS_USE_TIME_COMMAND
1.10	*	Zmiana  #define	OS_TICK_TIMER_TYPE na typedef 
		+	Definicja do ³atwiejszego tworzenia tasków, gdzie podaje siê czas w milisekundach zamiast w tickach systemowych
			#define	TaskAddMs(TaskPtr, Period)	TaskAdd(TaskPtr, Period / OS_TICK_DELAY, 0, NULL)
1.09	+	Nowe podejœcie do truby uœpienia - licznik procesów uniemo¿liwiaj¹cych wejœcie w tryb uœpienia
			Wejœcie w tryb uœpienia mo¿liwe tylko wtedy, gdy OS_SLEEP_GPIOR = 0
		+	#define		OS_SLEEP_DISABLE		if(OS_SLEEP_GPIOR != 255)	{OS_SLEEP_GPIOR++;}
		+	#define		OS_SLEEP_ENABLE			if(OS_SLEEP_GPIOR)			{OS_SLEEP_GPIOR--;}
1.08	+	Optymalizacja kodu i porz¹dkowanie
		+	Dodanie definicji do wybierania, jakie kolumny maj¹ siê pokazywaæ w Task Monitorze
1.07	+	Dodanie walidowania czasu - po w³¹czeniu zasilania czas domyœlnie jest Invalid, dopiero po ustawieniu czasu jest ustawiana flaga Valid
		+	void Os_TimeSet(uint8_t argc, uint8_t * argv[]);
		+	bool Os_TimeValidCheck(void);
1.06	*	Przeniesienie instrukcji resetowania Watchdoga - teraz kasuje siê po ka¿dym wykonaniu tasku, a nie po obiegu wszystkich tasków
1.05	+	void Os_WatchdogDisable(uint8_t argc = 0, uint8_t * argv[] = NULL);
1.04	*	Poprawienie wyœwietlania w TaskMonitor, dodatkowe definicja w configu do wybierania, któe kolumny tabeli maj¹ byæ pokazywane
1.03	+	void Os_ResetSourceShow(void);
		+	void Os_ResetSourceClear(void);
		+	void Os_ResetExecute(uint8_t argc = 0, uint8_t * argv[] = NULL);
1.02	*	Usuniêcie œmieci pozosta³ych po debugowaniu
		+	void Os_Monitor(uint8_t argc, uint8_t * argv[]);
1.01	*	Zmiana typu zmiennej Os_MsToTicks(uint16_t Time_ms) z uint8_t
1.00	*	Zakoñczenie prac testowych
0.09	*	Komunikaty debugowe
0.08	*	Scheduler zwraca informacjê czy wszystkie procesy zosta³y ju¿ wykonane i nic nie zalega (Pending=0) aby mo¿na by³o uœpiæ procesor
		+	#define	OS_SLEEP_INDISE_SCHEDULER - tryb uœpienia wywo³ywany wewn¹trz shedulera
		+	Pomiar zajêtœci procesora wyra¿ony w procentach
		+	Wydzielenie wszystkich definicji, typów, ipt do osobnego pliku uCosmos_defines.h
0.07	*	Wyœwietlanie czasu zajmowanego przez taski w mikrosekundach
		+	void Os_DebugTimeClear(void);
		+	void Os__SlotClear(uint8_t SlotNumber);
0.06	*	Rozwiniêcie funkcji debuguj¹cych
0.05	*	void Os_SleepTimer(uint8_t SleepTime, uint8_t SleepMode);
0.04	*	Kilka nowych zmiennych konfiguracyjnych w config.h
		+	void Os_TimePrint(void);
		+	void Os_TimeSet(uint8_t YY, uint8_t MM, uint8_t DD, uint8_t hh, uint8_t mm, uint8_t ss);
		+	time_t Os_TimeGet(void);
		+	#define	OS_TICK_DELAY
		+	OS_TIMER_TYPE Os_MsToTicks(uint8_t Time_ms);
0.03	+	os_t Os__FindTask(task_t (*TaskPtr)(runmode_t RunMode), uint8_t * SlotNumber);
		+	os_t TaskClose(task_t (*TaskPtr)(runmode_t RunMode));
		+	os_t TaskPeriodChange(uint8_t SlotNumber, uint8_t Period, uint8_t Counter);
		+	uint8_t TaskGetSlotNumber(task_t (*TaskPtr)(runmode_t));
0.02	+	void Os_Init(void);
		+	uint8_t TaskScheduler(void);
		+	uint8_t TaskAdd(task_t (*TaskPtr)(void), uint8_t Period, uint8_t InitCounter, uint8_t * ReturnSlotNumber);
		+	uint8_t Os__FindFreeSlot(uint8_t * SlotNumber);
		+	void TaskTableDump(void);
		+	uint8_t TaskKill(uint8_t SlotNumber);
0.01	*	Podró¿ dooko³a œwiata trzeba zacz¹æ od pierwszego kroku
		
HARDWARE
		-	RTC
*/


#ifndef UCOSMOS_H_
#define UCOSMOS_H_

#include		<time.h>
#include		<string.h>		// memset
#include		<avr/io.h>
#include		<avr/interrupt.h>
#include		"uCosmos_defines.h"
#include		"uCosmos_config.h"

#if C_PRINT
	#include	"../print/print.h"
#else
	#error		"This module requires PRINT component"
#endif

#if C_INTERPRETER
	#include	"../interpreter/interpreter.h"
#endif

#if C_PERIPHERALS
	#include	"../peripherals/peripherals.h"
#endif

//#if C_LOG
// #include	"log.h"
//#define		LOG_OS_Reset	0x01
//#endif

// #if OS_USE_CONSOLE
// 	#include	"../console/console.h"
// #endif

// TODO: Po co to jest?
// #if OS_USE_TIMESET_COMMAND || OS_USE_TIME_COMMAND
//  #include		"../console/console.h"
// #endif

#if OS_USE_TIME && OS_USE_TIME_RECOVERY
 #include	"eeprom.h"
#endif

// Zarz¹dzanie taskami
void		Os_Init(void);
void		Os_ConsoleInit(void);
void		TaskScheduler(void);																												// 406B
os_t		TaskAdd(task_t (*TaskPtr)(runmode_t), Os_Timer_t Period, Os_Timer_t InitCounter = 0, uint8_t * ReturnSlotNumber = NULL);
os_t		TaskClear(uint8_t SlotNumber);
os_t		TaskClose(task_t (*TaskPtr)(runmode_t));
os_t		TaskPeriodChange(uint8_t SlotNumber, Os_Timer_t Period, Os_Timer_t Counter = 0);
os_t		TaskPeriodChange(task_t (*TaskPtr)(runmode_t), Os_Timer_t Period, Os_Timer_t Counter = 0);
os_t		TaskFindFreeSlot(uint8_t * SlotNumber);
os_t		TaskFind(task_t (*TaskPtr)(runmode_t), uint8_t * SlotNumber = NULL);
uint8_t		TaskGetSlotNumber(task_t (*TaskPtr)(runmode_t));
Os_Timer_t	TaskMsToTicks(uint16_t Time_ms);

// Konsola systemowa
#if OS_USE_CONSOLE
 task_t		TaskConsole(runmode_t RunMode);
#endif

// Licznik ticków systemowych
extern volatile uint8_t Os_Ticks;

// Obs³uga czasu
#if OS_USE_TIME
 extern volatile time_t Os_Time;
 void		Os_TimePrint(uint8_t argc = 0, uint8_t * argv[] = NULL);
 void		Os_TimePrint(time_t Time);
 bool		Os_TimeValidCheck(void);
 void		Os_TimeInvalid(void);
 void		Os_TimeSet(uint8_t argc, uint8_t * argv[]);
 void		Os_TimeSet(tm * NewTime);
 #if OS_USE_TIME_RECOVERY
  void Os_TimeRecoverySave(void);
  task_t		Os_TimeRecovery(runmode_t RunMode);
 #endif
#endif

// Oszczêdzanie energii
#if OS_USE_SLEEP
 void		Os_Sleep(OS_SLEEP_TIMER_TYPE SleepTime, uint8_t SleepMode);
#endif

// Debugowanie
#if OS_TASK_MONITOR_USE
 void		Os_Monitor(uint8_t argc = 0, uint8_t * argv[] = NULL);
#endif

#if OS_TASK_MONITOR_AVG || OS_TASK_MONITOR_MIN_MAX
 void		Os_DebugTimeClear(void);
#endif 

// extern volatile uint8_t Os_DebugTimer;

#if OS_TASK_MONITOR_TASKMAXCNT
 extern uint8_t Os_DebugMaxTaskCnt;
#endif

// Reset
void		Os_ResetSourceShow(uint8_t Register);
void		Os_ResetSourceClear(void);
void		Os_ResetSourceLog(void);
void		Os_ResetExecute(uint8_t argc = 0, uint8_t * argv[] = NULL);

// Watchdog
void		Os_WatchdogDisable(uint8_t argc = 0, uint8_t * argv[] = NULL);

// Log
//void		Os_LogInterpreter(uint8_t * Data);
#endif /* UCOSMOS_H_ */
