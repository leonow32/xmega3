// Wersja 0.01

#if C_CONSOLE

#include "console.h"

// Command list
#include "console_commands.h"

Console_Struct Inter;

// ========================================
// Command line interpreter
// ========================================


// Initialization
void Console_Init(void) {
	TaskAdd(Console_Task, 0);
}


// Por�wnuje badany string do wzorcowego a� do:
// - napotkania NULL w obu stringach
// - pierwszego r�nego znaku w obu stringach
// Tak skonstrukowana funkcja zajmuje mniej miejsca ni� strcmp() z biblioteki string.h
static inline bool Console_StrCmp(const char *String1, const char *String2) {
	while(1) {
		if((*String1 == 0) && (*String2 == 0)) return true;		// Doszli�my do ko�ca obu string�w, czyli s� sobie r�wne
		if(*String1++ != *String2++) return false;				// Przy pierwszej napotkanej r�nicy zwr�� fa�sz
	}
}


// Pobieranie jednego znaku z bufora wej�ciowego i kopiowanie do bufora konsoli lub wykonywanie akcji
Console_t Console_CharInput(void) {
	
	uint8_t ReceivedChar = CONSOLE_INPUT_STREAM();
	
	// Znaki printable dodajemy do bufora
	if(ReceivedChar >= ' ' && ReceivedChar <= '~') {
		
		// Sprawdzenie czy jest wolne miejsce w buforze
		if(Inter.ReceivedCnt >= CONSOLE_COMMAND_LENGTH) {
			return Console_BufferFull;
		}
		else {
			// Dodawanie znak�w do bufora 
			Inter.Buffer[Inter.ReceivedCnt++] = ReceivedChar;
			Print(ReceivedChar);
			return Console_OK;
		}
	}
	
	// Interpretowanie znak�w kontrolnych dla HMI
	switch(ReceivedChar) {
		
		// Enter
		case CR:
			// Zwracanie Console_OK tylko je�eli co� mamy w buforze, je�li bufor jest pusty to brak reakcji
			if(Inter.ReceivedCnt) {
				return Console_ReceivedCommand;	
			}
			break;
		
		// Backspace
		case BACKSPACE1:
		case BACKSPACE2:
			if(Inter.ReceivedCnt) {
				Inter.ReceivedCnt--;
				Inter.Buffer[Inter.ReceivedCnt] = 0;
				Print(ReceivedChar);
			}
			break;
		
		// Przywr�cenie ostatnio wpisywanego polecenia
		#if CONSOLE_USE_CTRL_Z
		case CTRL_Z:	
			// Kasowanie dotychczas wpisanego polecenia
			while(Inter.ReceivedCnt) {
				Inter.ReceivedCnt--;
				Inter.Buffer[Inter.ReceivedCnt] = 0;
				Print(BACKSPACE1); 
			}
			
			// Kopiowanie bufora poprzedniego polecanie do bufora aktywnego polecenia
			memcpy(Inter.Buffer, Inter.Buffer2, CONSOLE_COMMAND_LENGTH);
			Inter.ReceivedCnt = strlen((const char *)Inter.Buffer);
			
			// Wy�wietlenie zawarto�ci bufora tylko dla cz�owieka
			Print((const char *)Inter.Buffer);
			break;
		#endif
		
		// ESCAPE - to samo, ale wprowadzone z klawiatury przez u�ytkownika
		case ESC:
			Inter.ReceivedCnt = 0;
			memset(Inter.Buffer, 0, CONSOLE_COMMAND_LENGTH);
			return Console_InputCancelled;
			break;
		
		// Wszystkie inne znaki ignorujemy - w tym NUL i LF
		default:
			
			break;
	}
	
	return Console_OK;
}


