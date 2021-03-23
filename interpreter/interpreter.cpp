// Wersja 0.01

#if C_INTERPRETER

#include "interpreter.h"

// Command list
#include "interpreter_commands.h"

Interpreter_Struct Inter;


// Initialization
void Interpreter_Init(void) {
	TaskAdd(Interpreter_Task, 0);
}


// Por�wnuje badany string do wzorcowego a� do:
// - napotkania NULL w obu stringach
// - pierwszego r�nego znaku w obu stringach
// Tak skonstrukowana funkcja zajmuje mniej miejsca ni� strcmp() z biblioteki string.h
static inline bool Interpreter_StrCmp(const char *String1, const char *String2) {
	while(1) {
		if((*String1 == 0) && (*String2 == 0)) return true;		// Doszli�my do ko�ca obu string�w, czyli s� sobie r�wne
		if(*String1++ != *String2++) return false;				// Przy pierwszej napotkanej r�nicy zwr�� fa�sz
	}
}


// Pobieranie jednego znaku z UART i kopiowanie do bufora lub wykonywanie akcji
// - Interpreter_Struct * ConsoleInstance					-	Wska�nik do struktry konsoli
Interpreter_Res_t Interpreter_UartInput(void) {
	
	uint8_t ReceivedChar = Uart_Read();
	
	// Znaki printable dodajemy do bufora
	if(ReceivedChar >= ' ' && ReceivedChar <= '~') {
		
		// Sprawdzenie czy jest wolne miejsce w buforze
		if(Inter.ReceivedCnt >= INTERPRETER_COMMAND_LENGTH) {
			return Interpreter_BufferFull;
		}
		else {
			// Dodawanie znak�w do bufora 
			Inter.Buffer[Inter.ReceivedCnt++] = ReceivedChar;
			return Interpreter_OK;
		}
	}
	
	// Interpretowanie znak�w kontrolnych dla HMI
	switch(ReceivedChar) {
		
		// Enter
		case CR:
			// Zwracanie Interpreter_OK tylko je�eli co� mamy w buforze, je�li bufor jest pusty to brak reakcji
			if(Inter.ReceivedCnt) {
				return Interpreter_ReceivedCommand;	
			}
			break;
		
		// Backspace
		case BACKSPACE1:
		case BACKSPACE2:
			if(Inter.ReceivedCnt) {
				Inter.ReceivedCnt--;
				Inter.Buffer[Inter.ReceivedCnt] = 0;
			}
			break;
		
		// Przywr�cenie ostatnio wpisywanego polecenia
		// !! niech to b�dzie opcjonalne
		case CTRL_Z:	
			// Kasowanie dotychczas wpisanego polecenia
			while(Inter.ReceivedCnt) {
				Inter.ReceivedCnt--;
				Inter.Buffer[Inter.ReceivedCnt] = 0;
				Print(BACKSPACE1); 
			}
			
			// Kopiowanie bufora poprzedniego polecanie do bufora aktywnego polecenia
			memcpy(Inter.Buffer, Inter.Buffer2, INTERPRETER_COMMAND_LENGTH);
			Inter.ReceivedCnt = strlen((const char *)Inter.Buffer);
			
			// Wy�wietlenie zawarto�ci bufora tylko dla cz�owieka
			Print((const char *)Inter.Buffer);
			break;
		
		// ESCAPE - to samo, ale wprowadzone z klawiatury przez u�ytkownika
		case ESC:
			Inter.ReceivedCnt = 0;
			memset(Inter.Buffer, 0, INTERPRETER_COMMAND_LENGTH);
			return Interpreter_InputCancelled;
			break;
		
		// Wszystkie inne znaki ignorujemy - w tym NUL i LF
		default:
			
			break;
	}
	
	return Interpreter_OK;
}


