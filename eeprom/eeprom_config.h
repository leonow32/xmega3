// Wersja 1.08

#ifndef EEPROM_CONFIG_H_
#define EEPROM_CONFIG_H_

// ========================================
// Template
// ========================================

#if P_TEMPLATE
	#define		EEPROM_USE_COMMAND_DUMP				1
	#define		EEPROM_USE_DEMO_COMMANDS			1
	#define		EEPROM_CONFIG_DONE
#endif

// ========================================
// Dev Board AVR-IoT
// ========================================

#if P_AVRIOT
	#define		EEPROM_USE_COMMAND_DUMP				1
	#define		EEPROM_USE_DEMO_COMMANDS			1
	#define		EEPROM_CONFIG_DONE
#endif

// ========================================
// Dev Board Curiosity ATmega4809
// ========================================

#if P_CURIOSITY_M4809
	#define		EEPROM_USE_COMMAND_DUMP				1
	#define		EEPROM_USE_DEMO_COMMANDS			1
	#define		EEPROM_CONFIG_DONE
#endif

// ========================================
// Dev Board XNANO
// ========================================

#if P_XNANO
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