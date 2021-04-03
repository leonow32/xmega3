// Wersja 1.18

#ifndef UCOSMOS_CONFIG_H_
#define UCOSMOS_CONFIG_H_

#include		<avr/io.h>

// ========================================
// Template
// ========================================

#if P_TEMPLATE
	
	// Wyb�r generatora
	#define		OS_GENERATOR_ULP				1
	#define		OS_GENERATOR_XOSC32				0
	
	// Konfiguracja systemu
	#define		OS_TASK_MAXCOUNT				10			// Od tego zalezy rozmiar tablicy Task[] w RAM
	#define		OS_TICK_DELAY					100			// Okres timera systemowego w ms, zakres 1-1000
	typedef		uint16_t						Os_Timer_t;	// Typ zmiennej timer�w programowych, od tego zale�y maksymalny odliczany czas i zaj�to�� pami�ci
	#define		OS_MULTIPLE_TASKS_ALLOWED		0			// Mo�na dodawa� kilka razy ten sam task
	#define		OS_SHOW_RESET_SOURCE_AT_START	1			// Czy pokazywa� �r�d�o resetu na starcie
	#define		OS_SHOW_SPLASH_SCREEN_AT_START	1			// Czy pokazywa� logo systemu na starcie
	
	// Konsola systemowa
	#define		OS_USE_CONSOLE					0			// Czy mam by� wykorzystywana konsola systemowa przez UART
	#define		OS_CONSOLE_UART_INSTANCE		USART2		// Kt�ry port UART ma by� wykorzystywany do konsoli
	
	// Watchdog
	#define		OS_USE_WATCHDOG					0			// W��czenia watchdoga podczas inisjalizacji i jego reset w Schedulerze
	#define		OS_USE_WATCHDOG_DIS_COMMAND		1			// Dodaj polecenie "wdt0" do wy��czania watchdoga (15B)

	// Czas
	#define		OS_USE_TIME						1			// Zegar czasu rzeczywistego dzia�aj�cy w tle (147B)
	#define		OS_USE_TIME_COMMAND				1			// Dodaje polecenie "time" do pokazywania czasu (963B)
	#define		OS_USE_TIMESET_COMMAND			1			// Dodaje polecenie "timeset" do ustawiania czasu z konsoli (772B)
	#define		OS_USE_TIME_RECOVERY			0			// Dodaje task Os_TimeRecovery do zapisywania i odczytywanie czasu w EEPROM 
	
	// Oszcz�dzanie energii
	// Wej�cie w tryb u�pienia nast�puje w Schedulerze je�eli �aden proces nie ma zaleg�ych wywo�a� (Pending = 0) oraz rejestr OS_SLEEP_GPIOR = 0.
	// Ka�dy proces lub funkcja chc�ca zablokowa� wej�cie w tryb u�pienia powinna wywo�a� OS_SLEEP_DISABLE, co powoduje zwi�kszenie OS_SLEEP_GPIOR o 1.
	// Kiedy proces chce zwolni� blokad�, powinien wywo�a� OS_SLEEP_ENABLE, co zmniejsza OS_SLEEP_GPIOR o 1.
	#define		OS_USE_SLEEP					0			// Tryb u�pienia
	#define		OS_SLEEP_GPIOR					GPIOR0		// Rejestr do licznika blokad u�pienia
	#define		OS_SLEEP_TIMER_TYPE				uint16_t	// Typ zmiennej do czasu u�pienia
	#define		OS_SLEEP_INDISE_SCHEDULER		1			// Wchodzenie w tryb u�pienia wewn�trz Schedulera (aby nie trzeba by�o tego robi� w main() lub w innych miejscach)
	
	// Debugowanie
	#define		OS_DEBUG_MESSAGES_SHOW			0			// Komunikaty u tworzeniu i zamykaniu task�w
	#define		OS_DEBUG_MESSAGES_TIMESTAMP		0			// W komunikatach o b��dach b�dzie podana data i godzina
	#define		OS_USE_TASK_IDENTIFY			1			// Identyfikacja task�w poprzez wyso�anie z argumentem Identify 
	#define		OS_TASK_MONITOR_USE				1			// Wy�wietlanie na UART tablicy task�w
	#define		OS_TASK_MONITOR_CNT				0			// Pokazywanie aktualnego licznika CNT poszczeg�lnych task�w
	#define		OS_TASK_MONITOR_MIN_MAX			0			// Pokazywanie czasu min i max proces�w
	#define		OS_TASK_MONITOR_AVG_PROC		1			// Pokazywanie czasu �redniego proces�w 
	#define		OS_TASK_MONITOR_TASKMAXCNT		1			// Pokazywanie najwi�kszej liczby task�w dzia�aj�cych jednocze�nie
	
	#define		OS_CONFIG_DONE
