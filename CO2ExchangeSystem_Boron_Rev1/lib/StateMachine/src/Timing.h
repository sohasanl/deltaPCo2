#pragma once

namespace deltaPCo2{

#define TIMETABLE_ADDR 0
#define INIT_ADDR 0
#define LOGGING_FREQUENCY_ADDR 2
#define SAMPLING_RATE_ADDR     6
#define SAMPLING_DURATION_ADDR 10
#define SAMPLING_PERIOD_ADDR   14

struct T{
    char         init;
    float        loggingFrequency; //mins
    float        samplingRate; //mins
    float        samplingDuration; //mins
    float        samplingPeriod; //mins

    T(){}

    T(float lf, float sr, float sd, float sp)
    : loggingFrequency(lf), samplingRate(sr), samplingDuration(sd), samplingPeriod(sp){}

    void set(float lf, float sr, float sd, float sp){
        loggingFrequency=lf;
        samplingRate=sr;
        samplingDuration=sd;
        samplingPeriod=sp;
    }
    // void setLoggingFrequency(float lf){
    //     loggingFrequency=lf;
    //     EEPROM.put(LOGGING_FREQUENCY_ADDR,loggingFrequency);
    // }
    // void setSamplingRate(float sr){
    //     samplingRate=sr;
    //     EEPROM.put(SAMPLING_RATE_ADDR,samplingRate);
    // }
    // void setSamplingDuration(float sd){
    //     samplingDuration=sd;
    //     EEPROM.put(SAMPLING_DURATION_ADDR,samplingDuration);
    // }
    // void setSamplingPeriod(float sp){
    //     samplingPeriod=sp;
    //     EEPROM.put(SAMPLING_PERIOD_ADDR,samplingPeriod); 
    // }

    // float getLoggingFrequency(){
    //     EEPROM.get(LOGGING_FREQUENCY_ADDR,loggingFrequency);
    //     return loggingFrequency;
    // }
    // float getSamplingRate(){
    //     EEPROM.get(SAMPLING_RATE_ADDR,samplingRate);
    //     return samplingRate;
    // }
    // float getSamplingDuration(){
    //     EEPROM.get(SAMPLING_DURATION_ADDR,samplingDuration);
    //     return samplingDuration;
    // }
    // float getSamplingPeriod(){
    //     EEPROM.get(SAMPLING_PERIOD_ADDR,samplingPeriod);
    //     return  samplingPeriod;
    // }

    // void put(){
    //     EEPROM.put(LOGGING_FREQUENCY_ADDR,loggingFrequency);
    //     EEPROM.put(SAMPLING_RATE_ADDR,samplingRate);
    //     EEPROM.put(SAMPLING_DURATION_ADDR,samplingDuration);
    //     EEPROM.put(SAMPLING_PERIOD_ADDR,samplingPeriod);  
    // }
    // void get(){
    //     EEPROM.get(LOGGING_FREQUENCY_ADDR,loggingFrequency);
    //     EEPROM.get(SAMPLING_RATE_ADDR,samplingRate);
    //     EEPROM.get(SAMPLING_DURATION_ADDR,samplingDuration);
    //     EEPROM.get(SAMPLING_PERIOD_ADDR,samplingPeriod);  
    // }

    // void dump(){
    //     Serial.print("Init byte is: "); Serial.println(init);
    //     Serial.print("LoggingFrequency is: "); Serial.println(loggingFrequency);
    //     Serial.print("samplingRate is: "); Serial.println(samplingRate);
    //     Serial.print("samplingDuration is: "); Serial.println(samplingDuration);
    //     Serial.print("samplingPeriod is: "); Serial.println(samplingPeriod);
    // }


};

extern T TimeTable;

}