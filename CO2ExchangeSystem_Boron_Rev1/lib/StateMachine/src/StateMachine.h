#pragma once
#include "Particle.h"
#include "Timing.h"
#include "ActiveSerial.h"
#include "Peripherals.h"

#include <functional>



namespace deltaPCo2{

class State;
class AppProcessor;

class StateMachine : public Peripherals{	
public:

	StateMachine(USARTSerial& aHardwareSerial, USBSerial& aSerial);
	~StateMachine();
	
    /////////////////////////////////////////////////
	// State Machine Methods
	/////////////////////////////////////////////////
	bool readSensors();
	bool publish();
	bool sleep();
	bool log();
	bool wakeup();
	void setCurrentState(State* currentState);

    /////////////////////////////////////////////////
	// TimeTable Setter/Getter
	/////////////////////////////////////////////////
	T& getTimeTable(){return TimeTable;}

private:
	State*        m_CurrentState;
};
}
