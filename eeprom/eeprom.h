/*
CHANGELOG
2.0.0		Converted to new repo
1.09	+	Dodanie zapisywania b³êdów w logu
1.08	*	Optymalizacja EEPROM_Fill() i EEPROM_Erase(). U¿ycie kontrolera NVM do kasowania ca³ej pamiêci zamiast pojedynczych bajtów
1.07	+	Funckja operuj¹ce na pojedynczych bitach
		+	uint8_t	EEPROM_ReadBit(uint8_t Address, uint8_t BitMask);
		+	EEres_t EEPROM_BitSet(uint8_t Address, uint8_t BitMask);
		+	EEres_t EEPROM_BitClr(uint8_t Address, uint8_t BitMask);
1.06	*	Oczyszczenie kodu i optymalizacja
1.05	+	Zmiana definicji EEPROM_VALID i EEPROM_INVALID na enum
1.04	+	Dodanie pliku eeprom_map.h
1.03	*	Zakoñczenie prac nad obs³ug¹ potrójnej redundancji
1.02	+	Dodanie pliku konfiguracyjnego eeprom_config.h
		+	Dodanie obs³ugi potrójnej redundancji
1.01	*	Uporz¹dkowanie kodu
1.00	+	Pierwsza wersja

UWAGI
		-	Obs³uguje pamiêci EEPROM o rozmiarze max 256B ze wzglêdu na adresowanie 8-bitowe
		-	Biblioteka wykorzystuje bajtowy dostêp do EEPROM, nie wykorzystuje stronicowania pamiêci
		
DO ZROBIENIA
		-	Automatyczne raportowanie b³êdów potrójnej redundancji do logu
*/


#ifndef EEPROM_H_
#define EEPROM_H_

#include	<avr/eeprom.h>
#include	<avr/interrupt.h>
#include	"eeprom_config.h"


void		EEPROM_Init(void);
uint8_t		EEPROM_Read(uint8_t Address);
void		EEPROM_Read(uint8_t Address, uint8_t * Array, size_t ArrayLength);
void		EEPROM_Write(uint8_t Address, uint8_t Data);
void		EEPROM_Write(uint8_t Address, uint8_t * Array, size_t ArrayLength);
void		EEPROM_Erase(void);
void		EEPROM_Fill(uint8_t Pattern);


#endif /* EEPROM_H_ */
