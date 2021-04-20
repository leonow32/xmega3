#ifndef MEM24_H_
#define MEM24_H_
#if COMPONENT_MEM24

// ========================================
// Includes
// ========================================

#include	<avr/io.h>
#include	"mem24_config.h"

#if COMPONENT_I2C_MASTER
	#include	"../i2c_master/i2c_master.h"
#else
	#error		"This module requires I2C_MASTER component"
#endif

// ========================================
// Functions
// ========================================

void		Mem24_Init(void);
void		Mem24_Read(uint16_t Address, uint8_t * Buffer, uint16_t Length);
void		Mem24_Write(uint16_t Address, uint8_t * Buffer, uint16_t Length);

#endif
#endif /* MEM24_H_ */
