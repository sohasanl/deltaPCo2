#pragma once
#include "Particle.h"
#include "Timing.h"
#include "ActiveSerial.h"
#include "Peripherals.h"
#include <functional>



namespace deltaPCo2{

class State;


class Co2System : public Peripherals{	
public:

	Co2System(USBSerial& aSerial, unsigned int sp=30, unsigned int sd=5, float sr=0.5, float lf=0.5);
	~Co2System();

	/////////////////////////////////////////////////
	// CommandLine Interface Methods
	///////////////////////////////////////////////// 
	static void cmdProcessor(USBSerial &aSerial, String buffer) {aSerial.println("hahaha");}
	
    /////////////////////////////////////////////////
	// State Machine Methods
	/////////////////////////////////////////////////
	bool readSensors();
	bool publish();
	bool sleep();
	bool log();
	bool wakeup();
	void setCurrentState(State* currentState);

	Timing T;

private:
	State*        m_CurrentState;
	ActiveSerial  anActiveSerial;
};
}
