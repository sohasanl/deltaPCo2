#pragma once
#include "State.h"
#include "SleepState.h"
#include "Co2System.h"

class PublishState : public State {
public:
	bool sleep(Co2System* pCo2Sys);
	bool readSensors(Co2System* pCo2Sys);
	bool publish(Co2System* pCo2Sys);
	bool log(Co2System* pCo2Sys);
};