#endif

// ========================================
// Dev Board AVR-IoT
// ========================================

#if P_AVRIOT
	
	// Wyb�r generatora
	#define		OS_GENERATOR_ULP				1
	#define		OS_GENERATOR_XOSC32				0
	
	// Konfiguracja systemu
	#define		OS_TASK_MAXCOUNT				10			// Od tego zalezy rozmiar tablicy Task[] w RAM
	#define		OS_TICK_DELAY					100			// Okres timera systemowego w ms, zakres 1-1000
	typedef		uint16_t						Os_Timer_t;	// Typ zmiennej timer�w programowych, od tego zale�y maksymalny odliczany czas i zaj�to�� pami�ci
	#define		OS_MULTIPLE_TASKS_ALLOWED		0			// Mo�na dodawa� kilka razy ten sam task
	#define		OS_SHOW_RESET_SOURCE_AT_START	1			// Czy pokazywa� �r�d�o resetu na starcie
	#define		OS_SHOW_SPLASH_SCREEN_AT_START	1			// Czy pokazywa� logo systemu na starcie
	
	// Konsola systemowa
	#define		OS_USE_CONSOLE					0			// Czy mam by� wykorzystywana konsola systemowa przez UART
	#define		OS_CONSOLE_UART_INSTANCE		USART2		// Kt�ry port UART ma by� wykorzystywany do konsoli
	
	// Watchdog
	#define		OS_USE_WATCHDOG					0			// W��czenia watchdoga podczas inisjalizacji i jego reset w Schedulerze
	#define		OS_USE_WATCHDOG_DIS_COMMAND		1			// Dodaj polecenie "wdt0" do wy��czania watchdoga (15B)
	
	// Czas
	#define		OS_USE_TIME						1			// Zegar czasu rzeczywistego dzia�aj�cy w tle (147B)
	#define		OS_USE_TIME_COMMAND				1			// Dodaje polecenie "time" do pokazywania czasu (963B)
	#define		OS_USE_TIMESET_COMMAND			1			// Dodaje polecenie "timeset" do ustawiania czasu z konsoli (772B)
	#define		OS_USE_TIME_RECOVERY			0			// Dodaje task Os_TimeRecovery do zapisywania i odczytywanie czasu w EEPROM 
	
	// Oszcz�dzanie energii
	// Wej�cie w tryb u�pienia nast�puje w Schedulerze je�eli �aden proces nie ma zaleg�ych wywo�a� (Pending = 0) oraz rejestr OS_SLEEP_GPIOR = 0.
	// Ka�dy proces lub funkcja chc�ca zablokowa� wej�cie w tryb u�pienia powinna wywo�a� OS_SLEEP_DISABLE, co powoduje zwi�kszenie OS_SLEEP_GPIOR o 1.
	// Kiedy proces chce zwolni� blokad�, powinien wywo�a� OS_SLEEP_ENABLE, co zmniejsza OS_SLEEP_GPIOR o 1.
	#define		OS_USE_SLEEP					0			// Tryb u�pienia
	#define		OS_SLEEP_GPIOR					GPIOR0		// Rejestr do licznika blokad u�pienia
	#define		OS_SLEEP_TIMER_TYPE				uint16_t	// Typ zmiennej do czasu u�pienia
	#define		OS_SLEEP_INDISE_SCHEDULER		1			// Wchodzenie w tryb u�pienia wewn�trz Schedulera (aby nie trzeba by�o tego robi� w main() lub w innych miejscach)
	
	// Debugowanie
	#define		OS_DEBUG_MESSAGES_SHOW			0			// Komunikaty u tworzeniu i zamykaniu task�w
	#define		OS_DEBUG_MESSAGES_TIMESTAMP		0			// W komunikatach o b��dach b�dzie podana data i godzina
	#define		OS_USE_TASK_IDENTIFY			1			// Identyfikacja task�w poprzez wyso�anie z argumentem Identify 
	#define		OS_TASK_MONITOR_USE				1			// Wy�wietlanie na UART tablicy task�w
	#define		OS_TASK_MONITOR_CNT				0			// Pokazywanie aktualnego licznika CNT poszczeg�lnych task�w
	#define		OS_TASK_MONITOR_MIN_MAX			0			// Pokazywanie czasu min i max proces�w
	#define		OS_TASK_MONITOR_AVG_PROC		1			// Pokazywanie czasu �redniego proces�w 
	#define		OS_TASK_MONITOR_TASKMAXCNT		1			// Pokazywanie najwi�kszej liczby task�w dzia�aj�cych jednocze�nie
	
	#define		OS_CONFIG_DONE
