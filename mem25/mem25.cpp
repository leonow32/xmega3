// Version 2.0.0

#if COMPONENT_MEM25

#include "mem25.h"

void SpiMem_Init(void) {
	SPIMEM_CHIP_DESELECT;
	SPIMEM_DIR_SET;
}

void SpiMem_Sleep(void) {
	// przed wejœciem w staaktualnie nie odbywa siê zapis do pamiêci przy pomocy SpiMem_IsBusy() lub SpiMem_WaitForReady()
	SPIMEM_CHIP_SELECT;
	Spi_1(SPIMEM_SLEEP);
	SPIMEM_CHIP_DESELECT;
}

void SpiMem_Wake(void) {
	// po wybudzeniu czekaæ na gotowoœæ przy pomocy SpiMem_WaitForReady()
	SPIMEM_CHIP_SELECT;
	Spi_1(SPIMEM_WAKE);
	SPIMEM_CHIP_DESELECT;
}

void SpiMem_WriteEnable(void) {
	SPIMEM_CHIP_SELECT;
	Spi_1(SPIMEM_WRITE_ENABLE);
	SPIMEM_CHIP_DESELECT;
}

void SpiMem_WriteDisble(void) {
	SPIMEM_CHIP_SELECT;
	Spi_1(SPIMEM_WRITE_DISABLE);
	SPIMEM_CHIP_DESELECT;
}

void SpiMem_ChipErase(void) {
	// po skasowaniu scalaka czekaæ na gotowoœæ przy pomocy SpiMem_WaitForReady()
	SPIMEM_CHIP_SELECT;
	Spi_1(SPIMEM_WRITE_ENABLE);
	SPIMEM_CHIP_DESELECT;

	SPIMEM_CHIP_SELECT;
	Spi_1(SPIMEM_ERASE_CHIP);
	SPIMEM_CHIP_DESELECT;
}

uint8_t SpiMem_StatusRead(void) {
	uint8_t Status;
	SPIMEM_CHIP_SELECT;
	Status = Spi_2(SPIMEM_STATUS_READ, 0);
	SPIMEM_CHIP_DESELECT;
	return Status;
}

void SpiMem_StatusWrite(uint8_t Status) {
	SPIMEM_CHIP_SELECT;
	Status = Spi_2(SPIMEM_STATUS_WRITE, Status);
	SPIMEM_CHIP_DESELECT;
}

bool SpiMem_IsBusy(void) {
	uint8_t Status;
	SPIMEM_CHIP_SELECT;
	Status = Spi_2(SPIMEM_STATUS_READ, 0);
	SPIMEM_CHIP_DESELECT;
	return Status & 0b00000001;
}

void SpiFlash_WaitForReady(void) {
	SPIMEM_CHIP_SELECT;
	while(Spi_2(SPIMEM_STATUS_READ, 0) & 0b00000001);
	SPIMEM_CHIP_DESELECT;
}

uint8_t SpiMem_Read(uint16_t Address) {
	uint8_t Data;
	SPIMEM_CHIP_SELECT;
	Data = Spi_4(SPIMEM_READ, (Address & 0xFF00) >> 8, Address & 0x00FF, 0);
	SPIMEM_CHIP_DESELECT;
	return Data;
}

void SpiMem_Read(uint16_t Address, uint8_t * Buffer, uint16_t Length) {
	SPIMEM_CHIP_SELECT;
	Spi_3(SPIMEM_READ, (Address & 0xFF00) >> 8, Address & 0x00FF);
	Spi_Stream(Buffer, Buffer, Length);
	SPIMEM_CHIP_DESELECT;
}

void SpiMem_Write(uint16_t Address, uint8_t Byte) {
	// sprawdzanie czy pamiêæ jest gotowa do zapisu
	SpiFlash_WaitForReady();

	// Write enable latch
	SpiMem_WriteEnable();

	// zapis w³aœciwy
	SPIMEM_CHIP_SELECT;
	Spi_4(SPIMEM_WRITE, (Address & 0xFF00) >> 8, Address & 0x00FF, Byte);
	SPIMEM_CHIP_DESELECT;
}

