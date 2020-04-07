
#include "State.h"

State::~State(){

}
bool State::publish(Co2System* pCo2Sys) {
	Serial.print("Can not Publish\n");
	return false;
}
bool State::sleep(Co2System* pCo2Sys) {
	Serial.print("Can not Sleep\n");
	return false;
}
bool State::readSensors(Co2System* pCo2Sys) {
	Serial.print("Can not Read Sensors\n");
	return false;
}
bool State::log(Co2System* pCo2Sys) {
	Serial.print("Can not log\n");
	return false;
}
bool State::wakeup(Co2System* pCo2Sys) {
	Serial.print("Can not wakeup\n");
	return false;
}
