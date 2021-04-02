/*
IDEAS AND TO DO LIST
		-	add interrupts
		-	add sleep modes

CHANGELOG
3.0.0	*	Translated to English

HARDWARE
		-	TWI Master
		-	Portmux
*/


#ifndef I2C_MASTER_H_
#define I2C_MASTER_H_

#include	<avr/io.h>
#include	"../config/config.h"
#include	"i2c_master_config.h"

// Functions
void		I2C_Init(void);
uint8_t		I2C_Start(uint8_t Address);
uint8_t		I2C_Write(uint8_t Data);
uint8_t		I2C_Read(void);
void		I2C_Stop(void);


#endif /* I2C_MASTER_H_ */
