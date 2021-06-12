/*
CHANGELOG
1.0.0	*	Added all MCUs based on xmega3 architecture (2019.01.01)
*/

#ifndef GENERAL_CONFIG_H_
#define GENERAL_CONFIG_H_

// ========================================
// Template
// ========================================

#if PRODUCT_TEMPLATE
	#define HW_CPU_ATtinyXX12				0
	#define HW_CPU_ATtinyXX14				0
	#define HW_CPU_ATtinyXX16				0
	#define HW_CPU_ATtinyXX17				0
	#define HW_CPU_ATtinyXX24				0
	#define HW_CPU_ATtinyXX26				0
	#define HW_CPU_ATtinyXX27				0
	#define HW_CPU_ATmegaXX08_28pin			0
	#define HW_CPU_ATmegaXX08_32pin			1
	#define HW_CPU_ATmegaXX09				0
	#define HW_CONFIG_DONE
#endif

// ========================================
// Demo Display SH1106
// ========================================

#if PRODUCT_SH1106
	#define HW_CPU_ATtinyXX17				1
	#define HW_CONFIG_DONE
#endif

// ========================================
// Demo Display SSD1309
// ========================================

#if PRODUCT_SSD1309
	#define HW_CPU_ATmegaXX08_32pin			1
	#define HW_CONFIG_DONE
#endif

// ========================================
// Demo Display SSD1351
// ========================================

#if PRODUCT_SSD1351
	#define HW_CPU_ATmegaXX08_32pin			1
	#define HW_CONFIG_DONE
#endif

// ========================================
// Demo Display SSD1681
// ========================================

#if PRODUCT_SSD1681
	#define HW_CPU_ATmegaXX08_32pin			1
	#define HW_CONFIG_DONE
#endif

// ========================================
// Dev Board AVR-IoT
// ========================================

#if PRODUCT_AVRIOT
	#define HW_CPU_ATmegaXX08_32pin			1
	#define HW_CONFIG_DONE
#endif

// ========================================
// Dev Board Curiosity ATmega4809
// ========================================

#if PRODUCT_CURIOSITY_M4809
	#define HW_CPU_ATmegaXX09				1
	#define HW_CONFIG_DONE
#endif

// ========================================
// Dev Board Curiosity ATtiny3217
// ========================================

#if PRODUCT_CURIOSITY_T1627
	#define HW_CPU_ATtinyXX27				1
	#define HW_CONFIG_DONE
#endif

// ========================================
// Dev Board Curiosity ATtiny3217
// ========================================

#if PRODUCT_CURIOSITY_T3217
	#define HW_CPU_ATtinyXX17				1
	#define HW_CONFIG_DONE
#endif

// ========================================
// Dev Board XNANO
// ========================================

#if BOARD_XNANO
	#define HW_CPU_ATtinyXX16				1
	#define HW_CONFIG_DONE
#endif

// ========================================
// GameBox
// ========================================

#if PRODUCT_GAMEBOX
	#define HW_CPU_ATmegaXX09				1
	#define HW_CONFIG_DONE
#endif

// ========================================
// Error handling
// ========================================

#ifndef HW_CONFIG_DONE
	#error "Missing config"
#endif

#if HW_CPU_ATtinyXX12 + HW_CPU_ATtinyXX14 + HW_CPU_ATtinyXX16 + HW_CPU_ATtinyXX17 + HW_CPU_ATmegaXX09 + HW_CPU_ATmegaXX08_28pin + HW_CPU_ATmegaXX08_32pin > 1
	#error "Selected more than one CPU"
#endif

#endif /* GENERAL_CONFIG_H_ */