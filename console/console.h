/*
UWAGI I POMYS�Y
		-	Doda� mo�liwo�� by mo�na by�o stosowa� kilka bufor�w interpretera o r�nej d�ugo�ci, p�ki co jest regulowany definicj� CMD_LINE_BUFFER_LENGTH
		!	Przycisk ESCAPE nie kasuje bufora polece�
		-	poprawi� CMD_MAX_ARGUMENTS
		-	poprawi� CMD_LINE_BUFFER_LENGTH

CHANGELOG
0.22	+	CmdRes_t	Parse_AsciiString(const uint8_t * InputString, uint8_t * OutputString, uint8_t * OutputLength, const uint8_t MaxLength, const uint8_t MinLength);
0.21	*	Dostosowanie do Remote M2M
0.20	*	Poprawienie b��du w Console_UartInput() - znak CTRL-Z powodowa� wy�wietlenie poprzedniego polecenia zawsze na domy�lnym UART, 
0.19	+	Standardowe odpowiedzi OK i Error
0.18	+	Sprz�tanie kodu i optymalizacja
0.17	+	Timeout callback w Console_SendCommand()
0.16	*	Funkcja wywo�uj�ca polecenie w konsoli na innym procesorze i Callback wywo�ywany po zako�czeniu odbioru danych 
		+	void Console_SendCommand(Console_Struct * ConsoleInstance, uint8_t * Command, void (*DataReceivedCallback)(uint8_t * Buffer));
0.15	*	Pocz�tek prac nad przerobieniem interpretera na task i umo�liwienie uruchomienia kilku niezale�nych instancji, zmiana nazwy biblioteki z command na console
0.14	+	Nowe definicje w celu oszcz�dzania pami�ci: CMD_USE_ALL i CMD_USE_HELP
0.13	+	Przymiarki do wprowadzenia znak�w kontrolnych w celu zastosowania wiersza polece� do komunikacji mi�dzy dwoma procesorami
0.12	+	Definicje wszystkich znak�w specjalnych ASCII
		-	Usuni�cie command_typedef.h
		+	Dodanie command_config.h
0.11	*	Poprawianie b��d�w
0.10	+	Wydzielenie funkcji pobieraj�cej lini� polece� i analuzuj�cej na oddzielne funkcje:
		+	void Command_Interpreter(uint8_t * Buffer);
		+	Dodanie definicji znak�w specjalnych CR, LF, drobne optymalizacje
0.09	*	Poprawienie b��du nie pokazywania znaku "> " po wci�ni�ciu przycisku ESCAPE
0.08	*	Wydzielenie tablicy polece� do pliku command_table.h
0.07	+	CmdRes_t Parse_HexString(const uint8_t * InputString, uint8_t * OutputString, uint8_t * OutputLength, const uint8_t MaxLength = 255, const uint8_t MinLength = 0);
		+	CTRL-Z przywraca ostatnio wpisywane polecenie
0.06	*	void ///Command_Debug(CmdRes_t Result, uint8_t * Argument)
		+	CmdRes_t Parse_DecChar(uint8_t * InputChar, uint8_t * OutputChar);
		+	CmdRes_t Parse_Dec8(uint8_t * Argument, uint8_t * Output, uint8_t MaxValue = 255);
		+	CmdRes_t Parse_Dec16(uint8_t * Argument, uint16_t * Output, uint16_t MaxValue = 65535);
		+	CmdRes_t Parse_Dec32(uint8_t * Argument, uint32_t * Output, uint32_t MaxValue = 4294967295UL);
		+	CmdRes_t Parse_Dec64(uint8_t * Argument, uint64_t * Output, uint64_t MaxValue = 18446744073709551615UL);
0.05	*	Przeniesienie z biblioteki interpreter.cpp/h v004
		+	CmdRes_t Parse_HexChar(uint8_t * InputChar, uint8_t * OutputChar);
		+	CmdRes_t Parse_Hex8(uint8_t * Argument, uint8_t * Output);
		+	CmdRes_t Parse_Hex16(uint8_t * Argument, uint16_t * Output);
		+	CmdRes_t Parse_Hex32(uint8_t * Argument, uint32_t * Output);
		+	CmdRes_t Parse_Hex64(uint8_t * Argument, uint64_t * Output);
0.04	+	Dodanie obs�ugi backspace
0.03	+	Funckja ca�o�ciowo ograniaj�ca pobieranie znak�w do bufora, rozbijanie go na argumenty, wyszukiwanie odpowiadaj�cej
			funkcji, wywo�ywanie jej i przekazywanie do niej argument�w
0.02	+	void Interpreter_PrintStringHex(uint8_t * String, uint8_t Lenght);
0.01	*	Pierwsza wersja
		
HARDWARE
		-	Uart
*/


