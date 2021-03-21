/*
UWAGI I POMYS�Y
		-	

CHANGELOG
1.18	+	Dodanie p�ytki Lock v001
1.17	+	Porz�dki w kodzie programu
1.16	+	Dodanie p�ytki Relay
1.15	+	Dodanie p�ytki Door Lock v003 (DL)
1.14	+	AVR-IoT: zdalna konsola
1.13	+	Dodanie p�ytki MRUSB_v003 w wersji RMVCP_v003
1.12	+	Dodanie obs�ugi p�ytki XNANO
1.11	+	Piny TX i RX dla p�ytki AVR-IoT jako zwyk�e GPIO bez UART
1.10	+	Piny PWM i INT dla p�ytki AVR-IoT
1.09	+	Taski demonstracyjne do mrugania diodami na AVR-IoT
1.08	*	Przedniesienie definicji linii I2C-POWER do biblioteki I2C
1.07	+	Dostosowanie do p�ytki AVR-IoT
1.06	+	Dodanie polece� do usypiania
1.05	+	Dodanie pin�w p�ytki MIFARE v002
1.04	+	Dodanie obs�ugi definicji B_xxxx w zale�no�ci od p�ytki, na kt�r� kompilujemy program, w zale�no�ci od ustawienia managera konfiguracji
1.03	*	Wydzielenie definicji dotycz�cych �adowarki baterii MCP73871 do pliku battery_mcp73871.cpp/h
1.02	+	Dodanie wszystkich wej�� i wyj�� p�ytki Safli RPM v005
1.01	+	RELAY_A_CHECK
		+	RELAY_B_CHECK
1.00	+	Pierwsza wersja
*/

#ifndef PERIPHERALS_H_
#define PERIPHERALS_H_

#include <avr/io.h>
#include "peripherals_config.h"

#if C_CONSOLE
	#include	"../console/console.h"
#endif

#if C_PRINT
	#include	"../print/print.h"
#else
	#error		"This module requires PRINT component"
#endif

// ========================================
// Dev Board AVR-IoT
// ========================================

#if P_AVRIOT
	
	// Funkcje
	void Peripherals_Init(void);
	
	// Taski
	#if PERIPHERALS_USE_DEMO_TASKS
		task_t Peripherals_TaskRed(runmode_t RunMode);
		task_t Peripherals_TaskYellow(runmode_t RunMode);
		task_t Peripherals_TaskGreen(runmode_t RunMode);
		task_t Peripherals_TaskBlue(runmode_t RunMode);
	#endif
	
	// Polecenie wywo�ywane z konsoli
	#if PERIPHERALS_USE_DEMO_COMMANDS
		void Peripherals_Demo_ioset(uint8_t argc, uint8_t * argv[]);
		void Peripherals_Demo_ioget(uint8_t argc, uint8_t * argv[]);
	#endif
	
#endif

// ========================================
// Dev Board Curiosity ATmega4809
// ========================================

#if P_CURIO4809
	
	// Funkcje
	void Peripherals_Init(void);
	
	// Taski
	#define		PERIPHERALS_USE_DEMO_TASKS		1
	#if PERIPHERALS_USE_DEMO_TASKS
		task_t Peripherals_TaskYellow(runmode_t RunMode);
	#endif
	
	// Polecenie wywo�ywane z konsoli
	#define		PERIPHERALS_USE_DEMO_COMMANDS	1
	#if PERIPHERALS_USE_DEMO_COMMANDS
		void Peripherals_Demo_ioset(uint8_t argc, uint8_t * argv[]);
		void Peripherals_Demo_ioget(uint8_t argc, uint8_t * argv[]);
	#endif
	
#endif

// ========================================
// Dev Board XNANO
// ========================================

#if P_XNANO
	
	// Funkcje
	void Peripherals_Init(void);
	
	// Taski
	#if PERIPHERALS_USE_DEMO_TASKS
		task_t Peripherals_TaskYellow(runmode_t RunMode);
	#endif
	
	// Polecenie wywo�ywane z konsoli
	#if PERIPHERALS_USE_DEMO_COMMANDS
		void Peripherals_Demo_ioset(uint8_t argc, uint8_t * argv[]);
		void Peripherals_Demo_ioget(uint8_t argc, uint8_t * argv[]);
	#endif

#endif


#endif /* PERIPHERALS_H_ */
