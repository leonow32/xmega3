// Wersja 2.04

#ifndef SPI_MASTER_CONFIG_H_
#define SPI_MASTER_CONFIG_H_

#include <avr/io.h>
#include "../config/config.h"

// ========================================
// Template
// ========================================

#if TEMPLATE
	#if HW_CPU_ATtinyXX12 || HW_CPU_ATtinyXX14
		#define			SPI_PORTA_13			0
	#endif
	
	#if HW_CPU_ATtinyXX16 || HW_CPU_ATtinyXX17
		#define			SPI_PORTA_13			0
		#define			SPI_PORTC_02			0
	#endif
	
	#if HW_CPU_ATmegaXX09
		#define			SPI_PORTA_46			0
		#define			SPI_PORTC_02			1
		#define			SPI_PORTE_02			0
	#endif
	
	#if HW_CPU_ATmegaXX08_28pin || HW_CPU_ATmegaXX08_32pin
		#define			SPI_PORTA_46			0
		#define			SPI_PORTC_02			1
	#endif
	
	#define		SPI_MASTER_USE_DEMO_COMMANDS	1
	#define		SPI_MASTER_CONFIG_DONE
#endif

// ========================================
// Dev Board AVR-IoT
// ========================================

#if P_AVRIOT
	#define		SPI_PORTA_46					1
	#define		SPI_MASTER_USE_DEMO_COMMANDS	1
	#define		SPI_MASTER_CONFIG_DONE
#endif

// ========================================
// Error handling
// ========================================

#ifndef SPI_MASTER_CONFIG_DONE
	#error "Missing config"
#endif


#endif /* SPI_MASTER_CONFIG_H_ */