#ifndef CONSOLE_H_
#define CONSOLE_H_


#include <avr/io.h>
#include <string.h>
#include "console_config.h"
#include "../uCosmos/uCosmos.h"
#include "../uart/uart.h"

#if C_REMOTE
	#include "remote.h"
#endif

// Struktura do budowy tablicy polece�
struct Console_NamePointer_t {
	const char *Name;
	void	(*Pointer)(uint8_t argc, uint8_t * argv[]);		
};


// Tablica polece� oraz liczba polece�
extern const Console_NamePointer_t	Console_CommandList[];

// Typ wynikowy
enum Console_Res_t {
	Console_OK = 0,													// Zwracane przez wszystkie funkcje, je�eli zako�czy�y si� prawid�owo
	Console_ReceivedCommand,										// Console_UartInput() - odebrano pe�ne polecenie gotowe do dalszej analizy
	Console_BufferFull,												// Console_UartInput() - przepe�nienie bufora
	Console_InputCancelled,											// Console_UartInput() - wci�ni�to ESC, trzeba wy�wietli� ponownie znak zach�ty wiersza polece�
	Console_ErrorToFix = 255,										// Tylko do cel�w deweloperskich, normalnie �adna funkcja nie powinna zwraca� czego� takiego
};


// Typ wynikowy dla funkcji interpretuj�cych znaki
enum CmdRes_t {
	Cmd_OK = 0,									// Zwracane przez wszystkie funkcje, je�eli zako�czy�y si� prawid�owo
	Cmd_NotReady,								// Zwracane przez Command_LineInput(), kiedy nie podano znaku ENTER
	Cmd_UnknownCommand,							// Zwracane przez Command_Interpreter(), kiedy nie rozpozna polecenia
	Cmd_NoInput,
	Cmd_MissingArgument,
	Cmd_Overflow,
	Cmd_Underflow,
	Cmd_ParseError,
	Cmd_ExpectedHex,
	Cmd_ExpectedDec,
	Cmd_ReceivedACK,							// Zwracane przez Command_Interpreter(), kiedy zostanie otrzymane potwierdzenie odebrania polecenia z po��czonego uk�adu
	Cmd_ReceivedNAK,							// Zwracane przez Command_Interpreter(), kiedy NIE zostanie otrzymane potwierdzenie odebrania polecenia z po��czonego uk�adu
};



// Struktura do obs�ugi bufora polece�
struct Console_Struct {
	uint16_t			ReceivedCnt;						// Aktualna liczba znak�w w tablicy Buffer
	uint8_t 			Buffer[CMD_LINE_BUFFER_LENGTH];		// Bufor aktualnie wprowadzanego polecenia
	uint8_t				Buffer2[CMD_LINE_BUFFER_LENGTH];	// Bufor poprzednio wykonanego polecenia (przywo�ywany przez CTRL-Z
	USART_t *			UartInstance;						// Wska�nik do portu UART, kt�ry ma odpowiada� za komunikacj�
	bool				ControlUse;							// Czy u�ywa� znak kontrolny przy analizowaniu polecenia i przesy�aniu odpowiedzi
	uint8_t				CRCH;								// Otrzymany starszy bajt CRC dla odbieranego polecenia
	uint8_t				Token;								// Numer transakcji
	uint8_t				Flags;								// Zmienna flagowa do trybu M2M
	
	Console_Struct(USART_t * UartInstance, uint8_t Flags);	// Konstruktor
};

// Definicja dla zmiennej flagowej Console_Struct.M2M
#define		FLAGS_M2M_CMD				0b00000001			// Trwa odbieranie polecenia
#define		FLAGS_M2M_RETRY				0b00000010			// Ponowne odbieranie polecenia
#define		FLAGS_NEXT_BYTE_CRCH		0b00000100			// Nast�pny bajt jaki zostanie odebrany to starszy bajt CRC
#define		FLAGS_NEXT_BYTE_CRCL		0b00001000			// Nast�npy bajt jaki zostanie odebrany to m�odszy bajt CRC
#define		FLAGS_WRONG_CRC				0b00010000			// Wykryto niew�a�ciwe CRC, token nieistotny tylko czekamy a� zostanie przes�any
#define		FLAGS_NEXT_BYTE_TOKEN		0b00100000			// Nast�pny bajt jaki zostanie odebrany to token
#define		FLAGS_USE_M2M				0b01000000			// Konsola ma reagowa� na znaki u�ywane w trybie M2M
#define		FLAGS_USE_HMI				0b10000000			// Konsola ma reagowa� na znaki u�ywane podczas wpisywania polece� z klawiatury



