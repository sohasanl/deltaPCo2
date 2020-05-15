
#include "State.h"


namespace deltaPCo2{
State::State() : SerialWriter(Serial){}
State::~State(){}
bool State::publish(Co2System* pCo2Sys) {
	serialPrintln("Can not Publish...");
	return false;
}
bool State::sleep(Co2System* pCo2Sys) {
	serialPrintln("Can not Sleep...");
	return false;
}
bool State::readSensors(Co2System* pCo2Sys) {
	serialPrintln("Can not Read Sensors...");
	return false;
}
bool State::log(Co2System* pCo2Sys) {
	serialPrintln("Can not log...");
	return false;
}
bool State::wakeup(Co2System* pCo2Sys) {
	serialWrite("Can not wakeup\n");
	return false;
}
}
