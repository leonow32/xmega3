/*
CHANGELOG

1.01	-	Poprawione ustawianie wyj�cia CLKOUT na procesorach innych ni� ATtinyXX16
1.00	-	Ustawianie preskalera zegara systemowego
		
HARDWARE
		-	CLKCTRL
*/

#ifndef CLOCK_H_
#define CLOCK_H_

#include <avr/io.h>
#include "general_config.h"
#include "clock_config.h"

// Funkcje
void Clock_Init(void);

#endif /* CLOCK_H_ */