// Dzielenie wej�ciowego stringu z wierza polece� na pojedyncze argumenty
// - argc												-	Wska�nik, przez kt�ry zwracana jest liczba znalezionych argument�w
// - argv												-	Wska�nik do tablicy wska�nik�w, w kt�rej zapisywane s� wska�niki do kolejnych argument�w
static inline Console_t Console_SplitArguments(uint8_t * argc, uint8_t * argv[]) {
	
	uint8_t		ArgCount		=	0;
	uint8_t *	CharPointer		=	Inter.Buffer;
	bool		NewArg			=	true;
	bool		StringMode		=	false;
	
	// Przesuwanie wska�nika a� do napotkania 0
	while(*CharPointer != 0) {
		switch(*CharPointer) {
		
			// Spacja = nowy argument je�li to nie jest "string obj�ty cudzys�owiem"
			case ' ':
				if(StringMode == false) {
					NewArg = true;
					*CharPointer = 0;			// zamiana spacji na NULL
				}
				else {
					if(NewArg) {
						argv[ArgCount] = CharPointer;
						ArgCount++;
						if(ArgCount == CONSOLE_MAX_ARGUMENTS) {				// Przekroczenie dopuszczalnej liczby argument�w
							Print("max arg");
							while(1);
							//Os_ResetExecute();
						}
						NewArg = false;
					}
				}
				break;
			
			case '"':
				if(StringMode) {
					StringMode = false;
					*CharPointer = 0;			// zmiana zamykaj�cego " na zero
				}
				else {
					StringMode = true;
					NewArg = true;
					
				}
				break;
			
			// Dowolny inny znak
			default:
				// Je�li wcze�niej by�a spacja to mamy tutaj pocz�tek nowego argumentu
				if(NewArg) {
					
					argv[ArgCount] = CharPointer;
					ArgCount++;
					if(ArgCount == CONSOLE_MAX_ARGUMENTS) {
						Print("max arg");
						while(1);
						//asm volatile("break");
						Os_ResetExecute();
					}
					NewArg = false;
				}
				break;
		}
		
		// Przesuwanie wska�nika na nast�pny znak linii polece�
		CharPointer++;	
	}
	
	*argc = ArgCount;
	
	return Console_OK;
}


// Wyszukiwanie funkcji dla wpisanego polecenia
// Nazwa polecenia jest przechowywana w argumencie zerowym argv[0]
// Funkcja zwraca wska�nik do funkcji typu void pobieraj�cej argumenty uint8_t argc, uint8_t * argv[]
// Argumentem przyjmowanym przez Console_FindCommand() jest wska�nik do stringu EnteredName zawieraj�cego polecenie wpisane przez u�ytkownika
// Je�eli Console_FindCommand nie znajdzie funkcji odpowiadaj�cej poleceniu to zwraca wska�nik NULL
static inline void (*Console_FindPointer(uint8_t * EnteredName))(uint8_t argc, uint8_t * argv[]) {
	
	for(uint8_t i=0; i<(sizeof(Console_CommandList)/sizeof(Console_NamePointer_t)); i++) {
		if(Console_StrCmp((const char *)EnteredName, Console_CommandList[i].Name)) {
			return Console_CommandList[i].Pointer;
		}
	}
	return NULL;
}


// Funkcja wywo�ywana z tasku obs�uguj�cego konsol�
void Console_TaskHandler(void) {
	
	// Pobieranie danych
	while(CONSOLE_INPUT_RECEIVED_CNT()) {
		
		// Przekazywanie znak�w z bufora wej�ciowego do bufora konsoli i podejmywanie dalszych dzia�a w zale�no�ci od Console_Result
		Console_t Console_Result;
		Console_Result =  Console_CharInput();
		
		// Je�eli zako�czono odbieranie polecenia
		if(Console_Result == Console_ReceivedCommand) {
			
			// Zmienne
			uint8_t			argc = 0;												// Liczba wpisanych argument�w
			uint8_t *		argv[CONSOLE_MAX_ARGUMENTS];							// Tablica wska�nik�w do argument�w
			memset(argv, 0, sizeof(argv));
			
			// Kopiowanie do bufora CTRL-Z
			#if CONSOLE_USE_CTRL_Z
				memcpy(Inter.Buffer2, Inter.Buffer, CONSOLE_COMMAND_LENGTH);
			#endif
			
			// Dzielenie bufora na poszczeg�lne argumenty
			Console_SplitArguments(&argc, argv);
			
			// Wyszukiwanie wska�nika 
			void (*CommandPointer)(uint8_t argc, uint8_t * argv[]) = Console_FindPointer(argv[0]);
			
			// Zej�cie do nowej linii, �eby w trybie r�cznym �adnie wygl�da�o w terminalu
			Print_NL();
			
			// Wykonanie polecenia, je�li rozpoznano
			if(CommandPointer) {
				
				// Wywo�anie funkcji odpowiadaj�cej poleceniu
				CommandPointer(argc, argv);
			}
			
			// Je�eli nie rozpoznano polecenia
			else {
				Print("Bad command");
			}
			
			// Czyszczenie aktualnego bufora wiersza polece�
			memset(Inter.Buffer, 0, CONSOLE_COMMAND_LENGTH);
			Inter.ReceivedCnt = 0;
			
			// Prompt by zasygnalizowa� gotowo�� do przyj�cia kolejnego polecenia
			Console_PromptShow();
		}
		
		// Wci�ni�to ESCAPE
		else if(Console_Result == Console_InputCancelled) {
			Console_PromptShow();
		}
	}
}