// Dzielenie wej�ciowego stringu z wierza polece� na pojedyncze argumenty
// - argc												-	Wska�nik, przez kt�ry zwracana jest liczba znalezionych argument�w
// - argv												-	Wska�nik do tablicy wska�nik�w, w kt�rej zapisywane s� wska�niki do kolejnych argument�w
static inline Interpreter_Res_t Interpreter_SplitArguments(uint8_t * argc, uint8_t * argv[]) {
	
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
						if(ArgCount == INTERPRETER_MAX_ARGUMENTS) {				// Przekroczenie dopuszczalnej liczby argument�w
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
					if(ArgCount == INTERPRETER_MAX_ARGUMENTS) {
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
	
	return Interpreter_OK;
}


// Wyszukiwanie funkcji dla wpisanego polecenia
// Nazwa polecenia jest przechowywana w argumencie zerowym argv[0]
// Funkcja zwraca wska�nik do funkcji typu void pobieraj�cej argumenty uint8_t argc, uint8_t * argv[]
// Argumentem przyjmowanym przez Interpreter_FindCommand() jest wska�nik do stringu EnteredName zawieraj�cego polecenie wpisane przez u�ytkownika
// Je�eli Interpreter_FindCommand nie znajdzie funkcji odpowiadaj�cej poleceniu to zwraca wska�nik NULL
static inline void (*Interpreter_FindPointer(uint8_t * EnteredName))(uint8_t argc, uint8_t * argv[]) {
	
	for(uint8_t i=0; i<(sizeof(Interpreter_CommandList)/sizeof(Interpreter_NamePointer_t)); i++) {
		if(Interpreter_StrCmp((const char *)EnteredName, Interpreter_CommandList[i].Name)) {
			return Interpreter_CommandList[i].Pointer;
		}
	}
	return NULL;
}


// Funkcja wywo�ywana z tasku obs�uguj�cego konsol�
void Interpreter_TaskHandler(void) {
	
	// Pobieranie danych z UART
	while(Uart_ReceivedCnt(&INTERPRETER_UART_INSTANCE)) {
		
		// Przekazywanie znak�w z bufora UART do bufora konsoli i podejmywanie dalszych dzia�a w zale�no�ci od Interpreter_Result
		Interpreter_Res_t Interpreter_Result;
		Interpreter_Result =  Interpreter_UartInput();
		
		// Je�eli zako�czono odbieranie polecenia
		if(Interpreter_Result == Interpreter_ReceivedCommand) {
			
			// !! wyrzuci� to
			//_delay_us(250);
			
			// Zmienne
			uint8_t			argc = 0;												// Liczba wpisanych argument�w
			uint8_t *		argv[INTERPRETER_MAX_ARGUMENTS];								// Tablica wska�nik�w do argument�w
			//void			(*CommandPointer)(uint8_t argc, uint8_t * argv[]);		// Wska�nik do funkcji, kt�ra ma by� wywo�ana
			memset(argv, 0, sizeof(argv));

			// Kopiowanie do bufora CTRL-Z
			memcpy(Inter.Buffer2, Inter.Buffer, INTERPRETER_COMMAND_LENGTH);

			// Dzielenie bufora na poszczeg�lne argumenty
			Interpreter_SplitArguments(&argc, argv);

			// Wyszukiwanie wska�nika 
			void (*CommandPointer)(uint8_t argc, uint8_t * argv[]) = Interpreter_FindPointer(argv[0]);

			// Zej�cie do nowej linii, �eby w trybie r�cznym �adnie wygl�da�o w terminalu
			Print_NL();

			// Ustawienie portu UART, kt�ry ma otrzyma� odpowied�
			//UART_PortOverride = Inter.UartInstance;

			// Wykonanie polecenia, je�li rozpoznano
			if(CommandPointer) {
				
				// Prolog odpowiedzi
				Uart_TxBufferFlush(&INTERPRETER_UART_INSTANCE);
				
				
				// Wywo�anie funkcji odpowiadaj�cej poleceniu
				CommandPointer(argc, argv);
				
			}
			
			// Je�eli nie rozpoznano polecenia
			else {
				Print("Bad command");
			}
			
			// Czyszczenie aktualnego bufora wiersza polece�
			memset(Inter.Buffer, 0, INTERPRETER_COMMAND_LENGTH);
			Inter.ReceivedCnt = 0;
			
			// Prompt by zasygnalizowa� gotowo�� do przyj�cia kolejnego polecenia
			Interpreter_PromptShow();
		}
		
		// Wci�ni�to ESCAPE
		else if(Interpreter_Result == Interpreter_InputCancelled) {
			Interpreter_PromptShow();
		}
	}
}


// System task to periodicaly execute interpreter routine
task_t Interpreter_Task(runmode_t RunMode) {
	
	// Normaln execution
	if(RunMode == Run) {
		Interpreter_TaskHandler();
	}
	
	// Constructor
	else if(RunMode == FirstRun) {
		Interpreter_PromptShow();						// !! zrobi� co�, �eby prompt nie pokazywa� si� w trakcie wysy�ania komunikatu o utworzeniu tasku
	}
	
	// Destructor
	else if(RunMode == Close) {
	}
	
	// Identification
	#if OS_USE_TASK_IDENTIFY
	else if(RunMode == Identify) {
		Print("Interpreter");
	}
	#endif
	
	return TaskOK;
}


// Display command line prompt
void Interpreter_PromptShow(void) {
	Print("\r\n > ");
}


//
//
//

// Clean all buffers
void Interpreter_BufferFlush(void) {
	memset(&Inter, 0, sizeof(Inter));
};


// ==================
// Parsery argument�w
// ==================


// Debugowanie b��d�w
void Console_Debug(const Interpreter_Res_t Result, const uint8_t * Argument) {
	Print("Error");
	if(Argument != NULL) {
		Print(" in agument ");
		Print((const char *)Argument);
	}
	Print(": ");

	switch(Result) {
		case Interpreter_OK:									Print("OK");								break;
		case Interpreter_NotReady:								Print("Not ready");						break;
		case Interpreter_UnknownCommand:						Print("Unknown command");					break;
		case Interpreter_NoInput:								Print("No input");							break;
		case Interpreter_Overflow:								Print("Overflow");							break;
		case Interpreter_MissingArgument:						Print("Missing arg");						break;
		case Interpreter_Underflow:								Print("Underflow");						break;
		case Interpreter_ParseError:							Print("Parse error");						break;
		case Interpreter_ExpectedHex:							Print("Expected Hex");						break;
		case Interpreter_ExpectedDec:							Print("Expected Dec");						break;
		case Interpreter_ReceivedACK:							Print("Received ACK");						break;
		case Interpreter_ReceivedNAK:							Print("Received NAK");						break;
	}
}



// Funkcja przekszta�ca znak ASCII HEX na warto�� binarn�
// - InputChar	- Wska�nik do badanego znaku
// - OutputChar	- Wska�nik do zmiennej, w kt�rej ma by� zapisany nibble
static Interpreter_Res_t Parse_HexChar(const uint8_t * InputChar, uint8_t * OutputChar) {
	if(*InputChar >= '0' && *InputChar <= '9') {
		*OutputChar = *InputChar - '0';
		return Interpreter_OK;
	}
	else if(*InputChar >= 'A' && *InputChar <= 'F') {
		*OutputChar = *InputChar - 55;
		return Interpreter_OK;
	}
	else if(*InputChar >= 'a' && *InputChar <= 'f') {
		*OutputChar = *InputChar - 87;
		return Interpreter_OK; 
	}
	else {
		return Interpreter_ExpectedHex;
	}
}



static Interpreter_Res_t Parse_HexChar_new(const uint8_t * InputChar, uint8_t * OutputChar, bool HighNibble) {
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
		return Interpreter_ExpectedHex;
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
	
	return Interpreter_OK; 
}


// Przetwarzanie stringu od ko�ca, a output od pocz�tku
// Zmienna wskazywana przez *Output musi by� wyzerowana, inaczej b�dzie b��d losowo zainicjalizowanej pami�ci
Interpreter_Res_t Parse_HexNum(const uint8_t * Argument, void * Output, uint8_t Characters) {
	
	Interpreter_Res_t Result;
	const uint8_t * OrgArgument = Argument;
	
	// Kontrola czy podano argument
	if(Argument == NULL) {
		Result = Interpreter_MissingArgument;
		goto End;
	}
	
	// Przesuni�cie wska�nika na koniec ci�gu znak�w argumentu
	Argument = Argument + Characters;
	
	// Sprawdzanie czy ostatni bajt argumentu to 0, je�eli nie to znaczy, �e przes�ano wi�cej znak� ni� jest potrzebne dla konkretnego typu zmiennej
	if(*Argument != 0) {
		Result = Interpreter_Overflow;
		goto End;
	}
	
	// Przetwarzanie wszystkich znak�w ASCII od ko�ca
	do {
		
		uint8_t HighNibble = Characters & 0x01;
		Result = Parse_HexChar_new(--Argument, (uint8_t*)Output, HighNibble);
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
		Console_Debug(Result, OrgArgument);
	}
	return Result;
}


// Parsowanie liczby HEX 8-bitowej
// - Argument	- Wska�nik do argumentu, kt�ry ma by� przetworzony
// - Output		- Wska�nik do zmiennej, w kt�rej b�dzie zwr�cony wynik
Interpreter_Res_t Parse_Hex8(const uint8_t * Argument, uint8_t * Output) {
	*Output = 0;
	return Parse_HexNum(Argument, Output, 2);
}


// Parsowanie liczby HEX 16-bitowej
// - Argument	- Wska�nik do argumentu, kt�ry ma by� przetworzony
// - Output		- Wska�nik do zmiennej, w kt�rej b�dzie zwr�cony wynik
Interpreter_Res_t Parse_Hex16(const uint8_t * Argument, uint16_t * Output) {
	*Output = 0;
	return Parse_HexNum(Argument, Output, 4);
}


// Parsowanie liczby HEX 32-bitowej
// - Argument	- Wska�nik do argumentu, kt�ry ma by� przetworzony
// - Output		- Wska�nik do zmiennej, w kt�rej b�dzie zwr�cony wynik
Interpreter_Res_t Parse_Hex32(const uint8_t * Argument, uint32_t * Output) {
	*Output = 0;
	return Parse_HexNum(Argument, Output, 8);
}


// Parsowanie liczby HEX 64-bitowej
// - Argument	- Wska�nik do argumentu, kt�ry ma by� przetworzony
// - Output		- Wska�nik do zmiennej, w kt�rej b�dzie zwr�cony wynik
Interpreter_Res_t Parse_Hex64(const uint8_t * Argument, uint64_t * Output) {
	*Output = 0;
	return Parse_HexNum(Argument, Output, 16);
}


// Konwertowanie stringu znak�w ASCII HEX na dane zapisane binarnie. W rezultacie wynikowy string jest 2x kr�tszy od
// stringu wej�ciowego (je�li by�y w nim spacje to dodatowo zosta�y wyci�te). Wszystkie nadmiarowe znaki zostaj� zast�pione zerami,
// aby mo�na by�o wykorzysta� miejsce w pami�ci, kt�re jest dotychczas zajmowane przez string wej�ciowy.
// - String		- wej�cie i wyj�cie
// - MaxLength	- maksymalna dopuszczalna d�ogo�� stringu po przetworzeniu, domy�lnie 255 znak�w
// - MinLength	- minimalna dopuszczalna d�ugo�� stringu po przetworzeniu, domy��nie 0 znak�w
Interpreter_Res_t Parse_HexString(const uint8_t * InputString, uint8_t * OutputString, uint8_t * OutputLength, const uint8_t MaxLength, const uint8_t MinLength) {
	
	// Wska�niki aktualnie przetwarzanych znak�w
	const uint8_t * OrgArgument = InputString;
	uint8_t NibbleH;
	uint8_t NibbleL;
	*OutputLength = 0;
	Interpreter_Res_t Result;

	// przetwarzanie a� do napotkania znaku 0
	while(*InputString != 0) {
		
		// Kontrola przepe�nienia
		if(*OutputLength == MaxLength) {
			Result = Interpreter_Overflow;
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
		Result = Interpreter_Underflow;
	}
	
	// Wy�wietlenie informacji o ewentualnym b��dzie i zwr�cenie wyniku
	End:
	if(Result) {
		Console_Debug(Result, OrgArgument);
	}
	return Result;
}


// Parsowanie stringu ASCII
Interpreter_Res_t Parse_AsciiString(const uint8_t * InputString, uint8_t * OutputString, uint8_t * OutputLength, const uint8_t MaxLength, const uint8_t MinLength) {
	
	// Wska�niki aktualnie przetwarzanych znak�w
	const uint8_t * OrgArgument = InputString;
	*OutputLength = 0;
	Interpreter_Res_t Result = Interpreter_OK;

	// przetwarzanie a� do napotkania znaku 0
	while(*InputString != 0) {
		
		// Kontrola przepe�nienia
		if(*OutputLength == MaxLength) {
			Result = Interpreter_Overflow;
			goto End;
		}
		
		// Kopiowanie znaku
		*OutputString++ = *InputString++;

		// Licznie znak�w w stringu wynikowym
		(*OutputLength)++;
	}

	// Kontrola d�ugo�ci
	if(*OutputLength < MinLength) {
		Result = Interpreter_Underflow;
	}
	
	// Wy�wietlenie informacji o ewentualnym b��dzie i zwr�cenie wyniku
	End:
	if(Result) {
		Console_Debug(Result, OrgArgument);
	}
	return Result;
}


// Parsowanie liczby dziesi�tnej 8-bitowej
// Funkcja przekszta�ca znak ASCII HEX na warto�� binarn�
// - InputChar	- Wska�nik do badanego znaku
// - OutputChar	- Wska�nik do zmiennej, w kt�rej ma by� zapisany nibble
static Interpreter_Res_t Parse_DecChar(const uint8_t * InputChar, uint8_t * OutputChar) {
	if(*InputChar >= '0' && *InputChar <= '9') {
		*OutputChar = *InputChar - '0';
		return Interpreter_OK;
	}
	else {
		return Interpreter_ExpectedDec;
	}
}


// Parsowanie liczby dziesi�tnej 8-bitowej
// - Argument	- Wska�nik do argumentu, kt�ry ma by� przetworzony
// - Output		- Wska�nik do zmiennej, w kt�rej b�dzie zwr�cony wynik
Interpreter_Res_t Parse_Dec8(const uint8_t * Argument, uint8_t * Output, const uint8_t MaxValue) {
	
	const uint8_t * OrgArgument = Argument;
	uint8_t Digit; 	
	uint8_t Temp = 0;
	uint8_t Temp2;
	Interpreter_Res_t Result;

	// Kontrola czy podano argument
	if(Argument == NULL) {
		Result = Interpreter_MissingArgument;
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
			Result = Interpreter_Overflow;
			goto End;
			//return Interpreter_Overflow;
		}
	} 

	// Zwracanie wyniku
	if(Temp <= MaxValue) {
		*Output = Temp;
	}
	else {
		Result = Interpreter_Overflow;
	}
	
	// Wy�wietlenie informacji o ewentualnym b��dzie i zwr�cenie wyniku
	End:
	if(Result) {
		Console_Debug(Result, OrgArgument);
	}
	return Result;
}


// Parsowanie liczby dziesi�tnej 16-bitowej
// - Argument	- Wska�nik do argumentu, kt�ry ma by� przetworzony
// - Output		- Wska�nik do zmiennej, w kt�rej b�dzie zwr�cony wynik
Interpreter_Res_t Parse_Dec16(const uint8_t * Argument, uint16_t * Output, const uint16_t MaxValue) {
	
	const uint8_t * OrgArgument = Argument;
	uint8_t Digit; 	
	uint16_t Temp = 0;
	uint16_t Temp2;
	Interpreter_Res_t Result;

	// Kontrola czy podano argument
	if(Argument == NULL) {
		Result = Interpreter_MissingArgument;
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
			Result = Interpreter_Overflow;
			goto End;
			//return Interpreter_Overflow;
		}
	} 

	// Zwracanie wyniku
	if(Temp <= MaxValue) {
		*Output = Temp;
	}
	else {
		Result = Interpreter_Overflow;
	}
	
	// Wy�wietlenie informacji o ewentualnym b��dzie i zwr�cenie wyniku
	End:
	if(Result) {
		Console_Debug(Result, OrgArgument);
	}
	return Result;
}


// Parsowanie liczby dziesi�tnej 32-bitowej
// - Argument	- Wska�nik do argumentu, kt�ry ma by� przetworzony
// - Output		- Wska�nik do zmiennej, w kt�rej b�dzie zwr�cony wynik
Interpreter_Res_t Parse_Dec32(const uint8_t * Argument, uint32_t * Output, const uint32_t MaxValue) {
	
	const uint8_t * OrgArgument = Argument;
	uint8_t Digit; 	
	uint32_t Temp = 0;
	uint32_t Temp2;
	Interpreter_Res_t Result;

	// Kontrola czy podano argument
	if(Argument == NULL) {
		Result = Interpreter_MissingArgument;
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
			Result = Interpreter_Overflow;
			goto End;
		}
	} 

	// Zwracanie wyniku
	if(Temp <= MaxValue) {
		*Output = Temp;
	}
	else {
		Result = Interpreter_Overflow;
	}
	
	// Wy�wietlenie informacji o ewentualnym b��dzie i zwr�cenie wyniku
	End:
	if(Result) {
		Console_Debug(Result, OrgArgument);
	}
	return Result;
}


