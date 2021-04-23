#ifndef MEM24_H_
#define MEM24_H_
#if COMPONENT_MEM24

// ========================================
// Includes
// ========================================

#include	<avr/io.h>
#include	<util/delay.h>
#include	"mem24_config.h"

#if COMPONENT_I2C_MASTER
	#include	"../i2c_master/i2c_master.h"
#else
	#error		"This module requires I2C_MASTER component"
#endif

// ========================================
// Result type
// ========================================

enum Mem24_t {
	Mem24_OK = 0,								// Success
	Mem24_Timeout,								// Received NACK after calling device address on I2C bus
	Mem24_TransmissionError,					// Received NACK during write operation
};

// ========================================
// Functions
// ========================================

void		Mem24_Init(void);
Mem24_t		Mem24_Read(uint16_t Address, uint8_t * Buffer, uint16_t Length);
Mem24_t		Mem24_Write(uint16_t Address, uint8_t * Buffer, uint16_t Length);

#endif
#endif /* MEM24_H_ */
