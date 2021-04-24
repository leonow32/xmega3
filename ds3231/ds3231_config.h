// Version 2.0.0

#ifndef DS3231_CONFIG_H_
#define DS3231_CONFIG_H_

// ========================================
// Template
// ========================================

#if TEMPLATE
	
	// Address
	#define		DS3231_ADDRESS_WRITE		0xD0
	#define		DS3231_ADDRESS_READ			0xD1
	
	#define		DS3231_CONFIG_DONE
	
#endif

// ========================================
// Dev Board AVR-IoT
// ========================================

#if PRODUCT_AVRIOT
	
	// Address
	#define		DS3231_ADDRESS_WRITE		0xD0
	#define		DS3231_ADDRESS_READ			0xD1
	
	// Additional stuff
	#define		DS3231_USE_DEMO_COMMANDS	1
	
	#define		DS3231_CONFIG_DONE
	
#endif

// ========================================
// Error handling
// ========================================

#ifndef DS3231_CONFIG_DONE
	#error "Missing config"
#endif

#endif /* SPI_MEM_CONFIG_H_ */