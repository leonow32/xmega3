/*

CHANGELOG
3.0.0	*	Translated to English

HARDWARE
		-	TWI Master
		-	Portmux
*/

#ifndef SPI_MASTER_H_
#define SPI_MASTER_H_

// ========================================
// Includes
// ========================================

#include	<avr/io.h>
#include	"../config/config.h"
#include	"spi_master_config.h"

// ========================================
// Functions
// ========================================

void		Spi_Init(void);
uint8_t		Spi_1(const uint8_t Byte);
uint8_t		Spi_2(const uint8_t Byte1, const uint8_t Byte2);
uint8_t		Spi_3(const uint8_t Byte1, const uint8_t Byte2, const uint8_t Byte3);
uint8_t		Spi_4(const uint8_t Byte1, const uint8_t Byte2, const uint8_t Byte3, uint8_t Byte4);
uint8_t		Spi_5(const uint8_t Byte1, const uint8_t Byte2, const uint8_t Byte3, const uint8_t Byte4, const uint8_t Byte5);
void		Spi_Stream(uint8_t * TxBuffer, uint8_t * RxBuffer, const uint16_t Length);
void		Spi_Transmit(const uint8_t * TxBuffer, const uint16_t Length);
void		Spi_Repeat(const uint8_t Byte, uint16_t Times);
void		Spi_Repeat(const uint8_t Byte1, const uint8_t Byte2, uint16_t Times);
#endif /* SPI_MASTER_H_ */
