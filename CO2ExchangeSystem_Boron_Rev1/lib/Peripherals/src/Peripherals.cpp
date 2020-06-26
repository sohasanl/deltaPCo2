#include "Peripherals.h"

namespace deltaPCo2{

    Peripherals::Peripherals(USARTSerial& aUsartSerial, USBSerial& aUsbSerial)
    : serial(aUsartSerial), anActiveSerial(aUsbSerial), extSerial(Wire, 0){
        czr = new COZIR(aUsartSerial);
        if(!this->sd.begin(SD_CS_PIN)) {Serial.println(" SD init failed!");}
        sdout.open("logs.txt", ios_base::app);
        sht31d.begin(0x44);
        extSerial.begin(9600);
        //Wire.begin();
    }


    Peripherals::~Peripherals(){
        if(czr){delete czr;}
        if(sdout){sdout.close();}
    }


    void Peripherals::save(){
        sdout.close();
        sdout.open("logs.txt", ios_base::app); 
    }
/////////////////////////////////////////////////
// 
/////////////////////////////////////////////////

	void Peripherals::getCo2(T& aTimeTable){
        std::vector<int> co2List;
        int stateTime = millis();
        while(!((millis() - stateTime) >=  aTimeTable.samplingDuration * 60000))
        { 
            co2List.push_back(czr->CO2());
            delay((int)(aTimeTable.samplingRate * 60000));
            Serial.print(".");
        }
        std::sort(co2List.begin(), co2List.end());
        int indexofMedian = co2List.size()/2;
        aData.co2=co2List[indexofMedian];
    }


    void Peripherals::getHumidityAndTemp(){
        SHT31D_CC::SHT31D result= sht31d.readTempAndHumidityPolling(SHT31D_CC::REPEATABILITY_HIGH, 200);
        if (result.error == SHT31D_CC::NO_ERROR){
            aData.humidity =result.rh;
            aData.temperature=result.t;
        }
    }

    SensorsData Peripherals::getSensorsData(T& aTimeTable){
        Serial.println(" Getting Sensors Data....."); 
        Serial.print(" Sampling Co2 for "); Serial.print(TimeTable.samplingDuration); Serial.println(" minutes "); 
        Serial.print(" With sampling rate of ");Serial.print(TimeTable.samplingRate); Serial.println(" minutes.");
        getHumidityAndTemp();
        getCo2(aTimeTable);
        getGPS();
        return aData;
    }


    void Peripherals::getGPS(){
        if (!myGPS.begin()){
            Serial.println(F("UBlox Freezing, Please check wiring..."));
        }
        myGPS.setI2COutput(COM_TYPE_UBX); //Set the I2C port to output UBX only (turn off NMEA noise)
        myGPS.saveConfiguration(); //Save the current settings to flash and BBR
        int stateTime = millis();
        while(!((millis() - stateTime) >=  0.1 * 60000)){ 
            aData.latitude = myGPS.getLatitude();
            aData.longitude = myGPS.getLongitude();
        } 

    }


    /////////////////////////////////////////////////
	// 
	///////////////////////////////////////////////// 


    ostream& operator<<(ostream& os, const String& aString){
        os << aString.c_str();
        return os;
    }

    void Peripherals::writeSensorData(){
        sdout << aData.co2 << "," << aData.humidity << "," << aData.temperature
        << aData.longitude << "," << aData.latitude << "\n";
        save();
    }

    
}