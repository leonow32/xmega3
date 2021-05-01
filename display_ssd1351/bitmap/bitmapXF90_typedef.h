#ifndef BITMAPXF90_TYPEDEF_H_
#define BITMAPXF90_TYPEDEF_H_

// Typ abstrakcyjny do okreœlania g³êbii kolorów
enum BitmapXF90_ColorDepth_t {
	BitmapXF90_Mono,								// 1 bajt = 8 pikseli
	BitmapXF90_RGB332,								// 1 piksel = 1 bajt,  0bRRRGGGBB
	BitmapXF90_RGB565								// 1 piksel = 2 bajty, 0bRRRRRGGGGGGBBBBB
};

// Struktura definicji bitmapy
typedef struct _BitmapXF90_t {
	const uint8_t Height;							// Wysokoœæ w pikselach
	const uint8_t Width;							// Je¿eli czcionka ma sta³¹ szerokoœæ, jeœli nie to =0
	const BitmapXF90_ColorDepth_t ColorDepth;		// Tablica szerokoœci i offsetów, jeœli Width jest ustalone to wstawiæ NULL
	const uint8_t * Bitmaps;						// Tablica znaków
} BitmapXF90_t;

#endif /* BITMAPXF90_TYPEDEF_H_ */