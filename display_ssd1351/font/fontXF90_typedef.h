#ifndef FONTXF90_TYPEDEF_H_
#define FONTXF90_TYPEDEF_H_

// Struktura d�ugo�ci i offset�w znak�w w tabeli bitmap
typedef struct _fontXF90_char_info {
	uint8_t		Width;						// Szeroko�� znaku w pikselach
	uint16_t	Offset;						// Adres w tablicy bitmap
} fontXF90_info_t;

// Struktura definicji czcionki
typedef struct _fontXF90_definition {
	uint8_t Height;							// Wysoko�� w pikselach
	uint8_t Width;							// Je�eli czcionka ma sta�� szeroko��, je�li nie to =0
	uint8_t Spacing;						// Odst�p mi�dzy znakami
	uint8_t FirstChar;						// Pierwszy znak, jaki znajduje si� w tablicy Bitmaps
	uint8_t LastChar;						// Ostatni znak, jaki znajduje si� w tablicy Bitmaps
	const fontXF90_info_t * Descriptors;		// Tablica szeroko�ci i offset�w, je�li Width jest ustalone to wstawi� NULL
	const uint8_t * Bitmaps;				// Tablica znak�w
} fontXF90_def_t;



#endif /* FONTXF90_TYPEDEF_H_ */