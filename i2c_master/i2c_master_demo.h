#ifndef I2C_MASTER_COMMANDS_H_
#define I2C_MASTER_COMMANDS_H_

// ========================================
// Includes
// ========================================

#include		"i2c_master.h"

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

#if I2C_MASTER_USE_DEMO_COMMANDS
	void I2C_CmdScan(uint8_t argc, uint8_t * argv[]);
	void I2C_CmdTransmit(uint8_t argc, uint8_t * argv[]);
#endif

#endif /* I2C_MASTER_COMMANDS_H_ */