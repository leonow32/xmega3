#ifndef I2C_MASTER_COMMANDS_H_
#define I2C_MASTER_COMMANDS_H_

// ========================================
// Includes
// ========================================

#include		"i2c_master.h"

#if C_CONSOLE
	#include	"../console/console.h"
#else
	#error		"This module requires CONSOLE component"
#endif

#if C_PRINT
	#include	"../print/print.h"
#else
	#error		"This module requires PRINT component"
#endif

// ========================================
// Console Commands
// ========================================

void I2C_CmdScan(uint8_t argc, uint8_t * argv[]);
void I2C_CmdStart(uint8_t argc, uint8_t * argv[]);
void I2C_CmdRead(uint8_t argc, uint8_t * argv[]);
void I2C_CmdWrite(uint8_t argc, uint8_t * argv[]);
void I2C_CmdStop(uint8_t argc, uint8_t * argv[]);

#endif /* I2C_MASTER_COMMANDS_H_ */