#pragma once


#include "Errors.h"
#include "SdFat.h"
#include "ActiveSerial.h"

#include "Particle.h"
#include "Cozir.h"
#include "Timing.h"
#include "JsonParserGeneratorRK.h"
#include "ClosedCube_SHT31D.h"
#include "SparkFun_Ublox_Arduino_Library.h"
#include "SC16IS740RK.h"
//#include "Adafruit_GPS.h"



#include <vector>
#include <algorithm>
#include <Wire.h>


 
namespace deltaPCo2{


struct SensorsData{
	float humidity;
	float temperature;
	int co2;
	long latitude;
	long longitude;
};

#define SD_CS_PIN SS

class PublishState;

class Peripherals {

public:
    Peripherals(USARTSerial& aUsartSerial, USBSerial& aUsbSerial);
    ~Peripherals();
    friend ostream& operator<<(ostream& os, const String aString);

    /////////////////////////////////////////////////
	// Methods
	///////////////////////////////////////////////// 

	SensorsData getSensorsData(T& aTimeTable);
	void writeSensorData();
    void save();
	void getCo2(T& aTimeTable);
	void getHumidityAndTemp();
	void getGPS();

    /////////////////////////////////////////////////
	// 
	///////////////////////////////////////////////// 

    
    friend class PublishState;
    friend class AppProcessor;

 protected:
    USARTSerial& serial;
    COZIR* czr;
    SdFat sd;
    ofstream sdout;
	SensorsData aData;
	SHT31D_CC::ClosedCube_SHT31D sht31d;
    ActiveSerial  anActiveSerial;
	SC16IS740 extSerial;
	SFE_UBLOX_GPS myGPS;
    };
}