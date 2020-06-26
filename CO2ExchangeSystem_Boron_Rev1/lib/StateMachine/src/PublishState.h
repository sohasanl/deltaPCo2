#pragma once
#include "State.h"
#include "SleepState.h"
#include "Timing.h"
#include <vector>
#include <algorithm>

namespace deltaPCo2{

class PublishState : public State{

public:
	PublishState();
	~PublishState();
	bool sleep(StateMachine* pCo2Sys);
	bool readSensors(StateMachine* pCo2Sys);
	bool publish(StateMachine* pCo2Sys);
	bool log(StateMachine* pCo2Sys);
private:
	void goToSleep(int seconds);

};
}