// System task to periodicaly execute interpreter routine
task_t Console_Task(runmode_t RunMode) {
	
	// Normaln execution
	if(RunMode == Run) {
		Console_TaskHandler();
	}
	
	// Constructor
	else if(RunMode == FirstRun) {
		Console_PromptShow();						// TODO zrobi� co�, �eby prompt nie pokazywa� si� w trakcie wysy�ania komunikatu o utworzeniu tasku
	}
	
	// Destructor
	else if(RunMode == Close) {
	}
	
	// Identification
	#if OS_USE_TASK_IDENTIFY
	else if(RunMode == Identify) {
		Print("Console");
	}
	#endif
	
	return TaskOK;
}


// Display command line prompt
void Console_PromptShow(void) {
	Print("\r\n > ");
}


// Clean all buffers
void Console_BufferFlush(void) {
	memset(&Inter, 0, sizeof(Inter));
};


// ========================================
// Argument parsers
// ========================================


// Debugowanie b��d�w
void Parse_Debug(const Parse_t Result, const uint8_t * Argument) {
	Print("Error");
	if(Argument != NULL) {
		Print(" in agument \"");
		Print((const char *)Argument);
	}
	Print("\": ");
	
	switch(Result) {
		case Parse_OK:									Print("OK");								break;
		case Parse_NotReady:							Print("Not ready");							break;
		case Parse_UnknownCommand:						Print("Unknown command");					break;
		case Parse_NoInput:								Print("No input");							break;
		case Parse_Overflow:							Print("Overflow");							break;
		case Parse_MissingArgument:						Print("Missing arg");						break;
		case Parse_Underflow:							Print("Underflow");							break;
		case Parse_ParseError:							Print("Parse error");						break;
		case Parse_ExpectedHex:							Print("Expected Hex");						break;
		case Parse_ExpectedDec:							Print("Expected Dec");						break;
		case Parse_ReceivedACK:							Print("Received ACK");						break;
		case Parse_ReceivedNAK:							Print("Received NAK");						break;
	}
}



// Funkcja przekszta�ca znak ASCII HEX na warto�� binarn�
// - InputChar	- Wska�nik do badanego znaku
// - OutputChar	- Wska�nik do zmiennej, w kt�rej ma by� zapisany nibble
static Parse_t Parse_HexChar(const uint8_t * InputChar, uint8_t * OutputChar) {
	if(*InputChar >= '0' && *InputChar <= '9') {
		*OutputChar = *InputChar - '0';
		return Parse_OK;
	}
	else if(*InputChar >= 'A' && *InputChar <= 'F') {
		*OutputChar = *InputChar - 55;
		return Parse_OK;
	}
	else if(*InputChar >= 'a' && *InputChar <= 'f') {
		*OutputChar = *InputChar - 87;
		return Parse_OK; 
	}
	else {
		return Parse_ExpectedHex;
	}
}


// TODO po co to jest?
static Parse_t Parse_HexChar(const uint8_t * InputChar, uint8_t * OutputChar, bool HighNibble) {
	uint8_t Temp = *InputChar;
	
	// Interpretowanie zaku ASCII
	if(Temp >= '0' && Temp <= '9') {
		Temp = Temp - '0';
	}
	else if(Temp >= 'A' && Temp <= 'F') {
		Temp = Temp - 55;
	}
	else if(Temp >= 'a' && Temp <= 'f') {
		Temp = Temp - 87;
	}
	else {
		return Parse_ExpectedHex;
	}
	
	// Przesuwanie je�eli to jest starszy nibble
	if(HighNibble) {
		Temp <<= 4;
		*OutputChar |= Temp;
	}
	else {
	// Zapisywanie wyniku
		*OutputChar = Temp;
	}
	
	return Parse_OK; 
}