#endif

// ========================================
// Dev Board Curiosity ATmega4809
// ========================================

#if P_CURIO4809
	
	// Wyb�r generatora
	#define		OS_GENERATOR_ULP				1
	#define		OS_GENERATOR_XOSC32				0
	
	// Konfiguracja systemu
	#define		OS_TASK_MAXCOUNT				10			// Od tego zalezy rozmiar tablicy Task[] w RAM
	#define		OS_TICK_DELAY					100			// Okres timera systemowego w ms, zakres 1-1000
	typedef		uint16_t						Os_Timer_t;	// Typ zmiennej timer�w programowych, od tego zale�y maksymalny odliczany czas i zaj�to�� pami�ci
	#define		OS_MULTIPLE_TASKS_ALLOWED		0			// Mo�na dodawa� kilka razy ten sam task
	#define		OS_SHOW_RESET_SOURCE_AT_START	1			// Czy pokazywa� �r�d�o resetu na starcie
	#define		OS_SHOW_SPLASH_SCREEN_AT_START	1			// Czy pokazywa� logo systemu na starcie
	
	// Konsola systemowa
	#define		OS_USE_CONSOLE					0			// Czy mam by� wykorzystywana konsola systemowa przez UART
	#define		OS_CONSOLE_UART_INSTANCE		USART3		// Kt�ry port UART ma by� wykorzystywany do konsoli

	// Watchdog
	#define		OS_USE_WATCHDOG					0			// W��czenia watchdoga podczas inisjalizacji i jego reset w Schedulerze
	#define		OS_USE_WATCHDOG_DIS_COMMAND		1			// Dodaj polecenie "wdt0" do wy��czania watchdoga (15B)
	
	// Czas
	#define		OS_USE_TIME						1			// Zegar czasu rzeczywistego dzia�aj�cy w tle (147B)
	#define		OS_USE_TIME_COMMAND				1			// Dodaje polecenie "time" do pokazywania czasu (963B)
	#define		OS_USE_TIMESET_COMMAND			1			// Dodaje polecenie "timeset" do ustawiania czasu z konsoli (772B)
	#define		OS_USE_TIME_RECOVERY			0			// Dodaje task Os_TimeRecovery do zapisywania i odczytywanie czasu w EEPROM 
	
	// Oszcz�dzanie energii
	// Wej�cie w tryb u�pienia nast�puje w Schedulerze je�eli �aden proces nie ma zaleg�ych wywo�a� (Pending = 0) oraz rejestr OS_SLEEP_GPIOR = 0.
	// Ka�dy proces lub funkcja chc�ca zablokowa� wej�cie w tryb u�pienia powinna wywo�a� OS_SLEEP_DISABLE, co powoduje zwi�kszenie OS_SLEEP_GPIOR o 1.
	// Kiedy proces chce zwolni� blokad�, powinien wywo�a� OS_SLEEP_ENABLE, co zmniejsza OS_SLEEP_GPIOR o 1.
	#define		OS_USE_SLEEP					0			// Tryb u�pienia
	#define		OS_SLEEP_GPIOR					GPIOR0		// Rejestr do licznika blokad u�pienia
	#define		OS_SLEEP_TIMER_TYPE				uint16_t	// Typ zmiennej do czasu u�pienia
	#define		OS_SLEEP_INDISE_SCHEDULER		1			// Wchodzenie w tryb u�pienia wewn�trz Schedulera (aby nie trzeba by�o tego robi� w main() lub w innych miejscach)
	
	// Debugowanie
	#define		OS_DEBUG_MESSAGES_SHOW			0			// Komunikaty u tworzeniu i zamykaniu task�w
	#define		OS_DEBUG_MESSAGES_TIMESTAMP		0			// W komunikatach o b��dach b�dzie podana data i godzina
	#define		OS_USE_TASK_IDENTIFY			1			// Identyfikacja task�w poprzez wyso�anie z argumentem Identify 
	#define		OS_TASK_MONITOR_USE				1			// Wy�wietlanie na UART tablicy task�w
	#define		OS_TASK_MONITOR_CNT				0			// Pokazywanie aktualnego licznika CNT poszczeg�lnych task�w
	#define		OS_TASK_MONITOR_MIN_MAX			0			// Pokazywanie czasu min i max proces�w
	#define		OS_TASK_MONITOR_AVG_PROC		1			// Pokazywanie czasu �redniego proces�w 
	#define		OS_TASK_MONITOR_TASKMAXCNT		1			// Pokazywanie najwi�kszej liczby task�w dzia�aj�cych jednocze�nie
	
	#define		OS_CONFIG_DONE
#endif

// ========================================
// Dev Board XNANO
// ========================================

