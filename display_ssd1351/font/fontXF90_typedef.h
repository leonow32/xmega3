#ifndef FONTXF90_TYPEDEF_H_
#define FONTXF90_TYPEDEF_H_

// Struktura d³ugoœci i offsetów znaków w tabeli bitmap
typedef struct _fontXF90_char_info {
	uint8_t		Width;						// Szerokoœæ znaku w pikselach
	uint16_t	Offset;						// Adres w tablicy bitmap
} fontXF90_info_t;

// Struktura definicji czcionki
typedef struct _fontXF90_definition {
	uint8_t Height;							// Wysokoœæ w pikselach
	uint8_t Width;							// Je¿eli czcionka ma sta³¹ szerokoœæ, jeœli nie to =0
	uint8_t Spacing;						// Odstêp miêdzy znakami
	uint8_t FirstChar;						// Pierwszy znak, jaki znajduje siê w tablicy Bitmaps
	uint8_t LastChar;						// Ostatni znak, jaki znajduje siê w tablicy Bitmaps
	const fontXF90_info_t * Descriptors;		// Tablica szerokoœci i offsetów, jeœli Width jest ustalone to wstawiæ NULL
	const uint8_t * Bitmaps;				// Tablica znaków
} fontXF90_def_t;



#endif /* FONTXF90_TYPEDEF_H_ */