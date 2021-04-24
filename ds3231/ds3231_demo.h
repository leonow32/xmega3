#ifndef DS3231_DEMO_H_
#define DS3231_DEMO_H_

// ========================================
// Includes
// ========================================

#include		"ds3231.h"

#if COMPONENT_SPI_MASTER
	#include		"../i2c_master/i2c_master.h"
#else
	#error		"This module requires I2C_MASTER component"
#endif

#if COMPONENT_CONSOLE
	#include	"../console/console.h"
#else
	#error		"This module requires CONSOLE component"
#endif

#if COMPONENT_PRINT
	#include	"../print/print.h"
#else
	#error		"This module requires PRINT component"
#endif

// ========================================
// Console Commands
// ========================================

void DS3231_Debug(DS3231_t Result);


#endif /* SPI_MEM_DEMO_H_ */
