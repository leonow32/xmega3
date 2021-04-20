// Version 2.0.0

#ifndef SPI_MEM_CONFIG_H_
#define SPI_MEM_CONFIG_H_

// ========================================
// Template
// ========================================

#if TEMPLATE
	
	
#endif

// ========================================
// Dev Board AVR-IoT
// ========================================

#if PRODUCT_AVRIOT
	
	// Address
	#define		MEM24_ADDRESS_WRITE			0xA0
	#define		MEM24_ADDRESS_READ			0xA1
	
	// Values specific for 24LC512 (needed only for page mode operation)
	#define		MEM24_SIZE					65536
	#define		MEM24_PAGE_SIZE				128
	#define		MEM24_PAGE_CNT				512
	
	// Additional stuff
	#define		MEM24_MULTIPLE_PAGE_WRITE	1
	#define		MEM24_USE_DEMO_COMMANDS		1
	
	#define		MEM24_CONFIG_DONE
	
#endif

// ========================================
// Error handling
// ========================================

#ifndef MEM24_CONFIG_DONE
	#error "Missing config"
#endif

#endif /* SPI_MEM_CONFIG_H_ */