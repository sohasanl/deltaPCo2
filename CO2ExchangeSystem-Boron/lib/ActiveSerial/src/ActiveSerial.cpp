#include "ActiveSerial.h"
namespace deltaPCo2{


static void cmdProcessor(USBSerial &aSerial, String buffer) {
    WITH_LOCK(aSerial){ aSerial.write(buffer); aSerial.write("\n");}
}

//USE: ctor---------------------------------------------------------------------------
ActiveSerial::ActiveSerial(USBSerial &aSerial)
: serial(aSerial), aCallbackFunc(cmdProcessor) {start();}

ActiveSerial::ActiveSerial(USBSerial &aSerial, parseCallback& aCallback)
: serial(aSerial), aCallbackFunc(aCallback) {start();}

ActiveSerial::~ActiveSerial(){}



void ActiveSerial::serialToBuffer(parseCallback aCallback) {
    serialCommandBuffer = "\0";
    while (true)
    {
        WITH_LOCK(serial) {
            if (serial.available() > 0) {                  //Device responded
                char inchar = (char)serial.read();         //get the char we just received
                serialCommandBuffer += inchar;             //add the char to the var called sensorstring
                if (inchar == '\r') {                      //if the incoming character is a <CR> end of message
                    (*aCallback)(serial, serialCommandBuffer);
                    serialCommandBuffer = "\0";
                }
            }
        }
        HAL_Delay_Milliseconds(10);
    }
}


void ActiveSerial::start() {
    // must pass "this" inside the capture list
    std::function<void()> runCMD = [this]() { serialToBuffer(aCallbackFunc); };
    hardwareThread = Thread("CommandBuffer", runCMD, OS_THREAD_PRIORITY_DEFAULT + 1);
}
}