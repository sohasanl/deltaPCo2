#include "Co2System.h"
#include "SleepState.h"
#include "PublishState.h"

namespace deltaPCo2{

Co2System::Co2System(USBSerial& aSerial, unsigned int sp, unsigned int sd, float sr, float lf)
    : Peripherals(Serial1), T(sp, sd, sr, lf), anActiveSerial(aSerial, cmdProcessor){
	SYSTEM_THREAD(ENABLED);
	m_CurrentState = new SleepState(); 
}

Co2System::~Co2System() {
	if(m_CurrentState) {delete m_CurrentState;}
}

////////////////////////////////////////////////////////////
// State Machine Methods
////////////////////////////////////////////////////////////

bool Co2System::publish() {
	if (m_CurrentState)
		return m_CurrentState->publish(this);
	return false;
}
bool Co2System::sleep() {
	if (m_CurrentState)
		return m_CurrentState->sleep(this);
	return false;
}
bool Co2System::readSensors() {
	if (m_CurrentState)
		return m_CurrentState->readSensors(this);
	return false;
}
bool Co2System::log() {
	if (m_CurrentState)
		return m_CurrentState->log(this);
	return false;
}
bool Co2System::wakeup() {
	if (m_CurrentState)
		return m_CurrentState->wakeup(this);
	return false;
}
void Co2System::setCurrentState(State* currentState) {
	if (m_CurrentState) {
		delete m_CurrentState;
		m_CurrentState = NULL;
	}
	m_CurrentState = currentState;
}
}























