// Wersja 0.22

#if C_CONSOLE

#include "console.h"

// Tablica polece� 
#include "console_commands.h"


// Funkcje static
static inline CmdRes_t Console_SplitArguments(Console_Struct * ConsoleInstance, uint8_t * argc, uint8_t * argv[]);
static inline bool Console_StrCmp(const char *String1, const char *String2);
static inline void (*Console_FindPointer(uint8_t * EnteredName))(uint8_t argc, uint8_t * argv[]);
static inline bool Console_StrCmp(const char *String1, const char *String2);

// Konstruktor
Console_Struct::Console_Struct(USART_t * UartInstance, uint8_t Flags) {
	memset(this, 0, sizeof(Console_Struct));
	this->UartInstance	=	UartInstance;
	this->Flags			=	Flags;
};


// Funkcja wywo�ywana z tasku obs�uguj�cego konsol�
// - Console_Struct * ConsoleInstance		-	Wska�nik do struktry konsoli
void Console_TaskHandler(Console_Struct * ConsoleInstance) {
	
	// Pobieranie danych z UART
	while(Uart_ReceivedCnt(ConsoleInstance->UartInstance)) {
		
		// Przekazywanie znak�w z bufora UART do bufora konsoli i podejmywanie dalszych dzia�a w zale�no�ci od Console_Result
		Console_Res_t Console_Result;
		Console_Result =  Console_UartInput(ConsoleInstance);
		
		// Je�eli zako�czono odbieranie polecenia
		if(Console_Result == Console_ReceivedCommand) {
			
			// !! wyrzuci� to
			//_delay_us(250);
			
			// Zmienne
			uint8_t			argc = 0;												// Liczba wpisanych argument�w
			uint8_t *		argv[CMD_MAX_ARGUMENTS];								// Tablica wska�nik�w do argument�w
			//void			(*CommandPointer)(uint8_t argc, uint8_t * argv[]);		// Wska�nik do funkcji, kt�ra ma by� wywo�ana
			memset(argv, 0, sizeof(argv));

			// Kopiowanie do bufora CTRL-Z
			memcpy(ConsoleInstance->Buffer2, ConsoleInstance->Buffer, CMD_LINE_BUFFER_LENGTH);

			// Dzielenie bufora na poszczeg�lne argumenty
			Console_SplitArguments(ConsoleInstance, &argc, argv);

			// Wyszukiwanie wska�nika 
			void (*CommandPointer)(uint8_t argc, uint8_t * argv[]) = Console_FindPointer(argv[0]);

			// Zej�cie do nowej linii, �eby w trybie r�cznym �adnie wygl�da�o w terminalu
			if(ConsoleInstance->Flags & FLAGS_USE_HMI) {
				Uart_WriteNL(ConsoleInstance->UartInstance);
			}

			// Ustawienie portu UART, kt�ry ma otrzyma� odpowied�
			UART_PortOverride = ConsoleInstance->UartInstance;

			// Wykonanie polecenia, je�li rozpoznano
			if(CommandPointer) {
				
				// Prolog odpowiedzi
				Uart_TxBufferFlush(ConsoleInstance->UartInstance);
				Uart_Write(ACK, ConsoleInstance->UartInstance);
				//Uart_TxCrcClear(ConsoleInstance->UartInstance);
				//_delay_us(3);
				
				
				//_delay_us(5);
				
				// Wywo�anie funkcji odpowiadaj�cej poleceniu
				CommandPointer(argc, argv);
				
				// Epilog odpowiedzi	
				if(ConsoleInstance->Flags & FLAGS_M2M_CMD) {		
					//uint16_t CRC = Uart_TxCrcGet(ConsoleInstance->UartInstance);
					Uart_Write(US, ConsoleInstance->UartInstance);
					//Uart_Write(uint8_t(CRC >> 8), ConsoleInstance->UartInstance);
					//Uart_Write(uint8_t(CRC & 0x00FF), ConsoleInstance->UartInstance);
					Uart_Write(ConsoleInstance->Token, ConsoleInstance->UartInstance);
				}
				
				if(ConsoleInstance->Flags & FLAGS_USE_HMI) {
					Uart_Write(ETX, ConsoleInstance->UartInstance);	
				}
				
				// Czekanie na zako�czenie wysy�ania polecenia
				// !! to raczej nie jest potrzebne
				Uart_WaitForTxComplete(ConsoleInstance->UartInstance);
			}
			
			// Je�eli nie rozpoznano polecenia
			else {
				#if REMOTE_DEBUG
// 					Uart_Write("[Console ");
// 					Uart_WriteHex((uint16_t)ConsoleInstance);
// 					Uart_Write(" BadCom=");
// 					for(uint8_t i=0; i<CMD_LINE_BUFFER_LENGTH; i++) {
// 						Uart_Write(ConsoleInstance->Buffer[i]);
// 					}
//					ERROR_ON;
				#endif
				
				if(ConsoleInstance->Flags & FLAGS_USE_HMI) {
					//ERROR_ON;
					Uart_Write(NAK, ConsoleInstance->UartInstance);
					Uart_Write("Bad command", ConsoleInstance->UartInstance);
					Uart_Write(ETX, ConsoleInstance->UartInstance);		
				
					// !! Debug
					Uart_WaitForTxComplete(ConsoleInstance->UartInstance);
				}
				
				#if REMOTE_DEBUG
					//ERROR_ON;
					UART_PortOverride = NULL;
					Uart_Write("\r\n[Bad command:", &UART_DEFAULT_PORT);
					for(uint8_t i=0; i<CMD_LINE_BUFFER_LENGTH; i++) {
						Uart_Write(ConsoleInstance->Buffer[i]);
					}
					Uart_Write(']');
					Uart_WaitForTxComplete(&UART_DEFAULT_PORT);
					
				#endif
				
			}
			
			// Czyszczenie bufora odbiorczego
			// !! Kasowanie kolejnych polece�, kt�re mog�y zosta� odebrane podczas wykonywania poprzedniego polecenia
			Uart_RxBufferFlush(ConsoleInstance->UartInstance);

			// Przywr�cenie domy�lnego portu UART
			UART_PortOverride = NULL;

			// Czyszczenie aktualnego bufora wiersza polece�
			memset(ConsoleInstance->Buffer, 0, CMD_LINE_BUFFER_LENGTH);
			ConsoleInstance->ReceivedCnt = 0;

			// Prompt by zasygnalizowa� gotowo�� do przyj�cia kolejnego polecenia
			if(ConsoleInstance->Flags & FLAGS_USE_HMI) {
				Console_PromptShow(ConsoleInstance);
			}
			
			// Czyszczenie wszystkich flag, pozostawiaj�c flagi HMI i M2M takie jak by�y wcze�niej
			ConsoleInstance->Flags = ConsoleInstance->Flags & (FLAGS_USE_HMI | FLAGS_USE_M2M);
		}

		// Wci�ni�to ESCAPE
		else if(Console_Result == Console_InputCancelled) {
			//Uart_Write("[Console ");
			//Uart_WriteHex((uint16_t)ConsoleInstance);
			//Uart_Write(" CANCELED] ");
			//PF2_ON;
			Console_PromptShow(ConsoleInstance);
			
			// Czyszczenie wszystkich flag, pozostawiaj�c flagi HMI i M2M takie jak by�y wcze�niej
			ConsoleInstance->Flags = ConsoleInstance->Flags & (FLAGS_USE_HMI | FLAGS_USE_M2M);
		}
	}

}


