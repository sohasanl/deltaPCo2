/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/Users/Omid/Desktop/CozirProject/CozirApp/CO2ExchangeSystem-Boron/src/CO2ExchangeSystem.ino"
#include "Co2System.h"

void setup_USBSerial();
void setup();
void loop();
#line 3 "c:/Users/Omid/Desktop/CozirProject/CozirApp/CO2ExchangeSystem-Boron/src/CO2ExchangeSystem.ino"
STARTUP(setup_USBSerial());
SYSTEM_MODE(MANUAL);

void setup_USBSerial(){
  Serial.begin(9600);
}

// default values for Sampling Period = 30; Sampling Duration=5; Sampling Rate=1; Logging Frequency=0.5
// to change these values deltaPCo2::Co2System obj(Serial, 30, 5, 1, 0.5);
//deltaPCo2::Co2System obj(Serial); // Create an State Machine object.


deltaPCo2::Co2System obj(Serial, 10, 5, 0.5, 0.5);

// setup() runs once, when the device is first turned on.
void setup() {

}

// loop() runs over and over again, as quickly as it can execute.
void loop() {

  obj.wakeup();      // change the current state of the State Machine.
  obj.readSensors(); // will read Co2 and GPS data.
  obj.log();         // log data into SD card using JSON format.
  obj.publish();   // will publish sensors data to Particle cloud.
  obj.sleep();       // will sleep for (SamplingPeriod - SamplingRate) * 60  minutes
  
}

