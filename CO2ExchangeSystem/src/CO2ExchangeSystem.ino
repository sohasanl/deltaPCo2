#include "Co2System.h"

STARTUP(setup_USBSerial());
SYSTEM_MODE(MANUAL);



void setup_USBSerial(){
  Serial.begin(9600);
}
Co2System obj(1,2,0.5); // Creat an State Machine object.

// setup() runs once, when the device is first turned on.
void setup() {
  // Put initialization like pinMode and begin functions here.
  //obj.setSamplingRate(1);
  //obj.setSamplingPeriod(2);
  //obj.setLoggingFrequency(0.5);
  obj.cmdStart(); // will run Serial CLI thread 
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {

  obj.readSensors(); // will read Co2 and GPS data.
  obj.log();         // log data into SD card using JSON format.
  //obj.publish();   // will publish sensors data to Particle cloud.
  obj.sleep();       // will sleep for (SamplingPeriod - SamplingRate) * 60  minutes
  obj.wakeup();      // change the current state of the State Machine.

}

