/*
CHANGELOG
1.0.0	*	Added all MCUs based on xmega3 architecture (2019.01.01)
*/

#ifndef GENERAL_CONFIG_H_
#define GENERAL_CONFIG_H_

// ========================================
// Template
// ========================================

#if P_TEMPLATE
	#define HW_CPU_ATtinyXX12					0
	#define HW_CPU_ATtinyXX14					0
	#define HW_CPU_ATtinyXX16					0
	#define HW_CPU_ATtinyXX17					0
	#define HW_CPU_ATmegaXX08_28pin				0
	#define HW_CPU_ATmegaXX08_32pin				1
	#define HW_CPU_ATmegaXX09					0
	#define HW_CONFIG_DONE
#endif

// ========================================
// Dev Board AVR-IoT
// ========================================

#if P_AVRIOT
	#define HW_CPU_ATtinyXX12					0
	#define HW_CPU_ATtinyXX14					0
	#define HW_CPU_ATtinyXX16					0
	#define HW_CPU_ATtinyXX17					0
	#define HW_CPU_ATmegaXX08_28pin				0
	#define HW_CPU_ATmegaXX08_32pin				1
	#define HW_CPU_ATmegaXX09					0
	#define HW_CONFIG_DONE
#endif

// ========================================
// Dev Board Curiosity ATmega4809
// ========================================

#if P_CURIO4809
	#define HW_CPU_ATtinyXX12					0
	#define HW_CPU_ATtinyXX14					0
	#define HW_CPU_ATtinyXX16					0
	#define HW_CPU_ATtinyXX17					0
	#define HW_CPU_ATmegaXX08_28pin				0
	#define HW_CPU_ATmegaXX08_32pin				0
	#define HW_CPU_ATmegaXX09					1
	#define HW_CONFIG_DONE
#endif

// ========================================
// Dev Board XNANO
// ========================================

#if B_XNANO
	#define HW_CPU_ATtinyXX12					0
	#define HW_CPU_ATtinyXX14					0
	#define HW_CPU_ATtinyXX16					1
	#define HW_CPU_ATtinyXX17					0
	#define HW_CPU_ATmegaXX08_28pin				0
	#define HW_CPU_ATmegaXX08_32pin				0
	#define HW_CPU_ATmegaXX09					0
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