#if B_XNANO
	// Wyb�r generatora
	#define		OS_GENERATOR_ULP				1
	#define		OS_GENERATOR_XOSC32				0
	
	// Konfiguracja systemu
	#define		OS_TASK_MAXCOUNT				10			// Od tego zalezy rozmiar tablicy Task[] w RAM
	#define		OS_TICK_DELAY					100			// Okres timera systemowego w ms, zakres 1-1000
	typedef		uint16_t						Os_Timer_t;	// Typ zmiennej timer�w programowych, od tego zale�y maksymalny odliczany czas i zaj�to�� pami�ci
	#define		OS_MULTIPLE_TASKS_ALLOWED		0			// Mo�na dodawa� kilka razy ten sam task
	#define		OS_SHOW_RESET_SOURCE_AT_START	1			// Czy pokazywa� �r�d�o resetu na starcie
	#define		OS_SHOW_SPLASH_SCREEN_AT_START	1			// Czy pokazywa� logo systemu na starcie
	
	// Konsola systemowa
	#define		OS_USE_CONSOLE					0			// Czy mam by� wykorzystywana konsola systemowa przez UART
	#define		OS_CONSOLE_UART_INSTANCE		USART0		// Kt�ry port UART ma by� wykorzystywany do konsoli
	
	// Watchdog
	#define		OS_USE_WATCHDOG					0			// W��czenia watchdoga podczas inisjalizacji i jego reset w Schedulerze
	#define		OS_USE_WATCHDOG_DIS_COMMAND		1			// Dodaj polecenie "wdt0" do wy��czania watchdoga (15B)
	
	// Czas
	#define		OS_USE_TIME						1			// Zegar czasu rzeczywistego dzia�aj�cy w tle (147B)
	#define		OS_USE_TIME_COMMAND				1			// Dodaje polecenie "time" do pokazywania czasu (963B)
	#define		OS_USE_TIMESET_COMMAND			1			// Dodaje polecenie "timeset" do ustawiania czasu z konsoli (772B)
	#define		OS_USE_TIME_RECOVERY			0			// Dodaje task Os_TimeRecovery do zapisywania i odczytywanie czasu w EEPROM 
	
	// Oszcz�dzanie energii
	// Wej�cie w tryb u�pienia nast�puje w Schedulerze je�eli �aden proces nie ma zaleg�ych wywo�a� (Pending = 0) oraz rejestr OS_SLEEP_GPIOR = 0.
	// Ka�dy proces lub funkcja chc�ca zablokowa� wej�cie w tryb u�pienia powinna wywo�a� OS_SLEEP_DISABLE, co powoduje zwi�kszenie OS_SLEEP_GPIOR o 1.
	// Kiedy proces chce zwolni� blokad�, powinien wywo�a� OS_SLEEP_ENABLE, co zmniejsza OS_SLEEP_GPIOR o 1.
	#define		OS_USE_SLEEP					0			// Tryb u�pienia
	#define		OS_SLEEP_GPIOR					GPIOR0		// Rejestr do licznika blokad u�pienia
	#define		OS_SLEEP_TIMER_TYPE				uint16_t	// Typ zmiennej do czasu u�pienia
	#define		OS_SLEEP_INDISE_SCHEDULER		1			// Wchodzenie w tryb u�pienia wewn�trz Schedulera (aby nie trzeba by�o tego robi� w main() lub w innych miejscach)
	
	// Debugowanie
	#define		OS_DEBUG_MESSAGES_SHOW			0			// Komunikaty u tworzeniu i zamykaniu task�w
	#define		OS_DEBUG_MESSAGES_TIMESTAMP		0			// W komunikatach o b��dach b�dzie podana data i godzina
	#define		OS_USE_TASK_IDENTIFY			1			// Identyfikacja task�w poprzez wyso�anie z argumentem Identify 
	#define		OS_TASK_MONITOR_USE				1			// Wy�wietlanie na UART tablicy task�w
	#define		OS_TASK_MONITOR_CNT				0			// Pokazywanie aktualnego licznika CNT poszczeg�lnych task�w
	#define		OS_TASK_MONITOR_MIN_MAX			0			// Pokazywanie czasu min i max proces�w
	#define		OS_TASK_MONITOR_AVG_PROC		1			// Pokazywanie czasu �redniego proces�w 
	#define		OS_TASK_MONITOR_TASKMAXCNT		1			// Pokazywanie najwi�kszej liczby task�w dzia�aj�cych jednocze�nie
	
	#define		OS_CONFIG_DONE
#endif

// ========================================
// Error handling
// ========================================

#ifndef OS_CONFIG_DONE
	#error "Missing config"
#endif



#endif /* UCOSMOS_CONFIG_H_ */