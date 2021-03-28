/*
CHANGELOG
2.0.0		Translated to English
1.0.1	-	Corrected setting of CLKOUT on MCUs other than ATtinyXX16
1.0.0	-	Prescaler settings
		
HARDWARE
		-	CLKCTRL
*/

#ifndef CLOCK_H_
#define CLOCK_H_

#include <avr/io.h>
#include "../config/config.h"
#include "clock_config.h"

// Functions
void Clock_Init(void);

#endif /* CLOCK_H_ */
