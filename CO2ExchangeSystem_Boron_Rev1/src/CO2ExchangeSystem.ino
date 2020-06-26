#include "StateMachine.h"

STARTUP(setup_USBSerial());
SYSTEM_MODE(MANUAL);
SYSTEM_THREAD(ENABLED);

void setup_USBSerial(){
  Serial.begin(9600);
}

// Create an State Machine object.
deltaPCo2::StateMachine obj(Serial1, Serial);

void loop() {
  
  delay(5000);
  obj.wakeup();      // change the current state of the State Machine.
  obj.readSensors(); // will read Co2 and GPS data.
  obj.log();         // log data into SD card using JSON format.
  obj.publish();   // will publish sensors data to Particle cloud.
  obj.sleep();       // will sleep for (SamplingPeriod - SamplingRate) * 60  minutes

}

