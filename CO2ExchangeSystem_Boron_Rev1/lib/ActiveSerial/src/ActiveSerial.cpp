#include "ActiveSerial.h"
namespace deltaPCo2{

StatusResult handleInput(istream &aStream, CommandProcessor &aProcessor) {
	deltaPCo2::Tokenizer theTokenizer(aStream);
	deltaPCo2::StatusResult theResult=theTokenizer.tokenize();
	while(theResult && theTokenizer.more()) {
		if(";"==theTokenizer.current().data) {
			theTokenizer.next();  //skip the ";"...
		}
		else theResult=aProcessor.processInput(theTokenizer);
	}
	return theResult;
}

ActiveSerial::ActiveSerial(USBSerial &aSerial)
: serial(aSerial), aCallbackFunc(handleInput) {start();}

ActiveSerial::ActiveSerial(USBSerial &aSerial, parseCallbackf& aCallback)
: serial(aSerial), aCallbackFunc(aCallback) {start();}

ActiveSerial::~ActiveSerial(){}


void ActiveSerial::showError(deltaPCo2::StatusResult &aResult) {
	std::string theMessage="Unknown Error";
	if(theErrorMessages.count(aResult.code)) {
		theMessage=theErrorMessages[aResult.code];
	}
	Serial.print("Error ("); Serial.print(aResult.code);
	Serial.print(") "); Serial.println(theMessage.c_str());
}




void ActiveSerial::serialToBuffer(parseCallbackf aCallback) {
    StatusResult theResult{noError};
    serialCommandBuffer = "\0";
    while (true)
    {
        WITH_LOCK(serial) {
            if (serial.available() > 0) {                  //Device responded
                char inchar = (char)serial.read();         //get the char we just received
                serialCommandBuffer += inchar;             //add the char to the var called sensorstring
                if (inchar == '\r') {                      //if the incoming character is a <CR> end of message
                    ibufstream theStream(serialCommandBuffer);
                    theResult = (*aCallback)(theStream, theAppProcessor);
                    if(!theResult) {showError(theResult);} 
                    serialCommandBuffer = "\0";
                }
            }
        }
        HAL_Delay_Milliseconds(10);
    }
}


void ActiveSerial::start() {    // must pass "this" inside the capture list
    SYSTEM_THREAD(ENABLED);
    std::function<void()> runCMD = [this]() { serialToBuffer(aCallbackFunc); };
    hardwareThread = Thread("CommandBuffer", runCMD, OS_THREAD_PRIORITY_DEFAULT + 1);
}
}