// Definicje znak�w specjalnych ASCII
#define		NUL			uint8_t(0)
#define		SOH			uint8_t(1)
#define		STX			uint8_t(2)
#define		ETX			uint8_t(3)
#define		EOT			uint8_t(4)
#define		ENQ			uint8_t(5)
#define		ACK			uint8_t(6)
#define		BEL			uint8_t(7)
#define		BS			uint8_t(8)
#define		HT			uint8_t(9)
#define		LF			uint8_t(10)
#define		VT			uint8_t(11)
#define		FF			uint8_t(12)
#define		CR			uint8_t(13)
#define		SO			uint8_t(14)
#define		SI			uint8_t(15)
#define		DLE			uint8_t(16)
#define		DC1			uint8_t(17)
#define		DC2			uint8_t(18)
#define		DC3			uint8_t(19)
#define		DC4			uint8_t(20)
#define		NAK			uint8_t(21)
#define		SYN			uint8_t(22)
#define		ETB			uint8_t(23)
#define		CAN			uint8_t(24)
#define		EM			uint8_t(25)
#define		SUB			uint8_t(26)
#define		ESC			uint8_t(27)
#define		FS			uint8_t(28)
#define		GS			uint8_t(29)
#define		RS			uint8_t(30)
#define		US			uint8_t(31)
#define		DEL			uint8_t(127)

#define		LINEFEED	uint8_t(10)
#define		ENTER		uint8_t(13)
#define		ESCAPE		uint8_t(27)
#define		TAB			uint8_t(9)
#define		BACKSPACE1	uint8_t(8)
#define		BACKSPACE2	uint8_t(127)
#define		CTRL_Z		uint8_t(26)

// Funkcja wywo�ywana z task�w poszczeg�lnych instancji konsoli
void			Console_TaskHandler(Console_Struct * ConsoleInstance);
Console_Res_t	Console_UartInput(Console_Struct * ConsoleInstance);
void			Console_PromptShow(Console_Struct * ConsoleInstance);

//void			Console_StructPrint(Console_Struct * ConsoleInstance);

#if CMD_USE_ALL
 void			Console_ShowAllCommands(uint8_t argc, uint8_t * argv[]);
#endif



// Standardowe odpowiedzi
void		Console_ResponseOK(void);
void		Console_ResponseError(void);
void		Console_ResponseInProgress(void);
void		Console_ResponseTimeout(void);
void		Console_ResponseNotSupported(void);

// Interpretowanie danych
void		Console_Debug(const CmdRes_t Result, const uint8_t * Argument);

CmdRes_t	Parse_Hex8(const uint8_t * Argument, uint8_t * Output);
CmdRes_t	Parse_Hex16(const uint8_t * Argument, uint16_t * Output);
CmdRes_t	Parse_Hex32(const uint8_t * Argument, uint32_t * Output);
CmdRes_t	Parse_Hex64(const uint8_t * Argument, uint64_t * Output);
CmdRes_t	Parse_HexString(const uint8_t * InputString, uint8_t * OutputString, uint8_t * OutputLength, const uint8_t MaxLength = 255, const uint8_t MinLength = 0);

CmdRes_t	Parse_AsciiString(const uint8_t * InputString, uint8_t * OutputString, uint8_t * OutputLength, const uint8_t MaxLength = 255, const uint8_t MinLength = 0);

CmdRes_t	Parse_Dec8(const uint8_t * Argument, uint8_t * Output, const uint8_t MaxValue = 255);
CmdRes_t	Parse_Dec16(const uint8_t * Argument, uint16_t * Output, const uint16_t MaxValue = 65535);
CmdRes_t	Parse_Dec32(const uint8_t * Argument, uint32_t * Output, const uint32_t MaxValue = 4294967295UL);
CmdRes_t	Parse_Dec64(const uint8_t * Argument, uint64_t * Output, const uint64_t MaxValue = 18446744073709551615UL);
CmdRes_t	Parse_Dec32S(const uint8_t * Argument, int32_t * Output); //, const int32_t MaxValue = 268435455L);

#endif /* CONSOLE_H_ */