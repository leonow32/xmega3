#ifndef UCOSMOS_TEMPLATE_H_
#define UCOSMOS_TEMPLATE_H_

// Szablon tasku v1.16
task_t Task_Template(runmode_t RunMode) {
	
	// Zmienne
	
	
	// Normalne wywo�anie
	if(RunMode == Run) {
		
	}
	
	// Konstruktor
	else if(RunMode == FirstRun) {
		
	}
	
	// Destruktor
	else if(RunMode == Close) {
		
	}
	
	// Identyfikacja
	#if OS_USE_TASK_IDENTIFY
	else if(RunMode == Identify) {
		Uart_Write("TaskName");
	}
	#endif
	
	return TaskOK;
}

// Szablon tasku na uCosmos v1.11
task_t Task_Template(runmode_t RunMode) {
	
	// Zmienne


	// Tryb wywo�ania
	switch(RunMode) {
		
		// Konstruktor
		case FirstRun:
			
			return TaskOK;

		// Destruktor
		case Close:
			
			return TaskDone;
		
		// Wywo�anie identyfikacyjne
		#if OS_USE_TASK_IDENTIFY
		case Identify:
			Uart_Write("TemplateName");
			return TaskOK;
		#endif

		// Normalne wywo�anie przez Scheduler
		case Run:
			
			// Je�eli podczas normalnego wywo�ania task nie b�dzie ju� wi�cej potrzebny
			// to mo�e zwr�ci� TaskDane, aby Scheduler usun�� go z tablicy task�w
			return TaskOK;
	}

	return TaskOK;
} 


#endif /* UCOSMOS_TEMPLATE_H_ */