#include "PublishState.h"

namespace deltaPCo2{

PublishState::PublishState(){}

PublishState::~PublishState(){}

bool PublishState::sleep(StateMachine* pCo2Sys) {
	T& aTimeTable= pCo2Sys->getTimeTable();
	pCo2Sys->setCurrentState(new SleepState());
	float secondsToSleep = (aTimeTable.samplingPeriod - aTimeTable.samplingDuration) * 60;
	Serial.print(" Going to sleep for "); Serial.print(secondsToSleep); Serial.println(" seconds...");
	System.sleep({}, {}, secondsToSleep);
	return true;
}


bool PublishState::readSensors(StateMachine* pCo2Sys) {
	SensorsData results=pCo2Sys->getSensorsData(pCo2Sys->getTimeTable());
	Serial.println("");
	Serial.print(" CO2         -> "); Serial.print(results.co2); Serial.println(" ppm...");
	Serial.print(" HUMIDITY    -> "); Serial.print(results.humidity); Serial.println(" %...");
	Serial.print(" TEMPERATURE -> "); Serial.print(results.temperature); Serial.println(" C...");
	Serial.print(" LONGITUDE   -> "); Serial.print(results.longitude); Serial.println(" (degrees * 10^-7)");
	Serial.print(" LATTITUDE   -> "); Serial.print(results.latitude); Serial.println(" (degrees * 10^-7)");
	return true;
}


bool PublishState::publish(StateMachine* pCo2Sys) {
	serialPrintln(" PUBLISHING   -> Done!");
	return true;
}


bool PublishState::log(StateMachine* pCo2Sys) {
	pCo2Sys->writeSensorData();
	serialPrintln("\n LOGGING   -> Done!");
	//Peripherals::sdout << "I'm Logging!";
	// pCo2Sys->sdout << "I'm Logging!";
	// pCo2Sys->save();
	return true;
}
}