// Przetwarzanie stringu od ko�ca, a output od pocz�tku
// Zmienna wskazywana przez *Output musi by� wyzerowana, inaczej b�dzie b��d losowo zainicjalizowanej pami�ci
Parse_t Parse_HexNum(const uint8_t * Argument, void * Output, uint8_t Characters) {
	
	Parse_t Result;
	const uint8_t * OrgArgument = Argument;
	
	// Kontrola czy podano argument
	if(Argument == NULL) {
		Result = Parse_MissingArgument;
		goto End;
	}
	
	// Przesuni�cie wska�nika na koniec ci�gu znak�w argumentu
	Argument = Argument + Characters;
	
	// Sprawdzanie czy ostatni bajt argumentu to 0, je�eli nie to znaczy, �e przes�ano wi�cej znak� ni� jest potrzebne dla konkretnego typu zmiennej
	if(*Argument != 0) {
		Result = Parse_Overflow;
		goto End;
	}
	
	// Przetwarzanie wszystkich znak�w ASCII od ko�ca
	do {
		
		uint8_t HighNibble = Characters & 0x01;
		Result = Parse_HexChar(--Argument, (uint8_t*)Output, HighNibble);
		if(Result) {
			goto End;
		}
		if(HighNibble) {
			Output = (uint8_t *)Output + 1;
		}
	} while(--Characters);
	
	// Wy�wietlenie informacji o ewentualnym b��dzie
	End:
	if(Result) {
		Parse_Debug(Result, OrgArgument);
	}
	return Result;
}


// Parsowanie liczby HEX 8-bitowej
// - Argument	- Wska�nik do argumentu, kt�ry ma by� przetworzony
// - Output		- Wska�nik do zmiennej, w kt�rej b�dzie zwr�cony wynik
Parse_t Parse_Hex8(const uint8_t * Argument, uint8_t * Output) {
	*Output = 0;
	return Parse_HexNum(Argument, Output, 2);
}


// Parsowanie liczby HEX 16-bitowej
// - Argument	- Wska�nik do argumentu, kt�ry ma by� przetworzony
// - Output		- Wska�nik do zmiennej, w kt�rej b�dzie zwr�cony wynik
Parse_t Parse_Hex16(const uint8_t * Argument, uint16_t * Output) {
	*Output = 0;
	return Parse_HexNum(Argument, Output, 4);
}


// Parsowanie liczby HEX 32-bitowej
// - Argument	- Wska�nik do argumentu, kt�ry ma by� przetworzony
// - Output		- Wska�nik do zmiennej, w kt�rej b�dzie zwr�cony wynik
Parse_t Parse_Hex32(const uint8_t * Argument, uint32_t * Output) {
	*Output = 0;
	return Parse_HexNum(Argument, Output, 8);
}


// Parsowanie liczby dziesi�tnej 8-bitowej
// Funkcja przekszta�ca znak ASCII HEX na warto�� binarn�
// - InputChar	- Wska�nik do badanego znaku
// - OutputChar	- Wska�nik do zmiennej, w kt�rej ma by� zapisany nibble
static Parse_t Parse_DecChar(const uint8_t * InputChar, uint8_t * OutputChar) {
	if(*InputChar >= '0' && *InputChar <= '9') {
		*OutputChar = *InputChar - '0';
		return Parse_OK;
	}
	else {
		return Parse_ExpectedDec;
	}
}


// Parsowanie liczby dziesi�tnej 8-bitowej
// - Argument	- Wska�nik do argumentu, kt�ry ma by� przetworzony
// - Output		- Wska�nik do zmiennej, w kt�rej b�dzie zwr�cony wynik
Parse_t Parse_Dec8(const uint8_t * Argument, uint8_t * Output, const uint8_t MaxValue) {
	
	const uint8_t * OrgArgument = Argument;
	uint8_t Digit; 	
	uint8_t Temp = 0;
	uint8_t Temp2;
	Parse_t Result;
	
	// Kontrola czy podano argument
	if(Argument == NULL) {
		Result = Parse_MissingArgument;
		goto End;
	}
	
	// Przetwarzamy wszystkie znaki po kolei
	while(*Argument != 0) {
		Result = Parse_DecChar(Argument++, &Digit);
		if(Result) {
			goto End;
			//return Result;
		}
		
		Temp2 = Temp * 10 + Digit;
		if(Temp <= Temp2) {
			Temp = Temp2;
		}
		else {
			Result = Parse_Overflow;
			goto End;
			//return Parse_Overflow;
		}
	}
	
	// Zwracanie wyniku
	if(Temp <= MaxValue) {
		*Output = Temp;
	}
	else {
		Result = Parse_Overflow;
	}
	
	// Wy�wietlenie informacji o ewentualnym b��dzie i zwr�cenie wyniku
	End:
	if(Result) {
		Parse_Debug(Result, OrgArgument);
	}
	return Result;
}


