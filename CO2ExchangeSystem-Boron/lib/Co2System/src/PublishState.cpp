#include "PublishState.h"

namespace deltaPCo2{

PublishState::PublishState(){}

PublishState::~PublishState(){}

bool PublishState::sleep(Co2System* pCo2Sys) {
	//transition to sleep state
	pCo2Sys->setCurrentState(new SleepState());
	//int secondsToSleep = (pCo2Sys->T.samplingPeriod - pCo2Sys->T.samplingDuration) * 60;
	System.sleep(SLEEP_MODE_DEEP/*, secondsToSleep*/);

	return true;
}
bool PublishState::readSensors(Co2System* pCo2Sys) {
	std::vector<int> co2List;
	int stateTime = millis();
	Serial.println((int)(pCo2Sys->T.samplingRate * 60000));
    while(!((millis() - stateTime) >=  pCo2Sys->T.samplingDuration * 60000))
    { 
		co2List.push_back(pCo2Sys->getCo2());
		Serial.print(".");
		delay((int)(pCo2Sys->T.samplingRate * 60000));	
	}
	std::sort(co2List.begin(), co2List.end());
	int indexofMedian = co2List.size()/2;
 	serialPrint<String>(" CO2 -> "); serialPrintln<int>(co2List[indexofMedian]);
	return true;
}


bool PublishState::publish(Co2System* pCo2Sys) {
	serialPrint<String>(Time.format(TIME_FORMAT_ISO8601_FULL));
	serialPrintln(" -> Published...");
	return true;
}


bool PublishState::log(Co2System* pCo2Sys) {
	serialPrint<String>(Time.format(TIME_FORMAT_ISO8601_FULL));
	serialPrintln(" -> logging done...");
	return true;
}
}