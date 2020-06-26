#pragma once
#include "StateMachine.h"
#include "SerialWriter.h"
namespace deltaPCo2{
class State : public SerialWriter {
public:
	State();
    virtual ~State();
	virtual bool readSensors(StateMachine* pCo2Sys);
	virtual bool sleep(StateMachine* pCo2Sys);
	virtual bool wakeup(StateMachine* pCo2Sys);
	virtual bool publish(StateMachine* pCo2Sys);
	virtual bool log(StateMachine* pCo2Sys);
};
}