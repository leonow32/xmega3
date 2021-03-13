/*
UWAGI I POMYS£Y
		-	

CHANGELOG
1.18	+	Dodanie p³ytki Lock v001
1.17	+	Porz¹dki w kodzie programu
1.16	+	Dodanie p³ytki Relay
1.15	+	Dodanie p³ytki Door Lock v003 (DL)
1.14	+	AVR-IoT: zdalna konsola
1.13	+	Dodanie p³ytki MRUSB_v003 w wersji RMVCP_v003
1.12	+	Dodanie obs³ugi p³ytki XNANO
1.11	+	Piny TX i RX dla p³ytki AVR-IoT jako zwyk³e GPIO bez UART
1.10	+	Piny PWM i INT dla p³ytki AVR-IoT
1.09	+	Taski demonstracyjne do mrugania diodami na AVR-IoT
1.08	*	Przedniesienie definicji linii I2C-POWER do biblioteki I2C
1.07	+	Dostosowanie do p³ytki AVR-IoT
1.06	+	Dodanie poleceñ do usypiania
1.05	+	Dodanie pinów p³ytki MIFARE v002
1.04	+	Dodanie obs³ugi definicji B_xxxx w zale¿noœci od p³ytki, na któr¹ kompilujemy program, w zale¿noœci od ustawienia managera konfiguracji
1.03	*	Wydzielenie definicji dotycz¹cych ³adowarki baterii MCP73871 do pliku battery_mcp73871.cpp/h
1.02	+	Dodanie wszystkich wejœæ i wyjœæ p³ytki Safli RPM v005
1.01	+	RELAY_A_CHECK
		+	RELAY_B_CHECK
1.00	+	Pierwsza wersja
*/

#ifndef PERIPHERALS_H_
#define PERIPHERALS_H_

#include <avr/io.h>

#if C_CONSOLE
	#include "../console/console.h"
#endif

#if C_UART
	#include "../uart/uart.h"
#endif


#if B_AVRIOT
	
	// Diody LED
	#define		LED_RED_ON				VPORTD.OUT	|=  PIN0_bm
	#define		LED_RED_OFF				VPORTD.OUT	&= ~PIN0_bm
	#define		LED_RED_TGL				VPORTD.OUT	^=  PIN0_bm
	#define		LED_RED_INIT			VPORTD.DIR	|=	PIN0_bm;	PORTD.PIN0CTRL = PORT_INVEN_bm;

	#define		LED_YELLOW_ON			VPORTD.OUT	|=  PIN1_bm
	#define		LED_YELLOW_OFF			VPORTD.OUT	&= ~PIN1_bm
	#define		LED_YELLOW_TGL			VPORTD.OUT	^=  PIN1_bm
	#define		LED_YELLOW_INIT			VPORTD.DIR	|=	PIN1_bm;	PORTD.PIN1CTRL = PORT_INVEN_bm;

	#define		LED_GREEN_ON			VPORTD.OUT	|=  PIN2_bm
	#define		LED_GREEN_OFF			VPORTD.OUT	&= ~PIN2_bm
	#define		LED_GREEN_TGL			VPORTD.OUT	^=  PIN2_bm
	#define		LED_GREEN_INIT			VPORTD.DIR	|=	PIN2_bm;	PORTD.PIN2CTRL = PORT_INVEN_bm;

	#define		LED_BLUE_ON				VPORTD.OUT	|=  PIN3_bm
	#define		LED_BLUE_OFF			VPORTD.OUT	&= ~PIN3_bm
	#define		LED_BLUE_TGL			VPORTD.OUT	^=  PIN3_bm
	#define		LED_BLUE_INIT			VPORTD.DIR	|=	PIN3_bm;	PORTD.PIN3CTRL = PORT_INVEN_bm;

	// Przyciski
	#define		KEY_SW0_READ			(VPORTF.IN	&	PIN6_bm)
	#define		KEY_SW0_INIT			PORTF.PIN6CTRL = PORT_INVEN_bm | PORT_PULLUPEN_bm;

	#define		KEY_SW1_READ			(VPORTF.IN	&	PIN5_bm)
	#define		KEY_SW1_INIT			PORTF.PIN5CTRL = PORT_INVEN_bm | PORT_PULLUPEN_bm;

	// Inne piny
	#define		PWM_ON					VPORTD.OUT	|=  PIN4_bm
	#define		PWM_OFF					VPORTD.OUT	&= ~PIN4_bm
	#define		PWM_INIT				VPORTD.DIR	|=	PIN4_bm

	#define		INT_ON					VPORTD.OUT	|=  PIN6_bm
	#define		INT_OFF					VPORTD.OUT	&= ~PIN6_bm
	#define		INT_INIT				VPORTD.DIR	|=	PIN6_bm				
	
	// Funkcje
	void Peripherals_Init(void);
	
	// Taski
	#define		PERIPHERALS_USE_DEMO_TASKS		1
	#if PERIPHERALS_USE_DEMO_TASKS
		task_t Peripherals_TaskRed(runmode_t RunMode);
		task_t Peripherals_TaskYellow(runmode_t RunMode);
		task_t Peripherals_TaskGreen(runmode_t RunMode);
		task_t Peripherals_TaskBlue(runmode_t RunMode);
	#endif
	
	// Polecenie wywo³ywane z konsoli
	#define		PERIPHERALS_USE_DEMO_COMMANDS	1
	#if PERIPHERALS_USE_DEMO_COMMANDS
		void Peripherals_Demo_ioset(uint8_t argc, uint8_t * argv[]);
		void Peripherals_Demo_ioget(uint8_t argc, uint8_t * argv[]);
		//void Peripherals_Echo(uint8_t argc, uint8_t * argv[]);
	#endif

#endif


#endif /* PERIPHERALS_H_ */
