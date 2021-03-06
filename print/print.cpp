// Version 1.0.0

#if COMPONENT_PRINT

#include "print.h"

// Pointer to a function which has to print the characters
void (*Print_Pointer)(const uint8_t Data) = PRINT_DEFAULT_STREAM;


// Pointer setting
// If NULL is passed as an argument then default the defeult pointer is set (see configuration)
#if PRINT_USE_STREAM_SINGLE
	void Print_SetStream(void (*NewPrintPointer)(const uint8_t Data)) {
		return;
	}
#elif PRINT_USE_STREAM_MULTI
void Print_SetStream(void (*NewPrintPointer)(const uint8_t Data)) {
		if(NewPrintPointer == NULL) {
			Print_Pointer = PRINT_DEFAULT_STREAM;
		}
		else {
			Print_Pointer = NewPrintPointer;
		}
	}
#endif


// Print single character
void Print(const uint8_t Data) {
	
	#if PRINT_USE_STREAM_SINGLE
		PRINT_DEFAULT_STREAM(Data);
	#endif
	
	#if PRINT_USE_STREAM_MULTI
		Print_Pointer(Data);
	#endif
}


// Print string
void Print(const char * Text) {
	while(*Text) Print(*Text++);
}


// NEw line
void Print_NL(void) {
	Print("\r\n");
}


// Unsigned decimal number
void Print_Dec(uint32_t Value) {
	if(Value==0) {
		Print('0');
		return;
	}
	
	uint8_t Digit[10];
	memset(Digit, 0, sizeof(Digit));
	int8_t i=0;
	
	while(Value) {
		Digit[i] = (uint8_t)(Value%10);
		Value = Value / 10;
		++i;
	}
	
	while(i--) {
		Print(Digit[i]+48);
	}
}


// Signed decimal number
void Print_DecSigned(int32_t Value) {
	if(Value < 0) {
		Print('-');
		Value = -Value;
	}
	Print_Dec(uint32_t(Value));
}


// Binary number
void Print_Bin(uint8_t Data, const uint8_t Separator) {
	for(uint8_t BitMask = 0b10000000; BitMask; BitMask = BitMask >> 1) {
		Print(Data & BitMask ? '1' : '0');
	}
	if(Separator) Print(Separator);
}


// Print half-byte as ASCII HEX
void Print_Nibble(uint8_t Nibble) {
	if(Nibble <= 9) Print(Nibble + '0');
	else Print(Nibble + 55);
}

// 8-bit HEX number
void Print_Hex(const uint8_t Data, const uint8_t Separator) {
	Print_Nibble((Data & 0xF0) >> 4);
	Print_Nibble((Data & 0x0F) >> 0);
	if(Separator) Print(Separator); 
}


// 16-bit HEX number
void Print_Hex(const uint16_t Data, const uint8_t Separator) {
	Print_Hex(uint8_t((Data & 0xFF00) >> 8), 0);
	Print_Hex(uint8_t((Data & 0x00FF)     ), Separator);
}


// 32-bit HEX number
void Print_Hex(const uint32_t Data, const uint8_t Separator) {
	Print_Hex(uint8_t((Data & 0xFF000000) >> 24), 0);
	Print_Hex(uint8_t((Data & 0x00FF0000) >> 16), 0);
	Print_Hex(uint8_t((Data & 0x0000FF00) >> 8 ), 0);
	Print_Hex(uint8_t((Data & 0x000000FF)      ), Separator);
}


// String printed as HEX numbers
void Print_HexString(const uint8_t * String, const uint16_t Length, const uint8_t Separator, const uint8_t BytesInRow) {
	
	for(uint16_t i=0; i<Length; i++) {
		
		// New line after printing defined number of bytes
		if((i%BytesInRow == 0) && i != 0) {
			Print_NL();
		}
		
		// Print byte as HEX
		Print_Hex(*(String+i), Separator);
	}
}


// Na potrzeby Os_TimePrint(), ?eby zaoszcz?dzi? troch? miejsca programu
static void Print_Dec2digits(uint8_t Dec) {
	Print(Dec / 10 + '0');
	Print(Dec % 10 + '0');
}


// Print time
void Print_Time(time_t * Time) {
	tm TimeStruct;
	if(*Time == 0xFFFFFFFF) *Time = 0;
	gmtime_r(Time, &TimeStruct);
	
	Print_Dec2digits(20);
	Print_Dec2digits(TimeStruct.tm_year - 100);
	Print('-');
	Print_Dec2digits(TimeStruct.tm_mon + 1);
	Print('-');
	Print_Dec2digits(TimeStruct.tm_mday);
	Print(' ');
	Print_Dec2digits(TimeStruct.tm_hour);
	Print(':');
	Print_Dec2digits(TimeStruct.tm_min);
	Print(':');
	Print_Dec2digits(TimeStruct.tm_sec);
}


// Byte array printed as HEX with the header and address
void Print_Dump(uint8_t * Pointer, uint32_t Length) {
	
	// Print header
	Print_Format(ForegroundWhiteBright);
	Print("\t");
	for(uint8_t i='0'; i<='F'; i++) {
		Print(' ');
		Print(i);
		Print(' ');
		if(i == '9') {
			i = 'A' - 1;
		}
	}
	Print_Format(FormatReset);
	
	// Loop for 16 bytes
	uint16_t Loops = Length / 16;
	if(Length & 0x0F) {
		Loops++;
	}
	
	while(Loops--) {
		
		// New line
		Print_NL();
		
		// Print address
		Print_Format(ForegroundWhiteBright);
		Print_Hex(uint16_t(Pointer));
		Print_Format(FormatReset);
		
		// Print as HEX
		Print('\t');
		Print_HexString(Pointer, 16, ' ');
		
		// Print as ASCII
		Print('\t');
		for(uint8_t h=0; h<=15; h++) {
			uint8_t Character = *Pointer++;
			if((Character >= ' ') && (Character < 127)) {		// Ignore special characters with codes <32 and >127
				Print(Character);
			} 
			else {
				Print(' ');
			}
		}
		
		// Watchdog reset
		asm volatile("wdr");
	}
}


// Change text format, bolt, italic, underline, color of foreground and background (https://en.wikipedia.org/wiki/ANSI_escape_code)
#if PRINT_USE_COLORS
void Print_Format(PrintFormat_t Code) {
	Print(ESC);
	Print('[');
	Print_Dec(uint8_t(Code));
	Print('m');
}
#endif


// ========================================
// Frequently used responses
// ========================================


void Print_ResponseOK(void) {
	Print_Format(ForegroundGreen);
	Print("OK");
}


void Print_ResponseError(void) {
	Print_Format(ForegroundRed);
	Print("Error");
}


void Print_ResponseNotFound(void) {
	Print_Format(ForegroundRed);
	Print("Not found");
}


void Print_ResponseUnknown(void) {
	Print_Format(ForegroundRed);
	Print("Unknown");
}


void Print_ResponseTimeout(void) {
	Print_Format(ForegroundRed);
	Print("Timeout");
}


void Print_ResponseTransmissionError(void) {
	Print_Format(ForegroundRed);
	Print("Transmission error");
}


#endif