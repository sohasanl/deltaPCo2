#pragma once
#include "Co2System.h"
#include "State.h"
class SleepState : public State {
public:
	bool wakeup(Co2System* pCo2Sys);
};