// Parsowanie liczby dziesi�tnej 64-bitowej
// - Argument	- Wska�nik do argumentu, kt�ry ma by� przetworzony
// - Output		- Wska�nik do zmiennej, w kt�rej b�dzie zwr�cony wynik
Interpreter_Res_t Parse_Dec64(const uint8_t * Argument, uint64_t * Output, const uint64_t MaxValue) {
	
	const uint8_t * OrgArgument = Argument;
	uint8_t Digit; 	
	uint64_t Temp = 0;
	uint64_t Temp2;
	Interpreter_Res_t Result;

	// Kontrola czy podano argument
	if(Argument == NULL) {
		Result = Interpreter_MissingArgument;
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
			Result = Interpreter_Overflow;
			goto End;
		}
	} 

	// Zwracanie wyniku
	if(Temp <= MaxValue) {
		*Output = Temp;
	}
	else {
		Result = Interpreter_Overflow;
	}
	
	// Wy�wietlenie informacji o ewentualnym b��dzie i zwr�cenie wyniku
	End:
	if(Result) {
		Console_Debug(Result, OrgArgument);
	}
	return Result;
}


// Parsowanie liczby dziesi�tnej 32-bitowej ze znakiem
// - Argument	- Wska�nik do argumentu, kt�ry ma by� przetworzony
// - Output		- Wska�nik do zmiennej, w kt�rej b�dzie zwr�cony wynik
Interpreter_Res_t Parse_Dec32S(const uint8_t * Argument, int32_t * Output) {
	
	const uint8_t * OrgArgument = Argument;
	uint8_t Digit; 	
	int32_t Temp = 0;
	int32_t Temp2;
	Interpreter_Res_t Result;
	bool Negative = false;

	// Kontrola czy podano argument
	if(Argument == NULL) {
		Result = Interpreter_MissingArgument;
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
			Result = Interpreter_Overflow;
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
		Console_Debug(Result, OrgArgument);
	}
	return Result;
}


#endif
