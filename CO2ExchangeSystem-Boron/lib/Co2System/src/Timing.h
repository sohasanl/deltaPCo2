#pragma once
namespace deltaPCo2{
struct Timing{
    Timing(unsigned int sp, unsigned int sd, float sr, float lf)
    : loggingFrequency(lf), samplingRate(sr) , samplingDuration(sd), samplingPeriod(sp){}
    float        loggingFrequency ; //mins
    float        samplingRate; //mins
    unsigned int samplingDuration; //mins
    unsigned int samplingPeriod; //mins
    };



}