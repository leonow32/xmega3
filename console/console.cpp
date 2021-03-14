// Wersja 0.22

#if C_CONSOLE

#include "console.h"

// Tablica poleceñ 
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


// Funkcja wywo³ywana z tasku obs³uguj¹cego konsolê
// - Console_Struct * ConsoleInstance		-	WskaŸnik do struktry konsoli
void Console_TaskHandler(Console_Struct * ConsoleInstance) {
	
	// Pobieranie danych z UART
	while(Uart_ReceivedCnt(ConsoleInstance->UartInstance)) {
		
		// Przekazywanie znaków z bufora UART do bufora konsoli i podejmywanie dalszych dzia³a w zale¿noœci od Console_Result
		Console_Res_t Console_Result;
		Console_Result =  Console_UartInput(ConsoleInstance);
		
		// Je¿eli zakoñczono odbieranie polecenia
		if(Console_Result == Console_ReceivedCommand) {
			
			// !! wyrzuciæ to
			//_delay_us(250);
			
			// Zmienne
			uint8_t			argc = 0;												// Liczba wpisanych argumentów
			uint8_t *		argv[CMD_MAX_ARGUMENTS];								// Tablica wskaŸników do argumentów
			//void			(*CommandPointer)(uint8_t argc, uint8_t * argv[]);		// WskaŸnik do funkcji, która ma byæ wywo³ana
			memset(argv, 0, sizeof(argv));

			// Kopiowanie do bufora CTRL-Z
			memcpy(ConsoleInstance->Buffer2, ConsoleInstance->Buffer, CMD_LINE_BUFFER_LENGTH);

			// Dzielenie bufora na poszczególne argumenty
			Console_SplitArguments(ConsoleInstance, &argc, argv);

			// Wyszukiwanie wskaŸnika 
			void (*CommandPointer)(uint8_t argc, uint8_t * argv[]) = Console_FindPointer(argv[0]);

			// Zejœcie do nowej linii, ¿eby w trybie rêcznym ³adnie wygl¹da³o w terminalu
			if(ConsoleInstance->Flags & FLAGS_USE_HMI) {
				Uart_WriteNL(ConsoleInstance->UartInstance);
			}

			// Ustawienie portu UART, który ma otrzymaæ odpowiedŸ
			UART_PortOverride = ConsoleInstance->UartInstance;

			// Wykonanie polecenia, jeœli rozpoznano
			if(CommandPointer) {
				
				// Prolog odpowiedzi
				Uart_TxBufferFlush(ConsoleInstance->UartInstance);
				Uart_Write(ACK, ConsoleInstance->UartInstance);
				//Uart_TxCrcClear(ConsoleInstance->UartInstance);
				//_delay_us(3);
				
				
				//_delay_us(5);
				
				// Wywo³anie funkcji odpowiadaj¹cej poleceniu
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
				
				// Czekanie na zakoñczenie wysy³ania polecenia
				// !! to raczej nie jest potrzebne
				Uart_WaitForTxComplete(ConsoleInstance->UartInstance);
			}
			
			// Je¿eli nie rozpoznano polecenia
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
			// !! Kasowanie kolejnych poleceñ, które mog³y zostaæ odebrane podczas wykonywania poprzedniego polecenia
			Uart_RxBufferFlush(ConsoleInstance->UartInstance);

			// Przywrócenie domyœlnego portu UART
			UART_PortOverride = NULL;

			// Czyszczenie aktualnego bufora wiersza poleceñ
			memset(ConsoleInstance->Buffer, 0, CMD_LINE_BUFFER_LENGTH);
			ConsoleInstance->ReceivedCnt = 0;

			// Prompt by zasygnalizowaæ gotowoœæ do przyjêcia kolejnego polecenia
			if(ConsoleInstance->Flags & FLAGS_USE_HMI) {
				Console_PromptShow(ConsoleInstance);
			}
			
			// Czyszczenie wszystkich flag, pozostawiaj¹c flagi HMI i M2M takie jak by³y wczeœniej
			ConsoleInstance->Flags = ConsoleInstance->Flags & (FLAGS_USE_HMI | FLAGS_USE_M2M);
		}

		// Wciœniêto ESCAPE
		else if(Console_Result == Console_InputCancelled) {
			//Uart_Write("[Console ");
			//Uart_WriteHex((uint16_t)ConsoleInstance);
			//Uart_Write(" CANCELED] ");
			//PF2_ON;
			Console_PromptShow(ConsoleInstance);
			
			// Czyszczenie wszystkich flag, pozostawiaj¹c flagi HMI i M2M takie jak by³y wczeœniej
			ConsoleInstance->Flags = ConsoleInstance->Flags & (FLAGS_USE_HMI | FLAGS_USE_M2M);
		}
	}

}


