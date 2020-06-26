#pragma once
#include "StateMachine.h"
#include "State.h"
namespace deltaPCo2{
class SleepState : public State {
public:
	bool wakeup(StateMachine* pCo2Sys);
};
}
