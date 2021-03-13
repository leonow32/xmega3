#include <avr/io.h>
#include <util/delay.h>


int main(void) {
	
	// Init Pins
	PORTD.DIRSET = PIN0_bm;
	
	while(1) {
		PORTD.OUTSET = PIN0_bm;
		_delay_ms(1000);
		PORTD.OUTCLR = PIN0_bm;
		_delay_ms(500);
	}
}

