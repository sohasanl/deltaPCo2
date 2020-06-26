
#include "State.h"


namespace deltaPCo2{
State::State() : SerialWriter(Serial){}
State::~State(){}
bool State::publish(StateMachine* pCo2Sys) {
	serialPrintln("Can not Publish...");
	return false;
}
bool State::sleep(StateMachine* pCo2Sys) {
	serialPrintln("Can not Sleep...");
	return false;
}
bool State::readSensors(StateMachine* pCo2Sys) {
	serialPrintln("Can not Read Sensors...");
	return false;
}
bool State::log(StateMachine* pCo2Sys) {
	serialPrintln("Can not log...");
	return false;
}
bool State::wakeup(StateMachine* pCo2Sys) {
	serialWrite("Can not wakeup\n");
	return false;
}
}
