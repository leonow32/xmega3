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


// Porównuje badany string do wzorcowego a¿ do:
// - napotkania NULL w obu stringach
// - pierwszego ró¿nego znaku w obu stringach
// Tak skonstrukowana funkcja zajmuje mniej miejsca ni¿ strcmp() z biblioteki string.h
static inline bool Console_StrCmp(const char *String1, const char *String2) {
	while(1) {
		if((*String1 == 0) && (*String2 == 0)) return true;		// Doszliœmy do koñca obu stringów, czyli s¹ sobie równe
		if(*String1++ != *String2++) return false;				// Przy pierwszej napotkanej ró¿nicy zwróæ fa³sz
	}
}


// Pobieranie jednego znaku z bufora wejœciowego i kopiowanie do bufora konsoli lub wykonywanie akcji
Console_t Console_CharInput(void) {
	
	uint8_t ReceivedChar = CONSOLE_INPUT_STREAM();
	
	// Znaki printable dodajemy do bufora
	if(ReceivedChar >= ' ' && ReceivedChar <= '~') {
		
		// Sprawdzenie czy jest wolne miejsce w buforze
		if(Inter.ReceivedCnt >= CONSOLE_COMMAND_LENGTH) {
			return Console_BufferFull;
		}
		else {
			// Dodawanie znaków do bufora 
			Inter.Buffer[Inter.ReceivedCnt++] = ReceivedChar;
			Print(ReceivedChar);
			return Console_OK;
		}
	}
	
	// Interpretowanie znaków kontrolnych dla HMI
	switch(ReceivedChar) {
		
		// Enter
		case CR:
			// Zwracanie Console_OK tylko je¿eli coœ mamy w buforze, jeœli bufor jest pusty to brak reakcji
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
		
		// Przywrócenie ostatnio wpisywanego polecenia
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
			
			// Wyœwietlenie zawartoœci bufora tylko dla cz³owieka
			Print((const char *)Inter.Buffer);
			break;
		#endif
		
		// ESCAPE - to samo, ale wprowadzone z klawiatury przez u¿ytkownika
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


// Dzielenie wejœciowego stringu z wierza poleceñ na pojedyncze argumenty
// - argc												-	WskaŸnik, przez który zwracana jest liczba znalezionych argumentów
// - argv												-	WskaŸnik do tablicy wskaŸników, w której zapisywane s¹ wskaŸniki do kolejnych argumentów
static inline Console_t Console_SplitArguments(uint8_t * argc, uint8_t * argv[]) {
	
	uint8_t		ArgCount		=	0;
	uint8_t *	CharPointer		=	Inter.Buffer;
	bool		NewArg			=	true;
	bool		StringMode		=	false;
	
	// Przesuwanie wskaŸnika a¿ do napotkania 0
	while(*CharPointer != 0) {
		switch(*CharPointer) {
		
			// Spacja = nowy argument jeœli to nie jest "string objêty cudzys³owiem"
			case ' ':
				if(StringMode == false) {
					NewArg = true;
					*CharPointer = 0;			// zamiana spacji na NULL
				}
				else {
					if(NewArg) {
						argv[ArgCount] = CharPointer;
						ArgCount++;
						if(ArgCount == CONSOLE_MAX_ARGUMENTS) {				// Przekroczenie dopuszczalnej liczby argumentów
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
					*CharPointer = 0;			// zmiana zamykaj¹cego " na zero
				}
				else {
					StringMode = true;
					NewArg = true;
					
				}
				break;
			
			// Dowolny inny znak
			default:
				// Jeœli wczeœniej by³a spacja to mamy tutaj pocz¹tek nowego argumentu
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
		
		// Przesuwanie wskaŸnika na nastêpny znak linii poleceñ
		CharPointer++;	
	}
	
	*argc = ArgCount;
	
	return Console_OK;
}


// Wyszukiwanie funkcji dla wpisanego polecenia
// Nazwa polecenia jest przechowywana w argumencie zerowym argv[0]
// Funkcja zwraca wskaŸnik do funkcji typu void pobieraj¹cej argumenty uint8_t argc, uint8_t * argv[]
// Argumentem przyjmowanym przez Console_FindCommand() jest wskaŸnik do stringu EnteredName zawieraj¹cego polecenie wpisane przez u¿ytkownika
// Je¿eli Console_FindCommand nie znajdzie funkcji odpowiadaj¹cej poleceniu to zwraca wskaŸnik NULL
static inline void (*Console_FindPointer(uint8_t * EnteredName))(uint8_t argc, uint8_t * argv[]) {
	
	for(uint8_t i=0; i<(sizeof(Console_CommandList)/sizeof(Console_NamePointer_t)); i++) {
		if(Console_StrCmp((const char *)EnteredName, Console_CommandList[i].Name)) {
			return Console_CommandList[i].Pointer;
		}
	}
	return NULL;
}


// Funkcja wywo³ywana z tasku obs³uguj¹cego konsolê
void Console_TaskHandler(void) {
	
	// Pobieranie danych
	while(CONSOLE_INPUT_RECEIVED_CNT()) {
		
		// Przekazywanie znaków z bufora wejœciowego do bufora konsoli i podejmywanie dalszych dzia³a w zale¿noœci od Console_Result
		Console_t Console_Result;
		Console_Result =  Console_CharInput();
		
		// Je¿eli zakoñczono odbieranie polecenia
		if(Console_Result == Console_ReceivedCommand) {
			
			// Zmienne
			uint8_t			argc = 0;												// Liczba wpisanych argumentów
			uint8_t *		argv[CONSOLE_MAX_ARGUMENTS];							// Tablica wskaŸników do argumentów
			memset(argv, 0, sizeof(argv));
			
			// Kopiowanie do bufora CTRL-Z
			#if CONSOLE_USE_CTRL_Z
				memcpy(Inter.Buffer2, Inter.Buffer, CONSOLE_COMMAND_LENGTH);
			#endif
			
			// Dzielenie bufora na poszczególne argumenty
			Console_SplitArguments(&argc, argv);
			
			// Wyszukiwanie wskaŸnika 
			void (*CommandPointer)(uint8_t argc, uint8_t * argv[]) = Console_FindPointer(argv[0]);
			
			// Zejœcie do nowej linii, ¿eby w trybie rêcznym ³adnie wygl¹da³o w terminalu
			Print_NL();
			
			// Wykonanie polecenia, jeœli rozpoznano
			if(CommandPointer) {
				
				// Wywo³anie funkcji odpowiadaj¹cej poleceniu
				CommandPointer(argc, argv);
			}
			
			// Je¿eli nie rozpoznano polecenia
			else {
				Print("Bad command");
			}
			
			// Czyszczenie aktualnego bufora wiersza poleceñ
			memset(Inter.Buffer, 0, CONSOLE_COMMAND_LENGTH);
			Inter.ReceivedCnt = 0;
			
			// Prompt by zasygnalizowaæ gotowoœæ do przyjêcia kolejnego polecenia
			Console_PromptShow();
		}
		
		// Wciœniêto ESCAPE
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
		Console_PromptShow();						// TODO zrobiæ coœ, ¿eby prompt nie pokazywa³ siê w trakcie wysy³ania komunikatu o utworzeniu tasku
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


// Debugowanie b³êdów
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



// Funkcja przekszta³ca znak ASCII HEX na wartoœæ binarn¹
// - InputChar	- WskaŸnik do badanego znaku
// - OutputChar	- WskaŸnik do zmiennej, w której ma byæ zapisany nibble
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
	
	// Przesuwanie je¿eli to jest starszy nibble
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


// Przetwarzanie stringu od koñca, a output od pocz¹tku
// Zmienna wskazywana przez *Output musi byæ wyzerowana, inaczej bêdzie b³¹d losowo zainicjalizowanej pamiêci
Parse_t Parse_HexNum(const uint8_t * Argument, void * Output, uint8_t Characters) {
	
	Parse_t Result;
	const uint8_t * OrgArgument = Argument;
	
	// Kontrola czy podano argument
	if(Argument == NULL) {
		Result = Parse_MissingArgument;
		goto End;
	}
	
	// Przesuniêcie wskaŸnika na koniec ci¹gu znaków argumentu
	Argument = Argument + Characters;
	
	// Sprawdzanie czy ostatni bajt argumentu to 0, je¿eli nie to znaczy, ¿e przes³ano wiêcej znakó ni¿ jest potrzebne dla konkretnego typu zmiennej
	if(*Argument != 0) {
		Result = Parse_Overflow;
		goto End;
	}
	
	// Przetwarzanie wszystkich znaków ASCII od koñca
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
	
	// Wyœwietlenie informacji o ewentualnym b³êdzie
	End:
	if(Result) {
		Parse_Debug(Result, OrgArgument);
	}
	return Result;
}


// Parsowanie liczby HEX 8-bitowej
// - Argument	- WskaŸnik do argumentu, który ma byæ przetworzony
// - Output		- WskaŸnik do zmiennej, w której bêdzie zwrócony wynik
Parse_t Parse_Hex8(const uint8_t * Argument, uint8_t * Output) {
	*Output = 0;
	return Parse_HexNum(Argument, Output, 2);
}


// Parsowanie liczby HEX 16-bitowej
// - Argument	- WskaŸnik do argumentu, który ma byæ przetworzony
// - Output		- WskaŸnik do zmiennej, w której bêdzie zwrócony wynik
Parse_t Parse_Hex16(const uint8_t * Argument, uint16_t * Output) {
	*Output = 0;
	return Parse_HexNum(Argument, Output, 4);
}


// Parsowanie liczby HEX 32-bitowej
// - Argument	- WskaŸnik do argumentu, który ma byæ przetworzony
// - Output		- WskaŸnik do zmiennej, w której bêdzie zwrócony wynik
Parse_t Parse_Hex32(const uint8_t * Argument, uint32_t * Output) {
	*Output = 0;
	return Parse_HexNum(Argument, Output, 8);
}


// Parsowanie liczby dziesiêtnej 8-bitowej
// Funkcja przekszta³ca znak ASCII HEX na wartoœæ binarn¹
// - InputChar	- WskaŸnik do badanego znaku
// - OutputChar	- WskaŸnik do zmiennej, w której ma byæ zapisany nibble
static Parse_t Parse_DecChar(const uint8_t * InputChar, uint8_t * OutputChar) {
	if(*InputChar >= '0' && *InputChar <= '9') {
		*OutputChar = *InputChar - '0';
		return Parse_OK;
	}
	else {
		return Parse_ExpectedDec;
	}
}


// Parsowanie liczby dziesiêtnej 8-bitowej
// - Argument	- WskaŸnik do argumentu, który ma byæ przetworzony
// - Output		- WskaŸnik do zmiennej, w której bêdzie zwrócony wynik
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
	
	// Wyœwietlenie informacji o ewentualnym b³êdzie i zwrócenie wyniku
	End:
	if(Result) {
		Parse_Debug(Result, OrgArgument);
	}
	return Result;
}


// Parsowanie liczby dziesiêtnej 16-bitowej
// - Argument	- WskaŸnik do argumentu, który ma byæ przetworzony
// - Output		- WskaŸnik do zmiennej, w której bêdzie zwrócony wynik
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
	
	// Wyœwietlenie informacji o ewentualnym b³êdzie i zwrócenie wyniku
	End:
	if(Result) {
		Parse_Debug(Result, OrgArgument);
	}
	return Result;
}


// Parsowanie liczby dziesiêtnej 32-bitowej
// - Argument	- WskaŸnik do argumentu, który ma byæ przetworzony
// - Output		- WskaŸnik do zmiennej, w której bêdzie zwrócony wynik
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
	
	// Wyœwietlenie informacji o ewentualnym b³êdzie i zwrócenie wyniku
	End:
	if(Result) {
		Parse_Debug(Result, OrgArgument);
	}
	return Result;
}


// Parsowanie liczby dziesiêtnej 32-bitowej ze znakiem
// - Argument	- WskaŸnik do argumentu, który ma byæ przetworzony
// - Output		- WskaŸnik do zmiennej, w której bêdzie zwrócony wynik
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
	
	// Czy znak minus na pocz¹tku
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
	
	// Wyœwietlenie informacji o ewentualnym b³êdzie i zwrócenie wyniku
	End:
	if(Result) {
		Parse_Debug(Result, OrgArgument);
	}
	return Result;
}

// Konwertowanie stringu znaków ASCII HEX na dane zapisane binarnie. W rezultacie wynikowy string jest 2x krótszy od
// stringu wejœciowego (jeœli by³y w nim spacje to dodatowo zosta³y wyciête). Wszystkie nadmiarowe znaki zostaj¹ zast¹pione zerami,
// aby mo¿na by³o wykorzystaæ miejsce w pamiêci, które jest dotychczas zajmowane przez string wejœciowy.
// - String		- wejœcie i wyjœcie
// - MaxLength	- maksymalna dopuszczalna d³ogoœæ stringu po przetworzeniu, domyœlnie 255 znaków
// - MinLength	- minimalna dopuszczalna d³ugoœæ stringu po przetworzeniu, domyœ³nie 0 znaków
Parse_t Parse_HexString(const uint8_t * InputString, uint8_t * OutputString, uint8_t * OutputLength, const uint8_t MaxLength, const uint8_t MinLength) {
	
	// WskaŸniki aktualnie przetwarzanych znaków
	const uint8_t * OrgArgument = InputString;
	uint8_t NibbleH;
	uint8_t NibbleL;
	*OutputLength = 0;
	Parse_t Result;
	
	// przetwarzanie a¿ do napotkania znaku 0
	while(*InputString != 0) {
		
		// Kontrola przepe³nienia
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
		
		// Przetwarzanie m³odszego nibble
		Result = Parse_HexChar(InputString++, &NibbleL);
		if(Result) {
			goto End;
		}
		
		// Sklejanie wyniku
		*OutputString++ = NibbleH << 4 | NibbleL;
		
		// Licznie znaków w stringu wynikowym
		(*OutputLength)++;
	}
	
	// Kontrola d³ugoœci
	if(*OutputLength < MinLength) {
		Result = Parse_Underflow;
	}
	
	// Wyœwietlenie informacji o ewentualnym b³êdzie i zwrócenie wyniku
	End:
	if(Result) {
		Parse_Debug(Result, OrgArgument);
	}
	return Result;
}


// Parsowanie stringu ASCII
Parse_t Parse_AsciiString(const uint8_t * InputString, uint8_t * OutputString, uint8_t * OutputLength, const uint8_t MaxLength, const uint8_t MinLength) {
	
	// WskaŸniki aktualnie przetwarzanych znaków
	const uint8_t * OrgArgument = InputString;
	*OutputLength = 0;
	Parse_t Result = Parse_OK;
	
	// przetwarzanie a¿ do napotkania znaku 0
	while(*InputString != 0) {
		
		// Kontrola przepe³nienia
		if(*OutputLength == MaxLength) {
			Result = Parse_Overflow;
			goto End;
		}
		
		// Kopiowanie znaku
		*OutputString++ = *InputString++;
		
		// Licznie znaków w stringu wynikowym
		(*OutputLength)++;
	}
	
	// Kontrola d³ugoœci
	if(*OutputLength < MinLength) {
		Result = Parse_Underflow;
	}
	
	// Wyœwietlenie informacji o ewentualnym b³êdzie i zwrócenie wyniku
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
