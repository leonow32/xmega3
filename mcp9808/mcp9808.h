#ifndef MCP9808_H_
#define MCP9808_H_
#if C_MCP9808

// Includes
#include		<avr/io.h>
#include		"mcp9808_config.h"

#if C_I2C_MASTER
	#include	"../i2c_master/i2c_master.h"
#else
	#error		"This module requires I2C_MASTER component"
#endif

//  Result type
enum MCP9808_t {
	MCP9808_OK = 0,								// Success
	MCP9808_StartNACK,							// Received NACK after calling device address on I2C bus
	MCP9808_TransmissionError,					// Received NACK during write operation
};

// Registers
#define MCP9808_REG_CONFIG						uint8_t(0x01)
#define MCP9808_REG_TUPPER						uint8_t(0x02)
#define MCP9808_REG_TLOWER						uint8_t(0x03)
#define MCP9808_REG_TCRITICAL					uint8_t(0x04)
#define MCP9808_REG_TAMBIENT					uint8_t(0x05)
#define MCP9808_REG_MANUFACTURER_ID				uint8_t(0x06)
#define MCP9808_REG_DEVICE_ID					uint8_t(0x07)
#define MCP9808_REG_RESOLUTION					uint8_t(0x08)

// Functions
void MCP9808_Init(void);
MCP9808_t MCP9808_Read(uint8_t Register, uint16_t * Data);
MCP9808_t MCP9808_Write(uint8_t Register, uint16_t Data);
MCP9808_t MCP9808_TemperatureGet(int32_t * Temperature);
#endif
#endif /* MCP9808_H_ */
