#include "Co2System.h"
#include "SleepState.h"
#include "PublishState.h"


bool SleepState::wakeup(Co2System* pCo2Sys) {
	pCo2Sys->setCurrentState(new PublishState());
	Serial.print("Woke up!\n");
	return true;
}
