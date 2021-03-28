#ifndef MCP9808_H_
#define MCP9808_H_
#if C_MCP9808

// Includes
#include	<avr/io.h>

#if C_I2C_MASTER
	#include	"../i2c_master/i2c_master.h"
#else
	#error		"This module requires I2C_MASTER component"
#endif



#endif
#endif /* MCP9808_H_ */