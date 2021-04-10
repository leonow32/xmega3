// Wersja 1.08

#ifndef EEPROM_CONFIG_H_
#define EEPROM_CONFIG_H_

// ========================================
// Template
// ========================================

#if PRODUCT_TEMPLATE
	#define		EEPROM_USE_COMMAND_DUMP				1
	#define		EEPROM_USE_DEMO_COMMANDS			1
	#define		EEPROM_CONFIG_DONE
#endif

// ========================================
// Dev Board AVR-IoT
// ========================================

#if PRODUCT_AVRIOT
	#define		EEPROM_USE_COMMAND_DUMP				1
	#define		EEPROM_USE_DEMO_COMMANDS			1
	#define		EEPROM_CONFIG_DONE
#endif

// ========================================
// Dev Board Curiosity ATmega4809
// ========================================

#if PRODUCT_CURIOSITY_M4809
	#define		EEPROM_USE_COMMAND_DUMP				1
	#define		EEPROM_USE_DEMO_COMMANDS			1
	#define		EEPROM_CONFIG_DONE
#endif

// ========================================
// Dev Board Curiosity ATtiny1627
// ========================================

#if PRODUCT_CURIOSITY_T1627
	#define		EEPROM_USE_COMMAND_DUMP				1
	#define		EEPROM_USE_DEMO_COMMANDS			1
	#define		EEPROM_CONFIG_DONE
#endif

// ========================================
// Dev Board Curiosity ATtiny3217
// ========================================

#if PRODUCT_CURIOSITY_T3217
	#define		EEPROM_USE_COMMAND_DUMP				1
	#define		EEPROM_USE_DEMO_COMMANDS			1
	#define		EEPROM_CONFIG_DONE
#endif

// ========================================
// Dev Board XNANO
// ========================================

#if PRODUCT_XNANO
	#define		EEPROM_USE_COMMAND_DUMP				1
	#define		EEPROM_USE_DEMO_COMMANDS			1
	#define		EEPROM_CONFIG_DONE
#endif

// ========================================
// Error handling
// ========================================

#ifndef EEPROM_CONFIG_DONE
	#error "Missing config"
#endif

#endif /* EEPROM_CONFIG_H_ */