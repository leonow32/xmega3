#ifndef MCP9808_CONFIG_H_
#define MCP9808_CONFIG_H_

#include "../config/config.h"

// ========================================
// Template
// ========================================

#if TEMPATE

#endif

// ========================================
// Dev Board AVR-IoT
// ========================================

#if P_AVRIOT
	#define		MCP9808_ADDRESS_READ			uint8_t(0x31)
	#define		MCP9808_ADDRESS_WRITE			uint8_t(0x30)
	#define		MCP9808_USE_COMMANDS			1
#endif



#endif /* MCP9808_CONFIG_H_ */