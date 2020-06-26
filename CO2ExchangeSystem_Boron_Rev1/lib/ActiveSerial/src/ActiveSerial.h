#pragma once

#include "Tokenizer.h"
#include "Errors.h"
#include "CommandProcessor.h"
#include "AppStatement.h"
#include "AppProcessor.h"
#include "SdFat.h"
#include "Timing.h"


#include <functional>
#include <Particle.h>

namespace deltaPCo2{

static String serialCommandBuffer;
using parseCallbackf = deltaPCo2::StatusResult(istream &aStream, deltaPCo2::CommandProcessor &aProcessor);

class ActiveSerial {
    std::map<int, std::string> theErrorMessages = {
		{deltaPCo2::illegalIdentifier, "Illegal identifier"},
		{deltaPCo2::unknownIdentifier, "Unknown identifier"},
		{deltaPCo2::syntaxError, "Syntax Error"},
		{deltaPCo2::unknownCommand, "Unknown command"},
		{deltaPCo2::unknownError,   "Unknown error"},
	};
public:
    // the actual thread function responsible fo receiving the commands.
    ActiveSerial(USBSerial& aSerial);
    ActiveSerial(USBSerial& aSerial, parseCallbackf& aCallback);
    ~ActiveSerial();
    void showError(deltaPCo2::StatusResult &aResult);

protected:
    void serialToBuffer(parseCallbackf aCallback);
    void start();


    Thread hardwareThread;
    USBSerial& serial;
    parseCallbackf& aCallbackFunc;
    deltaPCo2::AppProcessor  theAppProcessor;
};
}