void SpiMem_Write(uint16_t Address, const uint8_t * Buffer, uint16_t Length) {
	// Nie uwzglêdnia stronicowania pamiêci!!!

	// Sprawdzanie czy pamiêæ jest gotowa do zapisu
	SpiFlash_WaitForReady();

	// Write enable latch
	SpiMem_WriteEnable();

	// Zapis w³aœciwy
	SPIMEM_CHIP_SELECT;
	Spi_3(SPIMEM_WRITE, (Address & 0xFF00) >> 8, Address & 0x00FF);
	//Spi_Stream(Buffer, Buffer, Length);
	Spi_Transmit(Buffer, Length);
	SPIMEM_CHIP_DESELECT;
}

void SpiMem_WriteMultiPage(uint16_t Address, const uint8_t * Buffer, uint16_t Length) {
	uint16_t AddressEnd = Address + Length - 1;
	uint16_t PageStart = Address / SPIMEM_PAGE_SIZE;
	uint16_t PageEnd = AddressEnd / SPIMEM_PAGE_SIZE;
	uint16_t ActualPage = PageStart;
	uint16_t ActualPageEnd;
	uint16_t ActualStart = Address;
	uint16_t ActualEnd;
	uint16_t ActualLength;

	// pêtla obejmuj¹ca wszystkie wyliczone strony
	while(ActualPage <= PageEnd) {

		// wyznaczenie adresu koñca, czy do koñca strony czy do koñca transakcji, jeœli koniec transakcji jest mniejszy ni¿ koniec strony
		ActualPageEnd = SPIMEM_PAGE_SIZE * (ActualPage+1) - 1;
		if(AddressEnd <= ActualPageEnd) {
			// koniec transakcji jest na tej stronie
			ActualEnd = AddressEnd;
			} 
			else {
			// Koniec transakcji jest póŸniej
			ActualEnd = ActualPageEnd;
		}
		ActualLength = ActualEnd - ActualStart + 1;

		// zapis do pamiêci
		SpiMem_Write(ActualStart, Buffer, ActualLength);
		Buffer = Buffer + ActualLength;

		// zwiêkszenie wskaŸników
		ActualPage++;
		ActualStart = ActualEnd + 1;
	}
}

#if SPIMEM_INCLUDE_DUMP
void SpiMem_Dump(uint16_t Start, uint16_t Length) {
	
	uint8_t Buffer[16];

	uint16_t i = Start & 0xFFF0;

	// rozpoczêcie transmisji
	SPIMEM_CHIP_SELECT;
	Spi_3(SPIMEM_READ, (i & 0xFF00) >> 8, i & 0x00FF);

	// wyœwietlenie nag³ówka
	Uart_Write("\n\rADDR:  0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F");

	do {
		// odczytanie 16 bajtów
		Spi_Stream(Buffer, Buffer, 16);

		// zejœcie do nowej linii
		Uart_WriteNL();

		// wyœwietlenie adresu
		Uart_WriteHex(i, ':');
		Uart_Write(' ');

		// wyœwietlenie HEX
		for(uint8_t h=0; h<=15; h++) {
			Uart_WriteHex(*(Buffer+h), ' ');
		}
		
		// wyœwietlenie ASCII
		for(uint8_t h=0; h<=15; h++) {
			if((*(Buffer+h) >= ' ') && (*(Buffer+h) < 127)) {			// omijanie znaków specjanych <32 i <127
				Uart_Write(*(Buffer+h));
			} 
			else {
				Uart_Write(' ');
			}
		}
		
		// inkrementacja adresu
		i += 16;
	} while(i <= Start+Length-1 && i != 0);		// i != 0 zabezpiecza przed przekrêceniem sie licznika po 0xFFFF

	SPIMEM_CHIP_DESELECT;
}

#endif

#endif 