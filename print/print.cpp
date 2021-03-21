// Wersja 0.01

#if C_PRINT

#include "print.h"

// WskaŸnik do funkji, która ma wyœwietlaæ znaki
void (*Print_Pointer)(const uint8_t Data) = PRINT_DEFAULT_STREAM;


// Ustawienie wskaŸnika
// Je¿eli zostanie podany NULL wówczas ustawiany jest wskaŸnik do domyœlnego strumienia wyjœciowego, zdefiniowany w konfiguracji
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


// Zapis dojedynczego znaku
void Print(const uint8_t Data) {
	
	#if PRINT_USE_STREAM_SINGLE
		PRINT_DEFAULT_STREAM(Data);
	#endif
	
	#if PRINT_USE_STREAM_MULTI
		Print_Pointer(Data);
	#endif
}


// Zapis ci¹gu znaków
void Print(const char * Text) {
	while(*Text) Print(*Text++);
}


// Nowa linia
void Print_NL(void) {
	Print("\r\n");
}


// Liczba dziesiêtna bez znaku
void Print_Dec(uint32_t Value) {
	if(Value==0) {
		Print('0');
		return;
	}
	
	uint8_t cyfra[10];
	memset(cyfra, 0, sizeof(cyfra));
	int8_t i=0;
	
	while(Value) {
		cyfra[i] = (uint8_t)(Value%10);
		Value = Value / 10;
		++i;
	}
	
	while(i--) {
		Print(cyfra[i]+48);
	}
}


// Liczba dziesiêtna ze znakiem
void Print_DecSigned(int8_t Value) {
	if(Value < 0) {
		Print('-');
		Value = -Value;
	}
	Print_Dec(uint8_t(Value));
}


// Liczba dziesiêtna ze znakiem
void Print_DecSigned(int32_t Value) {
	if(Value < 0) {
		Print('-');
		Value = -Value;
	}
	Print_Dec(uint32_t(Value));
}


// Zapis liczny binarnej
void Print_Bin(uint8_t Data, const uint8_t Separator) {
	for(uint8_t BitMask = 0b10000000; BitMask; BitMask = BitMask >> 1) {
		Print(Data & BitMask ? '1' : '0');
	}
	if(Separator) Print(Separator);
}


// Zapis po³ówki bajtu jako ASCII HEX
void Print_Nibble(uint8_t Nibble) {
	if(Nibble <= 9) Print(Nibble + '0');
	else Print(Nibble + 55);
}

// Liczba HEX 8-bitowa
void Print_Hex(const uint8_t Data, const uint8_t Separator) {
	Print_Nibble((Data & 0xF0) >> 4);
	Print_Nibble((Data & 0x0F) >> 0);
	if(Separator) Print(Separator); 
}


// Liczba HEX 16-bitowa
void Print_Hex(const uint16_t Data, const uint8_t Separator) {
	Print_Hex(uint8_t((Data & 0xFF00) >> 8), 0);
	Print_Hex(uint8_t((Data & 0x00FF)     ), Separator);
}


// Liczba HEX 32-bitowa
void Print_Hex(const uint32_t Data, const uint8_t Separator) {
	Print_Hex(uint8_t((Data & 0xFF000000) >> 24), 0);
	Print_Hex(uint8_t((Data & 0x00FF0000) >> 16), 0);
	Print_Hex(uint8_t((Data & 0x0000FF00) >> 8 ), 0);
	Print_Hex(uint8_t((Data & 0x000000FF)      ), Separator);
}


// Ci¹g znaków prezentowany jako HEX
void Print_HexString(const uint8_t * String, const uint16_t Length, const uint8_t Separator, const uint8_t BytesInRow) {
	
	for(uint16_t i=0; i<Length; i++) {
		
		// Przejœcie do nowej linii (nie dotyczny pierwszego wyœwietlanego znaku)
		if((i%BytesInRow == 0) && i != 0) {
			Print_NL();
		}
		
		// Wyœwietlenie znaku
		Print_Hex(*(String+i), Separator);
	}
}


// Ci¹g znaków prezentowany jako HEX, wraz z nag³ówkiem i adresowaniem
void Print_Dump(const uint8_t * String, uint16_t Length, uint16_t AddressStartValue) {
	
	uint8_t * wskaznik		= (uint8_t *)String;
	uint16_t LengthForHex	= Length;
	uint16_t LengthForAscii	= Length;
	uint16_t i = 0;
	
	Print("       0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F");
	
	// Wyœwietlanie w pêtli po 16 znaków na ka¿d¹ liniê
	do {
		
		// Zejœcie do nowej linii
		Print_NL();
		
		// Wyœwietlenie adresu
		Print(' ');
		
		// Wyœwietlenie HEX
		for(uint8_t h=0; h<=15; h++) {
			
			// Sprawdzanie czy nie zosta³y wyœwietlone ju¿ wszystkie znaki
			if(LengthForHex) {
				LengthForHex--;
				Print_Hex(*(wskaznik+h), ' ');
			}
			else {
				// Wyœwietlanie trzech spacji, aby potem mo¿na by³o wyœwietliæ ASCII we w³aœciwym miejscu
				Print("   ");
			}
		}
		
		// Wyœwietlenie ASCII
		for(uint8_t h=0; h<=15; h++) {
			if((*(wskaznik+h) >= ' ') && (*(wskaznik+h) < 127)) {				// Omijanie znaków specjanych <32 i <127
				Print(*(wskaznik+h));
			} 
			else {
				Print(' ');
			}
			
			if(--LengthForAscii == 0) {
				break;
			}
		}
		
		// Inkrementacja wskaŸników
		wskaznik += 16;
		i += 16;
		
		// Reset watchdoga
		asm volatile("wdr");
	} while(i <= Length-1 && i != 0);											// i != 0 zabezpiecza przed przekrêceniem sie licznika po 0xFFFF
}


#endif