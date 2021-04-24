#ifndef DS3231_H_
#define DS3231_H_
#if COMPONENT_MEM24

// ========================================
// Includes
// ========================================

#include	<avr/io.h>
#include	<util/delay.h>
#include	"ds3231_config.h"

#if COMPONENT_I2C_MASTER
	#include	"../i2c_master/i2c_master.h"
#else
	#error		"This module requires I2C_MASTER component"
#endif

// ========================================
// Result type
// ========================================

enum DS3231_t {
	DS3231_OK = 0,	// Success
	DS3231_Error,	// Received NACK after calling device address on I2C bus, timeout or transmisstion broken
};

// ========================================
// Functions
// ========================================

void		DS3231_Init(void);


#endif
#endif /* MEM24_H_ */
