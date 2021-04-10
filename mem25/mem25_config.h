// Version 2.0.0

#ifndef SPI_MEM_CONFIG_H_
#define SPI_MEM_CONFIG_H_

// ========================================
// Template
// ========================================

#if PRODUCT_AVRIOT
	// Pinout
	#define		SPIMEM_DIR_SET					VPORTD.DIR	|=	PIN0_bm
	#define		SPIMEM_CHIP_SELECT				VPORTD.OUT	&= ~PIN0_bm
	#define		SPIMEM_CHIP_DESELECT			VPORTD.OUT	|=  PIN0_bm
	
	// Wielkosci specyficzne dla 25LC512
	#define		SPIMEM_SIZE						65535
	#define		SPIMEM_PAGE_SIZE				128
	#define		SPIMEM_PAGE_CNT					512
	
	// Konfiguracja dodatkowych funkcji
	#define		SPIMEM_INCLUDE_DUMP				1
	
#endif


#endif /* SPI_MEM_CONFIG_H_ */