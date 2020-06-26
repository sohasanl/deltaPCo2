#include "StateMachine.h"
#include "SleepState.h"
#include "PublishState.h"

namespace deltaPCo2{

StateMachine::StateMachine(USARTSerial& aUsartSerial, USBSerial& aUsbSerial)
    : Peripherals(aUsartSerial, aUsbSerial){
	m_CurrentState = new SleepState();
	//TimeTable.get();
	//EEPROM.clear(); 
	EEPROM.get(INIT_ADDR,TimeTable.init); EEPROM.get(LOGGING_FREQUENCY_ADDR,TimeTable.loggingFrequency);
    EEPROM.get(SAMPLING_RATE_ADDR,TimeTable.samplingRate); EEPROM.get(SAMPLING_DURATION_ADDR,TimeTable.samplingDuration);
    EEPROM.get(SAMPLING_PERIOD_ADDR,TimeTable.samplingPeriod); 
	if(TimeTable.init!='I'){
		TimeTable.init ='I';
		TimeTable.set(0.2, 0.3, 0.4, 1.0);
		//TimeTable.put();
		EEPROM.put(INIT_ADDR,TimeTable.init); EEPROM.put(LOGGING_FREQUENCY_ADDR,TimeTable.loggingFrequency);
    	EEPROM.put(SAMPLING_RATE_ADDR,TimeTable.samplingRate);EEPROM.put(SAMPLING_DURATION_ADDR,TimeTable.samplingDuration);
    	EEPROM.put(SAMPLING_PERIOD_ADDR,TimeTable.samplingPeriod);
	}
}

StateMachine::~StateMachine() {
	if(m_CurrentState) {delete m_CurrentState;}
}


////////////////////////////////////////////////////////////
// State Machine Methods
////////////////////////////////////////////////////////////

bool StateMachine::publish() {
	if (m_CurrentState)
		return m_CurrentState->publish(this);
	return false;
}
bool StateMachine::sleep() {
	if (m_CurrentState) {return m_CurrentState->sleep(this);}
	return false;
}
bool StateMachine::readSensors() {
	if (m_CurrentState) {return m_CurrentState->readSensors(this);}
	return false;
}
bool StateMachine::log() {
	if (m_CurrentState) {return m_CurrentState->log(this);}
	return false;
}
bool StateMachine::wakeup() {
	if (m_CurrentState) {return m_CurrentState->wakeup(this);}
	return false;
}
void StateMachine::setCurrentState(State* currentState) {
	if (m_CurrentState) {
		delete m_CurrentState;
		m_CurrentState = NULL;
	}
	m_CurrentState = currentState;
}
}