// Pobieranie jednego znaku z UART i kopiowanie do bufora lub wykonywanie akcji
// - Console_Struct * ConsoleInstance					-	Wska�nik do struktry konsoli
Console_Res_t Console_UartInput(Console_Struct * ConsoleInstance) {
	
	uint8_t ReceivedChar = Uart_Read(ConsoleInstance->UartInstance);
	static uint8_t TestMode = 0;
	
// 	UART_PortOverride = &UART_DEFAULT_PORT;
// 	Uart_WriteHex(ReceivedChar, ' ', ConsoleInstance->UartInstance);
// 	Uart_Write(ReceivedChar, ConsoleInstance->UartInstance);
// 	Uart_WaitForTxComplete(&UART_DEFAULT_PORT);
// 	UART_PortOverride = NULL;
	
	// Je�eli mamy trub M2M i wcze�niej odebrali�my US
	if(ConsoleInstance->Flags & FLAGS_NEXT_BYTE_CRCH) {
		ConsoleInstance->CRCH	=	ReceivedChar;
		ConsoleInstance->Flags	&= ~FLAGS_NEXT_BYTE_CRCH;
		ConsoleInstance->Flags	|=	FLAGS_NEXT_BYTE_CRCL;
		return Console_OK;
	}
	
	// Je�eli mamy tryb M2M i wcze�niej odebrali�my CRCH
	if(ConsoleInstance->Flags & FLAGS_NEXT_BYTE_CRCL) {
		
		// Kasowanie flagi
		ConsoleInstance->Flags &=  ~FLAGS_NEXT_BYTE_CRCL;
		ConsoleInstance->Flags |=	FLAGS_NEXT_BYTE_TOKEN;
		
		uint16_t ReceivedCRC = uint16_t(ConsoleInstance->CRCH) << 8 | ReceivedChar;
		//uint16_t CalculatedCRC = Remote_CRC(ConsoleInstance->Buffer, ConsoleInstance->ReceivedCnt);
		
		// TODO: oryginalnie odkomentowane, dodac jaki� #if
		//uint16_t CalculatedCRC = Remote_CRC(ConsoleInstance->Buffer);
		
		ReceivedCRC = ReceivedCRC + TestMode;
		if(TestMode) {
			TestMode--;
		}
		
// 		Uart_Write("[Cmd_CRC_");
// 		Uart_WriteHex(ReceivedCRC);
// 		Uart_Write(',');
// 		Uart_WriteHex(CalculatedCRC);
// 		Uart_Write("] ");
		
		
		
		
		// Zapisywanie wyniku weryfikacji
		/*
		if(ReceivedCRC == CalculatedCRC) {
// 			#if REMOTE_DEBUG
// 				Uart_Write("[Cmd_CRC_OK] ");
// 			#endif
//			ConsoleInstance->M2M |=	FLAGS_CRC_CORRECT;

//			ConsoleInstance->Flags |= FLAGS_NEXT_BYTE_TOKEN;
			
			// Sprawdzenie czy to duplikat polecenia - otrzymano polecenie z DC2, ale wcze�niej podano odpowied�
// 			if(ConsoleInstance->Flags & FLAGS_CMD_RETRY) {
// 				if(Console_StrCmp((const char *)ConsoleInstance->Buffer, (const char *)ConsoleInstance->Buffer2)) {
// 					Uart_Write("[Duplicate_CMD] ");
// 					
// 					// Czyszczenie bufora
// 					ConsoleInstance->ReceivedCnt = 0;
// 					ConsoleInstance->ControlUse = false;
// 					ConsoleInstance->CRCH = 0;
// 					ConsoleInstance->Flags = ConsoleInstance->Flags & (FLAGS_USE_HMI | FLAGS_USE_M2M);
// 					memset(ConsoleInstance->Buffer, 0, CMD_LINE_BUFFER_LENGTH);
// 					
// 					return Console_OK;
// 				}
// 			}
			
			// Poprawna weryfikacja - mo�na wykona� polecenie
			//return Console_ReceivedCommand;
		}
		else {
			#if REMOTE_DEBUG
// 				Uart_Write("\r\n[Cmd_CRC_ERROR_");
// 				Uart_WriteHex(ReceivedChar);
// 				Uart_Write(',');
// 				Uart_WriteHex(CalculatedCrc);
// 				Uart_Write(']');
			#endif
//			ConsoleInstance->M2M |=	FLAGS_CRC_INCORRECT;
			
			// CRC si� nie zgadza, odsy�amy NAK i czekamy na ponowne przes�anie polecenia
			// Czyszczenie bufora
// 			ConsoleInstance->ReceivedCnt = 0;
// 			ConsoleInstance->ControlUse = false;
// 			ConsoleInstance->CRCH = 0;
// 			ConsoleInstance->Flags = ConsoleInstance->Flags & (FLAGS_USE_HMI | FLAGS_USE_M2M);
// 			memset(ConsoleInstance->Buffer, 0, CMD_LINE_BUFFER_LENGTH);
// 			Uart_Write(NAK, ConsoleInstance->UartInstance);
			
			ConsoleInstance->Flags |= FLAGS_WRONG_CRC;
		}
		*/
		return Console_OK;
	}
	
	// Je�eli mamy tryb M2M i wcze�niej odebrali�my CRCH
	if(ConsoleInstance->Flags & FLAGS_NEXT_BYTE_TOKEN) {
		
		ConsoleInstance->Flags &= ~FLAGS_NEXT_BYTE_TOKEN;
		
		// Je�eli CRC nie by�o prawid�owe
		if(ConsoleInstance->Flags & FLAGS_WRONG_CRC) {
			
			// Token ignorujemy i od razu odsy�amy NAK
			ConsoleInstance->ReceivedCnt = 0;
			ConsoleInstance->ControlUse = false;
			ConsoleInstance->CRCH = 0;
			ConsoleInstance->Flags = ConsoleInstance->Flags & (FLAGS_USE_HMI | FLAGS_USE_M2M);
			memset(ConsoleInstance->Buffer, 0, CMD_LINE_BUFFER_LENGTH);
			Uart_Write(NAK, ConsoleInstance->UartInstance);
		}
		else {
			// CRC prawid�owe
			
			// Sprawdzamy czy polecenie jest inne ni� poprzednio odebrane
			if(Console_StrCmp((const char *)ConsoleInstance->Buffer, (const char *)ConsoleInstance->Buffer2)) {
				
				// Polecenie jest takie samo jak poprzednio odebrane, wi�c musimy jeszcze sprawdzi� czy token jest inny
				if(ConsoleInstance->Token == ReceivedChar) {
					// Token taki sam jak wcze�nie, a wi�c dostali�my duplikat
					
					Uart_Write("\r\n[Duplicate_CMD ");
					for(uint8_t i=0; i<16; i++) {
						Uart_Write(ConsoleInstance->Buffer[i]);
					}
					Uart_Write("] ");
					//ERROR_ON;
					
					// Ponowne wys�anie bufora
					//Uart_Resend(ConsoleInstance->UartInstance);
					
					// Czyszczenie bufora
// 					ConsoleInstance->ReceivedCnt = 0;
// 					ConsoleInstance->ControlUse = false;
// 					ConsoleInstance->CRCH = 0;
// 					ConsoleInstance->Flags = ConsoleInstance->Flags & (FLAGS_USE_HMI | FLAGS_USE_M2M);
// 					memset(ConsoleInstance->Buffer, 0, CMD_LINE_BUFFER_LENGTH);
					
					return Console_OK;
				}
			}
			
			// Mo�na przyst�pi� do wykonywania polecenia
			// Zapisanie tokena, aby odes�a� go wraz z odpowiedzi�
			ConsoleInstance->Token = ReceivedChar;
			
			// Poprawna weryfikacja - mo�na wykona� polecenie
			return Console_ReceivedCommand;
		}
	}

	
	// Znaki printable dodajemy do bufora
	if(ReceivedChar >= ' ' && ReceivedChar <= '~') {
		
		// Je�eli bufor jest pusty i otrzymujemy znaki spacja i > 
		// !! wywali� to, bo bez sensu
		if(ConsoleInstance->ReceivedCnt == 0) {
			if(ReceivedChar == ' ') return Console_OK;
			if(ReceivedChar == '>') return Console_OK;
		}
		
		// Sprawdzenie czy jest wolne miejsce w buforze
		if(ConsoleInstance->ReceivedCnt >= CMD_LINE_BUFFER_LENGTH) {
			
			// !! co robi�, kiedy nie ma miejsca w buforze?
			#if REMOTE_DEBUG
				//ERROR_ON;
				//Uart_Write('_');										// !! kt�ry uart?
				Uart_Write(ReceivedChar);
			#endif

			return Console_BufferFull;
		}
		else {
			// Dodawanie znak�wdo bufora 
			ConsoleInstance->Buffer[ConsoleInstance->ReceivedCnt++] = ReceivedChar;
			return Console_OK;
		}
	}
	
	// Interpretowanie znak�w kontrolnych dla M2M
	if(ConsoleInstance->Flags & FLAGS_USE_M2M) {
		
		switch(ReceivedChar) {
			
				// DC1 - pocz�tek polecenia w trybie M2M
			case DC1:
				ConsoleInstance->Flags	|=	FLAGS_M2M_CMD;
				if(ConsoleInstance->ReceivedCnt) {						// Czyszczenie bufora
					ConsoleInstance->ReceivedCnt = 0;
					ConsoleInstance->ControlUse = false;
					ConsoleInstance->CRCH = 0;
					memset(ConsoleInstance->Buffer, 0, CMD_LINE_BUFFER_LENGTH);
				}
				break;
			
		
			// DC2 - pocz�tek polecenia w trybie M2M, kt�re zosta�o przes�ane ponownie z powodu b��du
// 			case DC2:
// 				//ERROR_ON;
// 				ConsoleInstance->Flags	|=	FLAGS_M2M_RETRY;
// 				if(ConsoleInstance->ReceivedCnt) {						// Czyszczenie bufora
// 					ConsoleInstance->ReceivedCnt = 0;
// 					ConsoleInstance->ControlUse = false;
// 					ConsoleInstance->CRCH = 0;
// 					memset(ConsoleInstance->Buffer, 0, CMD_LINE_BUFFER_LENGTH);
// 				}
// 				break;
			

			// ��danie ponownego przes�ania odpowiedzi na poprzednie polecenie
			case DC3:
				Uart_Write("\r\n[Response DC3] ");
				//Uart_Resend(ConsoleInstance->UartInstance);
				break;
		
		
			// ENQ - zapytanie o prompt
			case ENQ:
				ConsoleInstance->ReceivedCnt = 0;
				ConsoleInstance->ControlUse = false;
				ConsoleInstance->CRCH = 0;
				memset(ConsoleInstance->Buffer, 0, CMD_LINE_BUFFER_LENGTH);
				Uart_Write(DC4, ConsoleInstance->UartInstance);
				break;
		
		
			// US - kolejny znak to CRC
			case US:
				ConsoleInstance->Flags	|=	FLAGS_NEXT_BYTE_CRCH;
				break;
				
				
			// ACK - otrzymano odpowied� na polecenie, najprawdopodobniej Remote wys�a� polecenie i wyst�pi� timeout, a dopiero teraz zdalna konsola przys�a�a odpowied�, ignorujemy ca�y bufor
			case ACK:
				_delay_ms(10);	// czas na ewentualne przes�anie reszty polecenia
				Uart_RxBufferFlush(ConsoleInstance->UartInstance);
				break;
			
				
		}
	}
	
	
	// Interpretowanie znak�w kontrolnych dla HMI
	if(ConsoleInstance->Flags & FLAGS_USE_HMI) {
		switch(ReceivedChar) {
		
			// Enter
			case CR:
				// Zwracanie Console_OK tylko je�eli co� mamy w buforze, je�li bufor jest pusty to brak reakcji
				if(ConsoleInstance->ReceivedCnt) {
					return Console_ReceivedCommand;	
				}
				break;

			case BACKSPACE1:
			case BACKSPACE2:
					if(ConsoleInstance->ReceivedCnt) {
						ConsoleInstance->ReceivedCnt--; 
						ConsoleInstance->Buffer[ConsoleInstance->ReceivedCnt] = 0;
					}
					break;

			// Przywr�cenie ostatnio wpisywanego polecenia
			// !! niech to b�dzie opcjonalne
			case CTRL_Z:	
				// Kasowanie dotychczas wpisanego polecenia
				while(ConsoleInstance->ReceivedCnt) {
					ConsoleInstance->ReceivedCnt--;
					ConsoleInstance->Buffer[ConsoleInstance->ReceivedCnt] = 0;
					Uart_Write(BACKSPACE1, ConsoleInstance->UartInstance); 
				}
			
				// Kopiowanie z drugiego bufora	
				memcpy(ConsoleInstance->Buffer, ConsoleInstance->Buffer2, CMD_LINE_BUFFER_LENGTH);
				ConsoleInstance->ReceivedCnt = strlen((const char *)ConsoleInstance->Buffer);
				Uart_Write((const char *)ConsoleInstance->Buffer, ConsoleInstance->UartInstance);									// Wy�wietlenie zawarto�ci bufora tylko dla cz�owieka
				break;

			// SOH - pocz�tek przesy�ania polecenia, kasowanie bufora, je�eli nie jest pusty
			case SOH:
				if(ConsoleInstance->ReceivedCnt) {						// Czyszczenie bufora
					ConsoleInstance->ReceivedCnt = 0;
					ConsoleInstance->ControlUse = false;
					ConsoleInstance->CRCH = 0;
					memset(ConsoleInstance->Buffer, 0, CMD_LINE_BUFFER_LENGTH);
				}
				break;

			// ESCAPE - to samo, ale wprowadzone z klawiatury przez u�ytkownika
			case ESC:
				if(ConsoleInstance->ReceivedCnt) {						// Czyszczenie bufora
					ConsoleInstance->ReceivedCnt = 0;
					ConsoleInstance->ControlUse = false;
					ConsoleInstance->CRCH = 0;
					memset(ConsoleInstance->Buffer, 0, CMD_LINE_BUFFER_LENGTH);
				}
				return Console_InputCancelled;
				break;

			// Wszystkie inne znaki ignorujemy - w tym NUL i LF
			default:
			
				break;
		}
	}
	
	return Console_OK;
}


