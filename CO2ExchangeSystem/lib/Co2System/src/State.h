#pragma once
#include "Co2System.h"
class State {
public:
    virtual ~State();
	virtual bool readSensors(Co2System* pCo2Sys);
	virtual bool sleep(Co2System* pCo2Sys);
	virtual bool wakeup(Co2System* pCo2Sys);
	virtual bool publish(Co2System* pCo2Sys);
	virtual bool log(Co2System* pCo2Sys);
};