// Pobieranie jednego znaku z UART i kopiowanie do bufora lub wykonywanie akcji
// - Console_Struct * ConsoleInstance					-	WskaŸnik do struktry konsoli
Console_Res_t Console_UartInput(Console_Struct * ConsoleInstance) {
	
	uint8_t ReceivedChar = Uart_Read(ConsoleInstance->UartInstance);
	static uint8_t TestMode = 0;
	
// 	UART_PortOverride = &UART_DEFAULT_PORT;
// 	Uart_WriteHex(ReceivedChar, ' ', ConsoleInstance->UartInstance);
// 	Uart_Write(ReceivedChar, ConsoleInstance->UartInstance);
// 	Uart_WaitForTxComplete(&UART_DEFAULT_PORT);
// 	UART_PortOverride = NULL;
	
	// Je¿eli mamy trub M2M i wczeœniej odebraliœmy US
	if(ConsoleInstance->Flags & FLAGS_NEXT_BYTE_CRCH) {
		ConsoleInstance->CRCH	=	ReceivedChar;
		ConsoleInstance->Flags	&= ~FLAGS_NEXT_BYTE_CRCH;
		ConsoleInstance->Flags	|=	FLAGS_NEXT_BYTE_CRCL;
		return Console_OK;
	}
	
	// Je¿eli mamy tryb M2M i wczeœniej odebraliœmy CRCH
	if(ConsoleInstance->Flags & FLAGS_NEXT_BYTE_CRCL) {
		
		// Kasowanie flagi
		ConsoleInstance->Flags &=  ~FLAGS_NEXT_BYTE_CRCL;
		ConsoleInstance->Flags |=	FLAGS_NEXT_BYTE_TOKEN;
		
		uint16_t ReceivedCRC = uint16_t(ConsoleInstance->CRCH) << 8 | ReceivedChar;
		//uint16_t CalculatedCRC = Remote_CRC(ConsoleInstance->Buffer, ConsoleInstance->ReceivedCnt);
		
		// TODO: oryginalnie odkomentowane, dodac jakiœ #if
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
			
			// Sprawdzenie czy to duplikat polecenia - otrzymano polecenie z DC2, ale wczeœniej podano odpowiedŸ
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
			
			// Poprawna weryfikacja - mo¿na wykonaæ polecenie
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
			
			// CRC siê nie zgadza, odsy³amy NAK i czekamy na ponowne przes³anie polecenia
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
	
	// Je¿eli mamy tryb M2M i wczeœniej odebraliœmy CRCH
	if(ConsoleInstance->Flags & FLAGS_NEXT_BYTE_TOKEN) {
		
		ConsoleInstance->Flags &= ~FLAGS_NEXT_BYTE_TOKEN;
		
		// Je¿eli CRC nie by³o prawid³owe
		if(ConsoleInstance->Flags & FLAGS_WRONG_CRC) {
			
			// Token ignorujemy i od razu odsy³amy NAK
			ConsoleInstance->ReceivedCnt = 0;
			ConsoleInstance->ControlUse = false;
			ConsoleInstance->CRCH = 0;
			ConsoleInstance->Flags = ConsoleInstance->Flags & (FLAGS_USE_HMI | FLAGS_USE_M2M);
			memset(ConsoleInstance->Buffer, 0, CMD_LINE_BUFFER_LENGTH);
			Uart_Write(NAK, ConsoleInstance->UartInstance);
		}
		else {
			// CRC prawid³owe
			
			// Sprawdzamy czy polecenie jest inne ni¿ poprzednio odebrane
			if(Console_StrCmp((const char *)ConsoleInstance->Buffer, (const char *)ConsoleInstance->Buffer2)) {
				
				// Polecenie jest takie samo jak poprzednio odebrane, wiêc musimy jeszcze sprawdziæ czy token jest inny
				if(ConsoleInstance->Token == ReceivedChar) {
					// Token taki sam jak wczeœnie, a wiêc dostaliœmy duplikat
					
					Uart_Write("\r\n[Duplicate_CMD ");
					for(uint8_t i=0; i<16; i++) {
						Uart_Write(ConsoleInstance->Buffer[i]);
					}
					Uart_Write("] ");
					//ERROR_ON;
					
					// Ponowne wys³anie bufora
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
			
			// Mo¿na przyst¹piæ do wykonywania polecenia
			// Zapisanie tokena, aby odes³aæ go wraz z odpowiedzi¹
			ConsoleInstance->Token = ReceivedChar;
			
			// Poprawna weryfikacja - mo¿na wykonaæ polecenie
			return Console_ReceivedCommand;
		}
	}

	
	// Znaki printable dodajemy do bufora
	if(ReceivedChar >= ' ' && ReceivedChar <= '~') {
		
		// Je¿eli bufor jest pusty i otrzymujemy znaki spacja i > 
		// !! wywaliæ to, bo bez sensu
		if(ConsoleInstance->ReceivedCnt == 0) {
			if(ReceivedChar == ' ') return Console_OK;
			if(ReceivedChar == '>') return Console_OK;
		}
		
		// Sprawdzenie czy jest wolne miejsce w buforze
		if(ConsoleInstance->ReceivedCnt >= CMD_LINE_BUFFER_LENGTH) {
			
			// !! co robiæ, kiedy nie ma miejsca w buforze?
			#if REMOTE_DEBUG
				//ERROR_ON;
				//Uart_Write('_');										// !! który uart?
				Uart_Write(ReceivedChar);
			#endif

			return Console_BufferFull;
		}
		else {
			// Dodawanie znakówdo bufora 
			ConsoleInstance->Buffer[ConsoleInstance->ReceivedCnt++] = ReceivedChar;
			return Console_OK;
		}
	}
	
	// Interpretowanie znaków kontrolnych dla M2M
	if(ConsoleInstance->Flags & FLAGS_USE_M2M) {
		
		switch(ReceivedChar) {
			
				// DC1 - pocz¹tek polecenia w trybie M2M
			case DC1:
				ConsoleInstance->Flags	|=	FLAGS_M2M_CMD;
				if(ConsoleInstance->ReceivedCnt) {						// Czyszczenie bufora
					ConsoleInstance->ReceivedCnt = 0;
					ConsoleInstance->ControlUse = false;
					ConsoleInstance->CRCH = 0;
					memset(ConsoleInstance->Buffer, 0, CMD_LINE_BUFFER_LENGTH);
				}
				break;
			
		
			// DC2 - pocz¹tek polecenia w trybie M2M, które zosta³o przes³ane ponownie z powodu b³êdu
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
			

			// ¯¹danie ponownego przes³ania odpowiedzi na poprzednie polecenie
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
				
				
			// ACK - otrzymano odpowiedŸ na polecenie, najprawdopodobniej Remote wys³a³ polecenie i wyst¹pi³ timeout, a dopiero teraz zdalna konsola przys³a³a odpowiedŸ, ignorujemy ca³y bufor
			case ACK:
				_delay_ms(10);	// czas na ewentualne przes³anie reszty polecenia
				Uart_RxBufferFlush(ConsoleInstance->UartInstance);
				break;
			
				
		}
	}
	
	
	// Interpretowanie znaków kontrolnych dla HMI
	if(ConsoleInstance->Flags & FLAGS_USE_HMI) {
		switch(ReceivedChar) {
		
			// Enter
			case CR:
				// Zwracanie Console_OK tylko je¿eli coœ mamy w buforze, jeœli bufor jest pusty to brak reakcji
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

			// Przywrócenie ostatnio wpisywanego polecenia
			// !! niech to bêdzie opcjonalne
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
				Uart_Write((const char *)ConsoleInstance->Buffer, ConsoleInstance->UartInstance);									// Wyœwietlenie zawartoœci bufora tylko dla cz³owieka
				break;

			// SOH - pocz¹tek przesy³ania polecenia, kasowanie bufora, je¿eli nie jest pusty
			case SOH:
				if(ConsoleInstance->ReceivedCnt) {						// Czyszczenie bufora
					ConsoleInstance->ReceivedCnt = 0;
					ConsoleInstance->ControlUse = false;
					ConsoleInstance->CRCH = 0;
					memset(ConsoleInstance->Buffer, 0, CMD_LINE_BUFFER_LENGTH);
				}
				break;

			// ESCAPE - to samo, ale wprowadzone z klawiatury przez u¿ytkownika
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


// Wyœwietlenie znaku zachêty wiersza poleceñ
// - Console_Struct * ConsoleInstance					-	WskaŸnik do struktry konsoli
void Console_PromptShow(Console_Struct * ConsoleInstance) {
	Uart_Write("\r\n > ", ConsoleInstance->UartInstance);
	Uart_Write(DC4, ConsoleInstance->UartInstance);
}









// Dzielenie wejœciowego stringu z wierza poleceñ na pojedyncze argumenty
// - Console_Struct * ConsoleInstance					-	WskaŸnik do struktry konsoli
// - CmdLine											-	Wiersz poleceñ wpisany z klawiatury
// - argc												-	WskaŸnik, przez który zwracana jest liczba znalezionych argumentów
// - argv												-	WskaŸnik do tablicy wskaŸników, w której zapisywane s¹ wskaŸniki do kolejnych argumentów
static inline CmdRes_t Console_SplitArguments(Console_Struct * ConsoleInstance, uint8_t * argc, uint8_t * argv[]) {
	
	uint8_t		ArgCount		=	0;
	uint8_t *	CharPointer		=	ConsoleInstance->Buffer;
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
						if(ArgCount == CMD_MAX_ARGUMENTS) {				// Przekroczenie dopuszczalnej liczby argumentów
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

		// Przesuwanie wskaŸnika na nastêpny znak linii poleceñ
		CharPointer++;	
	}

	*argc = ArgCount;

	return Cmd_OK;
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


// Wyszukiwanie funkcji dla wpisanego polecenia
// Nazwa polecenia jest przechowywana w argumencie zerowym argv[0]
// Funkcja zwraca wskaŸnik do funkcji typu void pobieraj¹cej argumenty uint8_t argc, uint8_t * argv[]
// Argumentem przyjmowanym przez Cmd_FindCommand() jest wskaŸnik do stringu EnteredName zawieraj¹cego polecenie wpisane przez u¿ytkownika
// Je¿eli Cmd_FindCommand nie znajdzie funkcji odpowiadaj¹cej poleceniu to zwraca wskaŸnik NULL
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

// Pokazywanie wszystkicj pól struktury
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


// Pokazywanie wszystkich dostêpnych poleceñ
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


// Standardowa odpowiedŸ OK
void Console_ResponseOK(void) {
	Uart_Write("OK");
}

// Standardowa odpowiedŸ Error
void Console_ResponseError(void) {
	Uart_Write("Error");
}


// Standardowa odpowiedŸ In Progress...
void Console_ResponseInProgress(void) {
	Uart_Write("In progress... ");
}


// Standardowa odpowiedŸ Timeout
void Console_ResponseTimeout(void) {
	Uart_Write("Timeout");
}


// Standardowa odpowiedŸ Not supported
void Console_ResponseNotSupported(void) {
	Uart_Write("Not supported");
}

// ==================
// Parsery argumentów
// ==================


// Debugowanie b³êdów
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



// Funkcja przekszta³ca znak ASCII HEX na wartoœæ binarn¹
// - InputChar	- WskaŸnik do badanego znaku
// - OutputChar	- WskaŸnik do zmiennej, w której ma byæ zapisany nibble
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
	
	// Przesuwanie je¿eli to jest starszy nibble
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


// Przetwarzanie stringu od koñca, a output od pocz¹tku
// Zmienna wskazywana przez *Output musi byæ wyzerowana, inaczej bêdzie b³¹d losowo zainicjalizowanej pamiêci
CmdRes_t Parse_HexNum(const uint8_t * Argument, void * Output, uint8_t Characters) {
	
	CmdRes_t Result;
	const uint8_t * OrgArgument = Argument;
	
	// Kontrola czy podano argument
	if(Argument == NULL) {
		Result = Cmd_MissingArgument;
		goto End;
	}
	
	// Przesuniêcie wskaŸnika na koniec ci¹gu znaków argumentu
	Argument = Argument + Characters;
	
	// Sprawdzanie czy ostatni bajt argumentu to 0, je¿eli nie to znaczy, ¿e przes³ano wiêcej znakó ni¿ jest potrzebne dla konkretnego typu zmiennej
	if(*Argument != 0) {
		Result = Cmd_Overflow;
		goto End;
	}
	
	// Przetwarzanie wszystkich znaków ASCII od koñca
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

	
	
	// Wyœwietlenie informacji o ewentualnym b³êdzie
	End:
	if(Result) {
		Console_Debug(Result, OrgArgument);
	}
	return Result;
}


// Parsowanie liczby HEX 8-bitowej
// - Argument	- WskaŸnik do argumentu, który ma byæ przetworzony
// - Output		- WskaŸnik do zmiennej, w której bêdzie zwrócony wynik
CmdRes_t Parse_Hex8(const uint8_t * Argument, uint8_t * Output) {
	*Output = 0;
	return Parse_HexNum(Argument, Output, 2);
}


// Parsowanie liczby HEX 16-bitowej
// - Argument	- WskaŸnik do argumentu, który ma byæ przetworzony
// - Output		- WskaŸnik do zmiennej, w której bêdzie zwrócony wynik
CmdRes_t Parse_Hex16(const uint8_t * Argument, uint16_t * Output) {
	*Output = 0;
	return Parse_HexNum(Argument, Output, 4);
}


// Parsowanie liczby HEX 32-bitowej
// - Argument	- WskaŸnik do argumentu, który ma byæ przetworzony
// - Output		- WskaŸnik do zmiennej, w której bêdzie zwrócony wynik
CmdRes_t Parse_Hex32(const uint8_t * Argument, uint32_t * Output) {
	*Output = 0;
	return Parse_HexNum(Argument, Output, 8);
}


// Parsowanie liczby HEX 64-bitowej
// - Argument	- WskaŸnik do argumentu, który ma byæ przetworzony
// - Output		- WskaŸnik do zmiennej, w której bêdzie zwrócony wynik
CmdRes_t Parse_Hex64(const uint8_t * Argument, uint64_t * Output) {
	*Output = 0;
	return Parse_HexNum(Argument, Output, 16);
}


// Konwertowanie stringu znaków ASCII HEX na dane zapisane binarnie. W rezultacie wynikowy string jest 2x krótszy od
// stringu wejœciowego (jeœli by³y w nim spacje to dodatowo zosta³y wyciête). Wszystkie nadmiarowe znaki zostaj¹ zast¹pione zerami,
// aby mo¿na by³o wykorzystaæ miejsce w pamiêci, które jest dotychczas zajmowane przez string wejœciowy.
// - String		- wejœcie i wyjœcie
// - MaxLength	- maksymalna dopuszczalna d³ogoœæ stringu po przetworzeniu, domyœlnie 255 znaków
// - MinLength	- minimalna dopuszczalna d³ugoœæ stringu po przetworzeniu, domyœ³nie 0 znaków
CmdRes_t Parse_HexString(const uint8_t * InputString, uint8_t * OutputString, uint8_t * OutputLength, const uint8_t MaxLength, const uint8_t MinLength) {
	
	// WskaŸniki aktualnie przetwarzanych znaków
	const uint8_t * OrgArgument = InputString;
	uint8_t NibbleH;
	uint8_t NibbleL;
	*OutputLength = 0;
	CmdRes_t Result;

	// przetwarzanie a¿ do napotkania znaku 0
	while(*InputString != 0) {
		
		// Kontrola przepe³nienia
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
		Result = Cmd_Underflow;
	}
	
	// Wyœwietlenie informacji o ewentualnym b³êdzie i zwrócenie wyniku
	End:
	if(Result) {
		Console_Debug(Result, OrgArgument);
	}
	return Result;
}


// Parsowanie stringu ASCII
CmdRes_t Parse_AsciiString(const uint8_t * InputString, uint8_t * OutputString, uint8_t * OutputLength, const uint8_t MaxLength, const uint8_t MinLength) {
	
	// WskaŸniki aktualnie przetwarzanych znaków
	const uint8_t * OrgArgument = InputString;
	*OutputLength = 0;
	CmdRes_t Result = Cmd_OK;

	// przetwarzanie a¿ do napotkania znaku 0
	while(*InputString != 0) {
		
		// Kontrola przepe³nienia
		if(*OutputLength == MaxLength) {
			Result = Cmd_Overflow;
			goto End;
		}
		
		// Kopiowanie znaku
		*OutputString++ = *InputString++;

		// Licznie znaków w stringu wynikowym
		(*OutputLength)++;
	}

	// Kontrola d³ugoœci
	if(*OutputLength < MinLength) {
		Result = Cmd_Underflow;
	}
	
	// Wyœwietlenie informacji o ewentualnym b³êdzie i zwrócenie wyniku
	End:
	if(Result) {
		Console_Debug(Result, OrgArgument);
	}
	return Result;
}


// Parsowanie liczby dziesiêtnej 8-bitowej
// Funkcja przekszta³ca znak ASCII HEX na wartoœæ binarn¹
// - InputChar	- WskaŸnik do badanego znaku
// - OutputChar	- WskaŸnik do zmiennej, w której ma byæ zapisany nibble
static CmdRes_t Parse_DecChar(const uint8_t * InputChar, uint8_t * OutputChar) {
	if(*InputChar >= '0' && *InputChar <= '9') {
		*OutputChar = *InputChar - '0';
		return Cmd_OK;
	}
	else {
		return Cmd_ExpectedDec;
	}
}


// Parsowanie liczby dziesiêtnej 8-bitowej
// - Argument	- WskaŸnik do argumentu, który ma byæ przetworzony
// - Output		- WskaŸnik do zmiennej, w której bêdzie zwrócony wynik
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
	
	// Wyœwietlenie informacji o ewentualnym b³êdzie i zwrócenie wyniku
	End:
	if(Result) {
		Console_Debug(Result, OrgArgument);
	}
	return Result;
}


// Parsowanie liczby dziesiêtnej 16-bitowej
// - Argument	- WskaŸnik do argumentu, który ma byæ przetworzony
// - Output		- WskaŸnik do zmiennej, w której bêdzie zwrócony wynik
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
	
	// Wyœwietlenie informacji o ewentualnym b³êdzie i zwrócenie wyniku
	End:
	if(Result) {
		Console_Debug(Result, OrgArgument);
	}
	return Result;
}


// Parsowanie liczby dziesiêtnej 32-bitowej
// - Argument	- WskaŸnik do argumentu, który ma byæ przetworzony
// - Output		- WskaŸnik do zmiennej, w której bêdzie zwrócony wynik
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
	
	// Wyœwietlenie informacji o ewentualnym b³êdzie i zwrócenie wyniku
	End:
	if(Result) {
		Console_Debug(Result, OrgArgument);
	}
	return Result;
}


// Parsowanie liczby dziesiêtnej 64-bitowej
// - Argument	- WskaŸnik do argumentu, który ma byæ przetworzony
// - Output		- WskaŸnik do zmiennej, w której bêdzie zwrócony wynik
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
	
	// Wyœwietlenie informacji o ewentualnym b³êdzie i zwrócenie wyniku
	End:
	if(Result) {
		Console_Debug(Result, OrgArgument);
	}
	return Result;
}


// Parsowanie liczby dziesiêtnej 32-bitowej ze znakiem
// - Argument	- WskaŸnik do argumentu, który ma byæ przetworzony
// - Output		- WskaŸnik do zmiennej, w której bêdzie zwrócony wynik
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
			Result = Cmd_Overflow;
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
		Console_Debug(Result, OrgArgument);
	}
	return Result;
}


#endif