#include "PublishState.h"

bool PublishState::sleep(Co2System* pCo2Sys) {
	pCo2Sys->setCurrentState(new SleepState());
	Serial.print("going to sleep\n");
	System.sleep(SLEEP_MODE_DEEP, (pCo2Sys->T.samplingPeriod - pCo2Sys->T.samplingRate) * 60);
	return true;
}
bool PublishState::readSensors(Co2System* pCo2Sys) {
	Serial.print(Time.format(TIME_FORMAT_ISO8601_FULL));
 	Serial.print("-> CO2 : ");Serial.println(pCo2Sys->co2());
	return true;
}
bool PublishState::publish(Co2System* pCo2Sys) {
	Serial.print("Publish\n");
	bool isMaxTime = false;
	pCo2Sys->T.stateTime = millis();
	
	while(!isMaxTime)
    {
      //connect particle to the cloud
      if (Particle.connected() == false)
      {
        Particle.connect();
      }
	  // If connected, publish data buffer
      if (Particle.connected())
      {
        Serial.println("publishing data");
        Particle.publish("deltaPCo2", (char*)pCo2Sys->getCo2Level() , 60, PRIVATE);

        // Wait for the publish data
        delay(4000);
        isMaxTime = true;
	  }
	  else
      {
        // Took too long to publish, just go to sleep
        if ((millis() - pCo2Sys->T.stateTime) >= 4000)
        {
          isMaxTime = true;
          Serial.println("max time for pulishing reach");
        }
        Serial.println("Not max time, try again to publish");
      }
	}
	return true;
}
bool PublishState::log(Co2System* pCo2Sys) {
    char fileName[] = "Log.txt"; // SD library only supports up to 8.3 names
    while(!pCo2Sys->initSdCard(fileName, A2, A0));
	pCo2Sys->writeJson(fileName);
	Serial.print("logging done!\n");
	return true;
}