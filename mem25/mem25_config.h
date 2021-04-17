// Version 2.0.0

#ifndef SPI_MEM_CONFIG_H_
#define SPI_MEM_CONFIG_H_

// ========================================
// Template
// ========================================

#if TEMPLATE
	
	// Pinout
	#define		MEM25_CHIP_SELECT_INIT		VPORTC.DIR	|=	PIN3_bm
	#define		MEM25_CHIP_SELECT			VPORTC.OUT	&= ~PIN3_bm
	#define		MEM25_CHIP_DESELECT			VPORTC.OUT	|=  PIN3_bm
	
	// Values specific for 25LC512
	#define		MEM25_SIZE					65536
	#define		MEM25_PAGE_SIZE				128
	#define		MEM25_PAGE_CNT				512
	
	// Additional stuff
	#define		MEM25_AUTO_SLEEP_MODE		1
	#define		MEM25_MULTIPLE_PAGE_WRITE	1
	#define		MEM25_USE_DEMO_COMMANDS		1
	
	#define		MEM25_CONFIG_DONE
	
#endif

// ========================================
// Dev Board AVR-IoT
// ========================================

#if PRODUCT_AVRIOT
	
	// Pinout
	#define		MEM25_CHIP_SELECT_INIT		VPORTC.DIR	|=	PIN3_bm
	#define		MEM25_CHIP_SELECT			VPORTC.OUT	&= ~PIN3_bm
	#define		MEM25_CHIP_DESELECT			VPORTC.OUT	|=  PIN3_bm
	
	// Values specific for 25LC512
	#define		MEM25_SIZE					65536
	#define		MEM25_PAGE_SIZE				128
	#define		MEM25_PAGE_CNT				512
	
	// Additional stuff
	#define		MEM25_AUTO_SLEEP_MODE		1
	#define		MEM25_MULTIPLE_PAGE_WRITE	1
	#define		MEM25_USE_DEMO_COMMANDS		1
	
	#define		MEM25_CONFIG_DONE
	
#endif

// ========================================
// Error handling
// ========================================

#ifndef MEM25_CONFIG_DONE
	#error "Missing config"
#endif

#endif /* SPI_MEM_CONFIG_H_ */