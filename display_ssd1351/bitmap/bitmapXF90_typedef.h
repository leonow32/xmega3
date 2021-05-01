#ifndef BITMAPXF90_TYPEDEF_H_
#define BITMAPXF90_TYPEDEF_H_

// Typ abstrakcyjny do okre�lania g��bii kolor�w
enum BitmapXF90_ColorDepth_t {
	BitmapXF90_Mono,								// 1 bajt = 8 pikseli
	BitmapXF90_RGB332,								// 1 piksel = 1 bajt,  0bRRRGGGBB
	BitmapXF90_RGB565								// 1 piksel = 2 bajty, 0bRRRRRGGGGGGBBBBB
};

// Struktura definicji bitmapy
typedef struct _BitmapXF90_t {
	const uint8_t Height;							// Wysoko�� w pikselach
	const uint8_t Width;							// Je�eli czcionka ma sta�� szeroko��, je�li nie to =0
	const BitmapXF90_ColorDepth_t ColorDepth;		// Tablica szeroko�ci i offset�w, je�li Width jest ustalone to wstawi� NULL
	const uint8_t * Bitmaps;						// Tablica znak�w
} BitmapXF90_t;

#endif /* BITMAPXF90_TYPEDEF_H_ */