/*
CHANGELOG
2.0.0		Comments translated to English
*/

#ifndef PERIPHERALS_H_
#define PERIPHERALS_H_

#include <avr/io.h>
#include "peripherals_config.h"

#if COMPONENT_CONSOLE
	#include	"../console/console.h"
#endif

#if COMPONENT_PRINT
	#include	"../print/print.h"
#else
	#error		"This module requires PRINT component"
#endif

#if COMPONENT_UCOSMOS
	#include	"../uCosmos/uCosmos.h"
#endif

// ========================================
// Dev Board AVR-IoT
// ========================================

#if PRODUCT_AVRIOT
	
	// Functions
	void Peripherals_Init(void);
	
	// Tasks
	#if PERIPHERALS_USE_DEMO_TASKS
		task_t Peripherals_TaskRed(runmode_t RunMode);
		task_t Peripherals_TaskYellow(runmode_t RunMode);
		task_t Peripherals_TaskGreen(runmode_t RunMode);
		task_t Peripherals_TaskBlue(runmode_t RunMode);
	#endif
	
	// Console commands
	#if PERIPHERALS_USE_DEMO_COMMANDS
		void Peripherals_Demo_ioset(uint8_t argc, uint8_t * argv[]);
		void Peripherals_Demo_ioget(uint8_t argc, uint8_t * argv[]);
	#endif
	
#endif

// ========================================
// Dev Board Curiosity ATmega4809
// ========================================

#if PRODUCT_CURIOSITY_M4809
	
	// Functions
	void Peripherals_Init(void);
	
	// Tasks
	#define		PERIPHERALS_USE_DEMO_TASKS		1
	#if PERIPHERALS_USE_DEMO_TASKS
		task_t Peripherals_TaskYellow(runmode_t RunMode);
	#endif
	
	// Console commands
	#define		PERIPHERALS_USE_DEMO_COMMANDS	1
	#if PERIPHERALS_USE_DEMO_COMMANDS
		void Peripherals_Demo_ioset(uint8_t argc, uint8_t * argv[]);
		void Peripherals_Demo_ioget(uint8_t argc, uint8_t * argv[]);
	#endif
	
#endif

// ========================================
// Dev Board Curiosity ATtiny3217
// ========================================

#if PRODUCT_CURIOSITY_T3217
	
	// Functions
	void Peripherals_Init(void);
	
	// Tasks
	#define		PERIPHERALS_USE_DEMO_TASKS		1
	#if PERIPHERALS_USE_DEMO_TASKS
		task_t Peripherals_TaskYellow(runmode_t RunMode);
	#endif
	
	// Console commands
	#define		PERIPHERALS_USE_DEMO_COMMANDS	1
	#if PERIPHERALS_USE_DEMO_COMMANDS
		void Peripherals_Demo_ioset(uint8_t argc, uint8_t * argv[]);
		void Peripherals_Demo_ioget(uint8_t argc, uint8_t * argv[]);
	#endif
	
#endif

// ========================================
// Dev Board XNANO
// ========================================

#if PRODUCT_XNANO
	
	// Functions
	void Peripherals_Init(void);
	
	// Tasks
	#if PERIPHERALS_USE_DEMO_TASKS
		task_t Peripherals_TaskYellow(runmode_t RunMode);
	#endif
	
	// Console commands
	#if PERIPHERALS_USE_DEMO_COMMANDS
		void Peripherals_Demo_ioset(uint8_t argc, uint8_t * argv[]);
		void Peripherals_Demo_ioget(uint8_t argc, uint8_t * argv[]);
	#endif

#endif


#endif /* PERIPHERALS_H_ */