// Parsowanie liczby dziesi�tnej 16-bitowej
// - Argument	- Wska�nik do argumentu, kt�ry ma by� przetworzony
// - Output		- Wska�nik do zmiennej, w kt�rej b�dzie zwr�cony wynik
Parse_t Parse_Dec16(const uint8_t * Argument, uint16_t * Output, const uint16_t MaxValue) {
	
	const uint8_t * OrgArgument = Argument;
	uint8_t Digit; 	
	uint16_t Temp = 0;
	uint16_t Temp2;
	Parse_t Result;
	
	// Kontrola czy podano argument
	if(Argument == NULL) {
		Result = Parse_MissingArgument;
		goto End;
	}
	
	// Przetwarzamy wszystkie znaki po kolei
	while(*Argument != 0) {
		Result = Parse_DecChar(Argument++, &Digit);
		if(Result) {
			goto End;
		}
		
		Temp2 = Temp * 10 + Digit;
		if(Temp <= Temp2) {
			Temp = Temp2;
		}
		else {
			Result = Parse_Overflow;
			goto End;
			//return Parse_Overflow;
		}
	} 
	
	// Zwracanie wyniku
	if(Temp <= MaxValue) {
		*Output = Temp;
	}
	else {
		Result = Parse_Overflow;
	}
	
	// Wy�wietlenie informacji o ewentualnym b��dzie i zwr�cenie wyniku
	End:
	if(Result) {
		Parse_Debug(Result, OrgArgument);
	}
	return Result;
}


// Parsowanie liczby dziesi�tnej 32-bitowej
// - Argument	- Wska�nik do argumentu, kt�ry ma by� przetworzony
// - Output		- Wska�nik do zmiennej, w kt�rej b�dzie zwr�cony wynik
Parse_t Parse_Dec32(const uint8_t * Argument, uint32_t * Output, const uint32_t MaxValue) {
	
	const uint8_t * OrgArgument = Argument;
	uint8_t Digit; 	
	uint32_t Temp = 0;
	uint32_t Temp2;
	Parse_t Result;
	
	// Kontrola czy podano argument
	if(Argument == NULL) {
		Result = Parse_MissingArgument;
		goto End;
	}
	
	// Przetwarzamy wszystkie znaki po kolei
	while(*Argument != 0) {
		Result = Parse_DecChar(Argument++, &Digit);
		if(Result) {
			goto End;
		}
		
		Temp2 = Temp * 10 + Digit;
		if(Temp <= Temp2) {
			Temp = Temp2;
		}
		else {
			Result = Parse_Overflow;
			goto End;
		}
	}
	
	// Zwracanie wyniku
	if(Temp <= MaxValue) {
		*Output = Temp;
	}
	else {
		Result = Parse_Overflow;
	}
	
	// Wy�wietlenie informacji o ewentualnym b��dzie i zwr�cenie wyniku
	End:
	if(Result) {
		Parse_Debug(Result, OrgArgument);
	}
	return Result;
}


