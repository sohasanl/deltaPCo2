#pragma once
#include "State.h"
#include "SleepState.h"
#include <vector>
#include <algorithm>

namespace deltaPCo2{



class PublishState : public State{

public:
	PublishState();
	~PublishState();
	bool sleep(Co2System* pCo2Sys);
	bool readSensors(Co2System* pCo2Sys);
	bool publish(Co2System* pCo2Sys);
	bool log(Co2System* pCo2Sys);
private:
	void goToSleep(int seconds);

};
}