// Wy�wietlenie znaku zach�ty wiersza polece�
// - Console_Struct * ConsoleInstance					-	Wska�nik do struktry konsoli
void Console_PromptShow(Console_Struct * ConsoleInstance) {
	Uart_Write("\r\n > ", ConsoleInstance->UartInstance);
	Uart_Write(DC4, ConsoleInstance->UartInstance);
}









// Dzielenie wej�ciowego stringu z wierza polece� na pojedyncze argumenty
// - Console_Struct * ConsoleInstance					-	Wska�nik do struktry konsoli
// - CmdLine											-	Wiersz polece� wpisany z klawiatury
// - argc												-	Wska�nik, przez kt�ry zwracana jest liczba znalezionych argument�w
// - argv												-	Wska�nik do tablicy wska�nik�w, w kt�rej zapisywane s� wska�niki do kolejnych argument�w
static inline CmdRes_t Console_SplitArguments(Console_Struct * ConsoleInstance, uint8_t * argc, uint8_t * argv[]) {
	
	uint8_t		ArgCount		=	0;
	uint8_t *	CharPointer		=	ConsoleInstance->Buffer;
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
						if(ArgCount == CMD_MAX_ARGUMENTS) {				// Przekroczenie dopuszczalnej liczby argument�w
							Uart_Write("max arg");
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
					if(ArgCount == CMD_MAX_ARGUMENTS) {
						Uart_Write("max arg");
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

	return Cmd_OK;
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


// Wyszukiwanie funkcji dla wpisanego polecenia
// Nazwa polecenia jest przechowywana w argumencie zerowym argv[0]
// Funkcja zwraca wska�nik do funkcji typu void pobieraj�cej argumenty uint8_t argc, uint8_t * argv[]
// Argumentem przyjmowanym przez Cmd_FindCommand() jest wska�nik do stringu EnteredName zawieraj�cego polecenie wpisane przez u�ytkownika
// Je�eli Cmd_FindCommand nie znajdzie funkcji odpowiadaj�cej poleceniu to zwraca wska�nik NULL
static inline void (*Console_FindPointer(uint8_t * EnteredName))(uint8_t argc, uint8_t * argv[]) { 
	
	for(uint8_t i=0; i<(sizeof(Console_CommandList)/sizeof(Console_NamePointer_t)); i++) {
		if(Console_StrCmp((const char *)EnteredName, Console_CommandList[i].Name)) {
			return Console_CommandList[i].Pointer; 
		}
	}
	return NULL;
}

// =======
// Testowe
// =======

// Pokazywanie wszystkicj p�l struktury
// void Console_StructPrint(Console_Struct * ConsoleInstance) {
// 	Uart_Write("\r\nReceivedCnt\t");
// 	Uart_WriteDec(ConsoleInstance->ReceivedCnt);
// 	
// 	Uart_Write("\r\nBuffer\t");
// 	for(uint8_t i=0; i<CMD_LINE_BUFFER_LENGTH; i++) {
// 		Uart_Write(ConsoleInstance->Buffer[i]);
// 	}
// 	
// 	Uart_Write("\r\nBuffer2\t");
// 	for(uint8_t i=0; i<CMD_LINE_BUFFER_LENGTH; i++) {
// 		Uart_Write(ConsoleInstance->Buffer2[i]);
// 	}
// 	
// 	Uart_Write("\r\nUartInstance\t");
// 	Uart_WriteHex(uint16_t(ConsoleInstance->UartInstance));
// 	
// 	Uart_Write("\r\nControlUse\t");
// 	Uart_WriteHex(uint8_t(ConsoleInstance->ControlUse));
// 	
// 	Uart_Write("\r\nCRCH\t");
// 	Uart_WriteHex(uint8_t(ConsoleInstance->CRCH));
// 	
// 	Uart_Write("\r\nToken\t");
// 	Uart_WriteHex(uint8_t(ConsoleInstance->Token));
// 	
// 	Uart_Write("\r\nFlags\t");
// 	Uart_WriteHex(uint8_t(ConsoleInstance->Flags));
// }


// Pokazywanie wszystkich dost�pnych polece�
#if CMD_USE_ALL
void Console_ShowAllCommands(uint8_t argc, uint8_t * argv[]) {
	for(uint8_t i=0; i<(sizeof(Console_CommandList)/sizeof(Console_NamePointer_t)); i++) {
		Uart_WriteDec(i);
		Uart_Write(":\t");
		Uart_WriteHex((uint16_t)Console_CommandList[i].Pointer);
		Uart_Write('\t');
		Uart_Write((const char *)Console_CommandList[i].Name);
		Uart_WriteNL();
	}
}
#endif


// Standardowa odpowied� OK
void Console_ResponseOK(void) {
	Uart_Write("OK");
}

// Standardowa odpowied� Error
void Console_ResponseError(void) {
	Uart_Write("Error");
}


// Standardowa odpowied� In Progress...
void Console_ResponseInProgress(void) {
	Uart_Write("In progress... ");
}


// Standardowa odpowied� Timeout
void Console_ResponseTimeout(void) {
	Uart_Write("Timeout");
}


// Standardowa odpowied� Not supported
void Console_ResponseNotSupported(void) {
	Uart_Write("Not supported");
}

// ==================
// Parsery argument�w
// ==================


// Debugowanie b��d�w
void Console_Debug(const CmdRes_t Result, const uint8_t * Argument) {
	Uart_Write("Error");
	if(Argument != NULL) {
		Uart_Write(" in agument ");
		Uart_Write((const char *)Argument);
	}
	Uart_Write(": ");

	switch(Result) {
		case Cmd_OK:									Uart_Write("OK");								break;
		case Cmd_NotReady:								Uart_Write("Not ready");						break;
		case Cmd_UnknownCommand:						Uart_Write("Unknown command");					break;
		case Cmd_NoInput:								Uart_Write("No input");							break;
		case Cmd_Overflow:								Uart_Write("Overflow");							break;
		case Cmd_MissingArgument:						Uart_Write("Missing arg");						break;
		case Cmd_Underflow:								Uart_Write("Underflow");						break;
		case Cmd_ParseError:							Uart_Write("Parse error");						break;
		case Cmd_ExpectedHex:							Uart_Write("Expected Hex");						break;
		case Cmd_ExpectedDec:							Uart_Write("Expected Dec");						break;
		case Cmd_ReceivedACK:							Uart_Write("Received ACK");						break;
		case Cmd_ReceivedNAK:							Uart_Write("Received NAK");						break;
	}
}



// Funkcja przekszta�ca znak ASCII HEX na warto�� binarn�
// - InputChar	- Wska�nik do badanego znaku
// - OutputChar	- Wska�nik do zmiennej, w kt�rej ma by� zapisany nibble
static CmdRes_t Parse_HexChar(const uint8_t * InputChar, uint8_t * OutputChar) {
	if(*InputChar >= '0' && *InputChar <= '9') {
		*OutputChar = *InputChar - '0';
		return Cmd_OK;
	}
	else if(*InputChar >= 'A' && *InputChar <= 'F') {
		*OutputChar = *InputChar - 55;
		return Cmd_OK;
	}
	else if(*InputChar >= 'a' && *InputChar <= 'f') {
		*OutputChar = *InputChar - 87;
		return Cmd_OK; 
	}
	else {
		return Cmd_ExpectedHex;
	}
}



static CmdRes_t Parse_HexChar_new(const uint8_t * InputChar, uint8_t * OutputChar, bool HighNibble) {
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
		return Cmd_ExpectedHex;
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
	
	return Cmd_OK; 
}


// Przetwarzanie stringu od ko�ca, a output od pocz�tku
// Zmienna wskazywana przez *Output musi by� wyzerowana, inaczej b�dzie b��d losowo zainicjalizowanej pami�ci
CmdRes_t Parse_HexNum(const uint8_t * Argument, void * Output, uint8_t Characters) {
	
	CmdRes_t Result;
	const uint8_t * OrgArgument = Argument;
	
	// Kontrola czy podano argument
	if(Argument == NULL) {
		Result = Cmd_MissingArgument;
		goto End;
	}
	
	// Przesuni�cie wska�nika na koniec ci�gu znak�w argumentu
	Argument = Argument + Characters;
	
	// Sprawdzanie czy ostatni bajt argumentu to 0, je�eli nie to znaczy, �e przes�ano wi�cej znak� ni� jest potrzebne dla konkretnego typu zmiennej
	if(*Argument != 0) {
		Result = Cmd_Overflow;
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
CmdRes_t Parse_Hex8(const uint8_t * Argument, uint8_t * Output) {
	*Output = 0;
	return Parse_HexNum(Argument, Output, 2);
}


// Parsowanie liczby HEX 16-bitowej
// - Argument	- Wska�nik do argumentu, kt�ry ma by� przetworzony
// - Output		- Wska�nik do zmiennej, w kt�rej b�dzie zwr�cony wynik
CmdRes_t Parse_Hex16(const uint8_t * Argument, uint16_t * Output) {
	*Output = 0;
	return Parse_HexNum(Argument, Output, 4);
}


// Parsowanie liczby HEX 32-bitowej
// - Argument	- Wska�nik do argumentu, kt�ry ma by� przetworzony
// - Output		- Wska�nik do zmiennej, w kt�rej b�dzie zwr�cony wynik
CmdRes_t Parse_Hex32(const uint8_t * Argument, uint32_t * Output) {
	*Output = 0;
	return Parse_HexNum(Argument, Output, 8);
}


// Parsowanie liczby HEX 64-bitowej
// - Argument	- Wska�nik do argumentu, kt�ry ma by� przetworzony
// - Output		- Wska�nik do zmiennej, w kt�rej b�dzie zwr�cony wynik
CmdRes_t Parse_Hex64(const uint8_t * Argument, uint64_t * Output) {
	*Output = 0;
	return Parse_HexNum(Argument, Output, 16);
}


// Konwertowanie stringu znak�w ASCII HEX na dane zapisane binarnie. W rezultacie wynikowy string jest 2x kr�tszy od
// stringu wej�ciowego (je�li by�y w nim spacje to dodatowo zosta�y wyci�te). Wszystkie nadmiarowe znaki zostaj� zast�pione zerami,
// aby mo�na by�o wykorzysta� miejsce w pami�ci, kt�re jest dotychczas zajmowane przez string wej�ciowy.
// - String		- wej�cie i wyj�cie
// - MaxLength	- maksymalna dopuszczalna d�ogo�� stringu po przetworzeniu, domy�lnie 255 znak�w
// - MinLength	- minimalna dopuszczalna d�ugo�� stringu po przetworzeniu, domy��nie 0 znak�w
CmdRes_t Parse_HexString(const uint8_t * InputString, uint8_t * OutputString, uint8_t * OutputLength, const uint8_t MaxLength, const uint8_t MinLength) {
	
	// Wska�niki aktualnie przetwarzanych znak�w
	const uint8_t * OrgArgument = InputString;
	uint8_t NibbleH;
	uint8_t NibbleL;
	*OutputLength = 0;
	CmdRes_t Result;

	// przetwarzanie a� do napotkania znaku 0
	while(*InputString != 0) {
		
		// Kontrola przepe�nienia
		if(*OutputLength == MaxLength) {
			Result = Cmd_Overflow;
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
		Result = Cmd_Underflow;
	}
	
	// Wy�wietlenie informacji o ewentualnym b��dzie i zwr�cenie wyniku
	End:
	if(Result) {
		Console_Debug(Result, OrgArgument);
	}
	return Result;
}


// Parsowanie stringu ASCII
CmdRes_t Parse_AsciiString(const uint8_t * InputString, uint8_t * OutputString, uint8_t * OutputLength, const uint8_t MaxLength, const uint8_t MinLength) {
	
	// Wska�niki aktualnie przetwarzanych znak�w
	const uint8_t * OrgArgument = InputString;
	*OutputLength = 0;
	CmdRes_t Result = Cmd_OK;

	// przetwarzanie a� do napotkania znaku 0
	while(*InputString != 0) {
		
		// Kontrola przepe�nienia
		if(*OutputLength == MaxLength) {
			Result = Cmd_Overflow;
			goto End;
		}
		
		// Kopiowanie znaku
		*OutputString++ = *InputString++;

		// Licznie znak�w w stringu wynikowym
		(*OutputLength)++;
	}

	// Kontrola d�ugo�ci
	if(*OutputLength < MinLength) {
		Result = Cmd_Underflow;
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
static CmdRes_t Parse_DecChar(const uint8_t * InputChar, uint8_t * OutputChar) {
	if(*InputChar >= '0' && *InputChar <= '9') {
		*OutputChar = *InputChar - '0';
		return Cmd_OK;
	}
	else {
		return Cmd_ExpectedDec;
	}
}


// Parsowanie liczby dziesi�tnej 8-bitowej
// - Argument	- Wska�nik do argumentu, kt�ry ma by� przetworzony
// - Output		- Wska�nik do zmiennej, w kt�rej b�dzie zwr�cony wynik
CmdRes_t Parse_Dec8(const uint8_t * Argument, uint8_t * Output, const uint8_t MaxValue) {
	
	const uint8_t * OrgArgument = Argument;
	uint8_t Digit; 	
	uint8_t Temp = 0;
	uint8_t Temp2;
	CmdRes_t Result;

	// Kontrola czy podano argument
	if(Argument == NULL) {
		Result = Cmd_MissingArgument;
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
			Result = Cmd_Overflow;
			goto End;
			//return Cmd_Overflow;
		}
	} 

	// Zwracanie wyniku
	if(Temp <= MaxValue) {
		*Output = Temp;
	}
	else {
		Result = Cmd_Overflow;
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
CmdRes_t Parse_Dec16(const uint8_t * Argument, uint16_t * Output, const uint16_t MaxValue) {
	
	const uint8_t * OrgArgument = Argument;
	uint8_t Digit; 	
	uint16_t Temp = 0;
	uint16_t Temp2;
	CmdRes_t Result;

	// Kontrola czy podano argument
	if(Argument == NULL) {
		Result = Cmd_MissingArgument;
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
			Result = Cmd_Overflow;
			goto End;
			//return Cmd_Overflow;
		}
	} 

	// Zwracanie wyniku
	if(Temp <= MaxValue) {
		*Output = Temp;
	}
	else {
		Result = Cmd_Overflow;
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
CmdRes_t Parse_Dec32(const uint8_t * Argument, uint32_t * Output, const uint32_t MaxValue) {
	
	const uint8_t * OrgArgument = Argument;
	uint8_t Digit; 	
	uint32_t Temp = 0;
	uint32_t Temp2;
	CmdRes_t Result;

	// Kontrola czy podano argument
	if(Argument == NULL) {
		Result = Cmd_MissingArgument;
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
			Result = Cmd_Overflow;
			goto End;
		}
	} 

	// Zwracanie wyniku
	if(Temp <= MaxValue) {
		*Output = Temp;
	}
	else {
		Result = Cmd_Overflow;
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
CmdRes_t Parse_Dec64(const uint8_t * Argument, uint64_t * Output, const uint64_t MaxValue) {
	
	const uint8_t * OrgArgument = Argument;
	uint8_t Digit; 	
	uint64_t Temp = 0;
	uint64_t Temp2;
	CmdRes_t Result;

	// Kontrola czy podano argument
	if(Argument == NULL) {
		Result = Cmd_MissingArgument;
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
			Result = Cmd_Overflow;
			goto End;
		}
	} 

	// Zwracanie wyniku
	if(Temp <= MaxValue) {
		*Output = Temp;
	}
	else {
		Result = Cmd_Overflow;
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
CmdRes_t Parse_Dec32S(const uint8_t * Argument, int32_t * Output) {
	
	const uint8_t * OrgArgument = Argument;
	uint8_t Digit; 	
	int32_t Temp = 0;
	int32_t Temp2;
	CmdRes_t Result;
	bool Negative = false;

	// Kontrola czy podano argument
	if(Argument == NULL) {
		Result = Cmd_MissingArgument;
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
			Result = Cmd_Overflow;
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