// Parsowanie liczby dziesi�tnej 32-bitowej ze znakiem
// - Argument	- Wska�nik do argumentu, kt�ry ma by� przetworzony
// - Output		- Wska�nik do zmiennej, w kt�rej b�dzie zwr�cony wynik
Parse_t Parse_Dec32S(const uint8_t * Argument, int32_t * Output) {
	
	const uint8_t * OrgArgument = Argument;
	uint8_t Digit; 	
	int32_t Temp = 0;
	int32_t Temp2;
	Parse_t Result;
	bool Negative = false;
	
	// Kontrola czy podano argument
	if(Argument == NULL) {
		Result = Parse_MissingArgument;
		goto End;
	}
	
	// Czy znak minus na pocz�tku
	if(*Argument == '-') {
		Argument++;
		Negative = true;
	}
	
	// Przetwarzamy wszystkie znaki po kolei
	while(*Argument != 0) {
		Result = Parse_DecChar(Argument++, &Digit);
		if(Result) {
			goto End;
		}
		
		Temp2 = Temp * 10 + Digit;
		if(Temp <= Temp2) {
			Temp = Temp2;
		}
		else {
			Result = Parse_Overflow;
			goto End;
		}
	}
	
	// Zwracanie wyniku
	if(Negative) {
		Temp = -Temp;
	}
	*Output = Temp;
	
	// Wy�wietlenie informacji o ewentualnym b��dzie i zwr�cenie wyniku
	End:
	if(Result) {
		Parse_Debug(Result, OrgArgument);
	}
	return Result;
}

// Konwertowanie stringu znak�w ASCII HEX na dane zapisane binarnie. W rezultacie wynikowy string jest 2x kr�tszy od
// stringu wej�ciowego (je�li by�y w nim spacje to dodatowo zosta�y wyci�te). Wszystkie nadmiarowe znaki zostaj� zast�pione zerami,
// aby mo�na by�o wykorzysta� miejsce w pami�ci, kt�re jest dotychczas zajmowane przez string wej�ciowy.
// - String		- wej�cie i wyj�cie
// - MaxLength	- maksymalna dopuszczalna d�ogo�� stringu po przetworzeniu, domy�lnie 255 znak�w
// - MinLength	- minimalna dopuszczalna d�ugo�� stringu po przetworzeniu, domy��nie 0 znak�w
Parse_t Parse_HexString(const uint8_t * InputString, uint8_t * OutputString, uint8_t * OutputLength, const uint8_t MaxLength, const uint8_t MinLength) {
	
	// Wska�niki aktualnie przetwarzanych znak�w
	const uint8_t * OrgArgument = InputString;
	uint8_t NibbleH;
	uint8_t NibbleL;
	*OutputLength = 0;
	Parse_t Result;
	
	// przetwarzanie a� do napotkania znaku 0
	while(*InputString != 0) {
		
		// Kontrola przepe�nienia
		if(*OutputLength == MaxLength) {
			Result = Parse_Overflow;
			goto End;
		}
		
		// Pomijanie spacji
		if(*InputString == ' ') {
			InputString++;
			continue;
		}
		
		// Przetwarzanie starszego nibble
		Result = Parse_HexChar(InputString++, &NibbleH);
		if(Result) {
			goto End;
			//return Result;
		}
		
		// Przetwarzanie m�odszego nibble
		Result = Parse_HexChar(InputString++, &NibbleL);
		if(Result) {
			goto End;
		}
		
		// Sklejanie wyniku
		*OutputString++ = NibbleH << 4 | NibbleL;
		
		// Licznie znak�w w stringu wynikowym
		(*OutputLength)++;
	}
	
	// Kontrola d�ugo�ci
	if(*OutputLength < MinLength) {
		Result = Parse_Underflow;
	}
	
	// Wy�wietlenie informacji o ewentualnym b��dzie i zwr�cenie wyniku
	End:
	if(Result) {
		Parse_Debug(Result, OrgArgument);
	}
	return Result;
}


// Parsowanie stringu ASCII
Parse_t Parse_AsciiString(const uint8_t * InputString, uint8_t * OutputString, uint8_t * OutputLength, const uint8_t MaxLength, const uint8_t MinLength) {
	
	// Wska�niki aktualnie przetwarzanych znak�w
	const uint8_t * OrgArgument = InputString;
	*OutputLength = 0;
	Parse_t Result = Parse_OK;
	
	// przetwarzanie a� do napotkania znaku 0
	while(*InputString != 0) {
		
		// Kontrola przepe�nienia
		if(*OutputLength == MaxLength) {
			Result = Parse_Overflow;
			goto End;
		}
		
		// Kopiowanie znaku
		*OutputString++ = *InputString++;
		
		// Licznie znak�w w stringu wynikowym
		(*OutputLength)++;
	}
	
	// Kontrola d�ugo�ci
	if(*OutputLength < MinLength) {
		Result = Parse_Underflow;
	}
	
	// Wy�wietlenie informacji o ewentualnym b��dzie i zwr�cenie wyniku
	End:
	if(Result) {
		Parse_Debug(Result, OrgArgument);
	}
	return Result;
}


