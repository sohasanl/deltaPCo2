#pragma once
#include "application.h"

namespace deltaPCo2{
class SerialWriter{
public:
    SerialWriter(USBSerial&  aSerial): serial(aSerial){}
    ~SerialWriter(){}

    template <typename T>
    void serialWrite(T aT){
	    WITH_LOCK(serial) {serial.write(aT);}
    }

    template <typename T>
    void serialPrint(T aT){
	    WITH_LOCK(serial) {serial.print(aT);}
    }

    template <typename T>
    void serialPrintln(T aT){
	    WITH_LOCK(serial) {serial.println(aT);}
    }
private:
    USBSerial&   serial;
};
}