// Wersja 2.04

#ifndef SPI_MASTER_CONFIG_H_
#define SPI_MASTER_CONFIG_H_

#include <avr/io.h>
#include "../config/config.h"

// ========================================
// Template
// ========================================

#if PRODUCT_TEMPLATE
	#if HW_CPU_ATtinyXX12 || HW_CPU_ATtinyXX14
		#define		SPI_PORTA_13					0
	#endif
	
	#if HW_CPU_ATtinyXX16 || HW_CPU_ATtinyXX17
		#define		SPI_PORTA_13					0
		#define		SPI_PORTC_02					0
	#endif
	
	#if HW_CPU_ATtinyXX24 || HW_CPU_ATtinyXX26 || HW_CPU_ATtinyXX27
		#define		SPI_PORTA_13					1
		#define		SPI_PORTC_02					0
	#endif
	
	#if HW_CPU_ATmegaXX09
		#define		SPI_PORTA_46					0
		#define		SPI_PORTC_02					1
		#define		SPI_PORTE_02					0
	#endif
	
	#if HW_CPU_ATmegaXX08_28pin || HW_CPU_ATmegaXX08_32pin
		#define		SPI_PORTA_46					0
		#define		SPI_PORTC_02					1
	#endif
	
	#define			SPI_MASTER_USE_DEMO_COMMANDS	1
	#define			SPI_MASTER_CONFIG_DONE
#endif

// ========================================
// Dev Board AVR-IoT
// ========================================

#if PRODUCT_AVRIOT
	#define			SPI_PORTA_46					1
	#define			SPI_MASTER_USE_DEMO_COMMANDS	1
	
	// Pinout of CS pin only for demo commands (all SPI devices should have configuration of CS pin in their ouw config files)
	#if SPI_MASTER_USE_DEMO_COMMANDS
		#define		SPI_DEMO_DIR_SET				VPORTC.DIR	|=	PIN3_bm
		#define		SPI_DEMO_CHIP_SELECT			VPORTC.OUT	&= ~PIN3_bm
		#define		SPI_DEMO_CHIP_DESELECT			VPORTC.OUT	|=  PIN3_bm
	#endif
	
	#define			SPI_MASTER_CONFIG_DONE
#endif

// ========================================
// Dev Board Curiosity ATtiny1627
// ========================================

#if PRODUCT_CURIOSITY_T1627
	#define			SPI_PORTA_13					0
	#define			SPI_PORTC_02					1
	#define			SPI_MASTER_USE_DEMO_COMMANDS	1
	
	// Pinout of CS pin only for demo commands (all SPI devices should have configuration of CS pin in their ouw config files)
	#if SPI_MASTER_USE_DEMO_COMMANDS
		#define		SPI_DEMO_DIR_SET				VPORTA.DIR	|=	PIN4_bm
		#define		SPI_DEMO_CHIP_SELECT			VPORTA.OUT	&= ~PIN4_bm
		#define		SPI_DEMO_CHIP_DESELECT			VPORTA.OUT	|=  PIN4_bm
	#endif
	
	#define			SPI_MASTER_CONFIG_DONE
#endif

// ========================================
// Error handling
// ========================================

#ifndef SPI_MASTER_CONFIG_DONE
	#error "Missing config"
#endif


#endif /* SPI_MASTER_CONFIG_H_ */