// ========================================
// Demo commands
// ========================================

#if CONSOLE_USE_COMMAND_ALL

// Print all known commands
void Console_CmdAll(uint8_t argc, uint8_t * argv[]) {
	for(uint16_t i=0; i<(sizeof(Console_CommandList)/sizeof(Console_NamePointer_t)); i++) {
		Print_Dec(i);
		Print(":\t");
		Print_Hex(uint16_t(Console_CommandList[i].Pointer));
		Print('\t');
		Print((const char *)Console_CommandList[i].Name);
		Print_NL();
	}
}
#endif


#if CONSOLE_USE_DEMO_COMMANDS

// Print all provided arguments
void Console_CmdArgs(uint8_t argc, uint8_t * argv[]) {
	Print("\r\nShow all passed arguments\r\nargc = ");
	Print_Dec(argc);
	for(uint8_t i=0; i<CONSOLE_MAX_ARGUMENTS; i++) {
		Print_NL();
		Print_Dec(i);
		Print(":\t");
		Print_Hex((uint16_t)argv[i]);
		if(argv[i]) {
			Print('\t');
			Print((const char *)argv[i]);
		}
	}
}


// Print first argument
void Console_CmdEcho(uint8_t argc, uint8_t * argv[]) {
	if(argc != 1) {
		Print((const char *)argv[1]);
	}
}


// 
void Console_CmdHex8(uint8_t argc, uint8_t * argv[]) {
	
	uint8_t Value;
	Parse_t Result;
	
	Result = Parse_Hex8(argv[1], &Value);
	//Result = Parse_HexNum(argv[1], &Value, 2);
	if(Result) {
		//////Command_Debug(Result, argv[1]);
		return;
	}

	Print_Dec(Value);
}


void Console_CmdHex16(uint8_t argc, uint8_t * argv[]) {
	
	uint16_t Value;
	Parse_t Result;
	
	Result = Parse_Hex16(argv[1], &Value);
	//Result = Parse_HexNum(argv[1], &Value, 4);
	if(Result) {
		//////Command_Debug(Result, argv[1]);
		return;
	}

	Print_Dec(Value);
}


void Console_CmdHex32(uint8_t argc, uint8_t * argv[]) {
	
	uint32_t Value;
	Parse_t Result;
	
	Result = Parse_Hex32(argv[1], &Value);
	//Result = Parse_HexNum(argv[1], &Value, 8);
	if(Result) {
		//////Command_Debug(Result, argv[1]);
		return;
	}

	Print_Dec(Value);
}





void Console_CmdDec8(uint8_t argc, uint8_t * argv[]) {
	
	uint8_t Value = 0;
	Parse_t Result;
	
	Result = Parse_Dec8(argv[1], &Value, 100);
	if(Result) {
		return;
	}
	
	Print_Dec(Value);
}


void Console_CmdDec16(uint8_t argc, uint8_t * argv[]) {
	
	uint16_t Value = 0;
	Parse_t Result;
	
	Result = Parse_Dec16(argv[1], &Value, 10000);
	if(Result) {
		return;
	}
	
	Print_Dec(Value);
}


void Console_CmdDec32(uint8_t argc, uint8_t * argv[]) {
	
	uint32_t Value = 0;
	Parse_t Result;
	
	Result = Parse_Dec32(argv[1], &Value, 1000000);
	if(Result) {
		return;
	}
	
	Print_Dec(Value);
}


void Console_CmdHexString(uint8_t argc, uint8_t * argv[]) {
	uint8_t Buffer[64];
	uint8_t Length;
	Parse_t Result;
	
	Result = Parse_HexString(argv[1], Buffer, &Length);
	if(Result) {
		return;
	}
	
	Print("Length: ");
	Print_Dec(Length);
	Print_NL();
	Print_Dump(Buffer, Length);
}


void Console_CmdAsciiString(uint8_t argtc, uint8_t * argv[]) {
	uint8_t Buffer[32];
	uint8_t Length;
	Parse_t Result;
	
	Result = Parse_AsciiString(argv[1], Buffer, &Length, sizeof(Buffer), 3);
	if(Result) {
		return;
	}
	
	Print("Length: ");
	Print_Dec(Length);
	Print_NL();
	Print_Dump(Buffer, Length);
}


#endif

#endif
