#ifndef UCOSMOS_TEMPLATE_H_
#define UCOSMOS_TEMPLATE_H_

// Szablon tasku v1.16
task_t Task_Template(runmode_t RunMode) {
	
	// Zmienne
	
	
	// Normalne wywo³anie
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


	// Tryb wywo³ania
	switch(RunMode) {
		
		// Konstruktor
		case FirstRun:
			
			return TaskOK;

		// Destruktor
		case Close:
			
			return TaskDone;
		
		// Wywo³anie identyfikacyjne
		#if OS_USE_TASK_IDENTIFY
		case Identify:
			Uart_Write("TemplateName");
			return TaskOK;
		#endif

		// Normalne wywo³anie przez Scheduler
		case Run:
			
			// Je¿eli podczas normalnego wywo³ania task nie bêdzie ju¿ wiêcej potrzebny
			// to mo¿e zwróciæ TaskDane, aby Scheduler usun¹³ go z tablicy tasków
			return TaskOK;
	}

	return TaskOK;
} 


#endif /* UCOSMOS_TEMPLATE_H_ */