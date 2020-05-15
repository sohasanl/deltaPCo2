#pragma once
#include "Co2System.h"
#include "SerialWriter.h"
namespace deltaPCo2{
class State : public SerialWriter {
public:
	State();
    virtual ~State();
	virtual bool readSensors(Co2System* pCo2Sys);
	virtual bool sleep(Co2System* pCo2Sys);
	virtual bool wakeup(Co2System* pCo2Sys);
	virtual bool publish(Co2System* pCo2Sys);
	virtual bool log(Co2System* pCo2Sys);
};
}