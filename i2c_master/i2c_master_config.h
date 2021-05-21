// Version 3.0.0

#ifndef I2C_MASTER_CONFIG_H_
#define I2C_MASTER_CONFIG_H_

#include "../config/config.h"

// ========================================
// Template
// ========================================

#if PRODUCT_TEMPLATE
	#if HW_CPU_ATtinyXX12
		#define				I2C_PORTA_12			0
	#endif
	
	#if HW_CPU_ATtinyXX14 || HW_CPU_ATtinyXX16 || HW_CPU_ATtinyXX17
		#define				I2C_PORTA_12			0
		#define				I2C_PORTB_01			1
	#endif
	
	#if HW_CPU_ATtinyXX24 || HW_CPU_ATtinyXX26 || HW_CPU_ATtinyXX27
		#define				I2C_PORTB_01			1
	#endif
	
	#if HW_CPU_ATmegaXX08_28pin || HW_CPU_ATmegaXX08_32pin || HW_CPU_ATmegaXX09
		#define				I2C_PORTA_23			1
		#define				I2C_PORTC_23			0
	#endif
	
	#define		I2C_MASTER_SCL_FREQUENCY			100000
	#define		I2C_MASTER_USE_DEMO_COMMANDS		1
	#define		I2C_MASTER_CONFIG_DONE
#endif

// ========================================
// Demo Display SH1106
// ========================================

#if PRODUCT_SH1106
	#define		I2C_PORTB_01						1
	#define		I2C_MASTER_SCL_FREQUENCY			750000
	#define		I2C_MASTER_USE_DEMO_COMMANDS		1
	#define		I2C_MASTER_CONFIG_DONE
#endif

// ========================================
// Dev Board AVR-IoT
// ========================================

#if PRODUCT_AVRIOT
	#define		I2C_PORTA_23						1
	#define		I2C_MASTER_SCL_FREQUENCY			157000
	#define		I2C_MASTER_USE_DEMO_COMMANDS		1
	#define		I2C_MASTER_CONFIG_DONE
#endif

// ========================================
// Dev Board Curiosity ATtiny1627
// ========================================

#if PRODUCT_CURIOSITY_T1627
	#define		I2C_PORTB_01						1
	#define		I2C_MASTER_SCL_FREQUENCY			157000
	#define		I2C_MASTER_USE_DEMO_COMMANDS		1
	#define		I2C_MASTER_CONFIG_DONE
#endif

// ========================================
// Error handling
// ========================================

#ifndef I2C_MASTER_CONFIG_DONE
	#error "Missing config"
#endif



#endif /* I2C_MASTER_CONFIG_H_ */