// Version 2.0.0

#ifndef SPI_MEM_CONFIG_H_
#define SPI_MEM_CONFIG_H_

// ========================================
// Template
// ========================================

#if TEMPLATE
	
	// Pinout
	#define		MEM23_CHIP_SELECT_INIT		VPORTC.DIR	|=	PIN3_bm
	#define		MEM23_CHIP_SELECT			VPORTC.OUT	&= ~PIN3_bm
	#define		MEM23_CHIP_DESELECT			VPORTC.OUT	|=  PIN3_bm
	
	// Values specific for 23K512 (needed only for page mode operation)
	#define		MEM23_SIZE					65536
	#define		MEM23_PAGE_SIZE				32
	#define		MEM23_PAGE_CNT				2048
	
	// Additional stuff
	#define		MEM23_USE_DEMO_COMMANDS		1
	
	#define		MEM23_CONFIG_DONE
	
#endif

// ========================================
// Dev Board AVR-IoT
// ========================================

#if PRODUCT_AVRIOT
	
	// Pinout
	#define		MEM23_CHIP_SELECT_INIT		VPORTC.DIR	|=	PIN3_bm
	#define		MEM23_CHIP_SELECT			VPORTC.OUT	&= ~PIN3_bm
	#define		MEM23_CHIP_DESELECT			VPORTC.OUT	|=  PIN3_bm
	
	// Values specific for 23K512 (needed only for page mode operation)
	#define		MEM23_SIZE					65536
	#define		MEM23_PAGE_SIZE				32
	#define		MEM23_PAGE_CNT				2048
	
	// Additional stuff
	#define		MEM23_USE_DEMO_COMMANDS		1
	
	#define		MEM23_CONFIG_DONE
	
#endif

// ========================================
// Error handling
// ========================================

#ifndef MEM23_CONFIG_DONE
#error "Missing config"
#endif

#endif /* SPI_MEM_CONFIG_H_ */