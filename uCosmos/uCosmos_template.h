#ifndef UCOSMOS_TEMPLATE_H_
#define UCOSMOS_TEMPLATE_H_

// Task template v1.17
task_t Task_Template(runmode_t RunMode) {
	
	// Variables
	
	
	// Normal execution
	if(RunMode == Run) {
		
	}
	
	// Constructor
	else if(RunMode == FirstRun) {
		
	}
	
	// Destructor
	else if(RunMode == Close) {
		
	}
	
	// Identification
	#if OS_USE_TASK_IDENTIFY
	else if(RunMode == Identify) {
		Print("TaskName");
	}
	#endif
	
	return TaskOK;
}

#endif /* UCOSMOS_TEMPLATE_H_ */