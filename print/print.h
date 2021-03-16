/*
UWAGI I POMYS£Y

CHANGELOG
0.00	+	Pocz¹tki
		
HARDWARE
		-	UART
*/

#ifndef PRINT_H_
#define PRINT_H_

#if C_PRINT

// Include
#if C_UART_SINGLE
	#include	"../uart/uart_single.h"
#elif C_UART_MULTI
	#include	"../uart/uart_multi.h"
#else
	#error		"This module requires UART component"
#endif


// Funkcje
void Print_Init(void);
void Print(const char Char);
void Print(const char * Text);
void Print_NL(void);
void Print_Dec(uint32_t Value);
void Print_DecSigned(int8_t Value);
void Print_DecSigned(int32_t Value);
void Print_Bin(uint8_t Data, const uint8_t Separator);
void Print_Hex(const uint8_t Data, const uint8_t Separator = 0);
void Print_Hex(const uint16_t Data, const uint8_t Separator = 0);
void Print_Hex(const uint32_t Data, const uint8_t Separator = 0);
void Print_HexString(const uint8_t * String, const uint16_t Length, const uint8_t Separator, const uint8_t BytesInRow);
void Print_Dump(const uint8_t * String, uint16_t Length, uint16_t AddressStartValue);
#endif /* C_PRINT */
#endif /* PRINT_H_ */

