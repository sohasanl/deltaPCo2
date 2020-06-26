#include "StateMachine.h"
#include "SleepState.h"
#include "PublishState.h"

namespace deltaPCo2{
bool SleepState::wakeup(StateMachine* pCo2Sys) {
	pCo2Sys->setCurrentState(new PublishState());
	Serial.println("\n Woke up...");
	return true;
}

}
