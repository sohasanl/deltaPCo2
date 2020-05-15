#pragma once

#include <functional>
#include <Particle.h>
namespace deltaPCo2{
static String serialCommandBuffer;
using parseCallback = void(USBSerial &aSerial, String buffer);

class ActiveSerial {
public:
    // the actual thread function responsible fo receiving the commands.

    ActiveSerial(USBSerial& aSerial);
    ActiveSerial(USBSerial& aSerial, parseCallback& aCallback);

    ~ActiveSerial();

protected:
    void serialToBuffer(parseCallback aCallback);
    void start();


    Thread hardwareThread;
    USBSerial& serial;
    parseCallback& aCallbackFunc;

};
}