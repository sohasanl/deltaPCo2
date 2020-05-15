#include "Co2System.h"
#include "SleepState.h"
#include "PublishState.h"

namespace deltaPCo2{
bool SleepState::wakeup(Co2System* pCo2Sys) {
	pCo2Sys->setCurrentState(new PublishState());
	serialPrintln("Woke up!");
	return true;
}
}
