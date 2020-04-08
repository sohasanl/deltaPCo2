#include "Co2System.h"
#include "SleepState.h"
#include "PublishState.h"
#include "Serial4/Serial4.h"

static String serialCommandBuffer;
static SimpleCLI cli;
static bool initialized = false;

float Timing::loggingFrequency;
unsigned long Timing::stateTime;
unsigned int Timing::samplingRate;
unsigned int Timing::samplingPeriod;


static void cmdProcessor(String buffer);
static void errorCallback(cmd_error* e);
static void srateCallback(cmd* c);
static void speriodCallback(cmd* c); 
static void lfreqCallback(cmd* c); 

Co2System::Co2System(unsigned int sr, unsigned int sp, float lf){
	SYSTEM_THREAD(ENABLED);
	T.stateTime = 0;
	T.samplingRate = sr;
	T.samplingPeriod = sp; 
	T.loggingFrequency = lf; 

	m_CurrentState = new PublishState();
	czr = new COZIR(Serial1);
	SD = new SdFat();
	co2Level = 0;
}

Co2System::~Co2System() {

}
/////////////////////////////////////////////////////////////
// getters and setters
/////////////////////////////////////////////////////////////

void Co2System::setCo2Level(int aCo2){
	co2Level = aCo2;
}

int Co2System::getCo2Level(){
	return co2Level;	
}
////////////////////////////////////////////////////////////
// State Machine Methods
////////////////////////////////////////////////////////////

bool Co2System::publish() {
	if (m_CurrentState)
		return m_CurrentState->publish(this);
	return false;
}
bool Co2System::sleep() {
	if (m_CurrentState)
		return m_CurrentState->sleep(this);
	return false;
}
bool Co2System::readSensors() {
	if (m_CurrentState)
		return m_CurrentState->readSensors(this);
	return false;
}
bool Co2System::log() {
	if (m_CurrentState)
		return m_CurrentState->log(this);
	return false;
}
bool Co2System::wakeup() {
	if (m_CurrentState)
		return m_CurrentState->wakeup(this);
	return false;
}
void Co2System::setCurrentState(State* currentState) {
	if (m_CurrentState) {
		delete m_CurrentState;
		m_CurrentState = NULL;
	}
	m_CurrentState = currentState;
}
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
int Co2System::gps(){

	return 0;
}
int Co2System::co2(){
	co2Level = czr->CO2();
	return co2Level;
}


bool Co2System::initSdCard(char* fileName, uint8_t chipSelect, uint8_t cardDetect)
{
	// Is there even a card?
	if (!digitalRead(cardDetect))
	{
		Serial.print(F("No card detected. Waiting for card."));
		delay(1000);
		return false;
	}
	// Card seems to exist.  begin() returns failure
	// even if it worked if it's not the first call.
	if (!SD->begin(chipSelect, SPI_FULL_SPEED))  
	{
		Serial.print(F("SD Initialization failed!\n"));
		delay(1000);
		return false;
	}
	return true;
}


void Co2System::writeJson(char* fileName){
  File fd;
  DynamicJsonDocument  doc(200);
  doc["sensor"] = "Co2";
  doc["time"] = Time.format(Time.now(), "%Y-%m-%d %H:%M:%S");
  JsonArray data = doc.createNestedArray("data");
  data.add(co2Level);
  fd = SD->open(fileName, O_RDWR | O_CREAT | O_AT_END);
  delay(1);
    if (fd)
  {
    serializeJson(doc, fd); fd.close();
  }
  
}
//////////////////////////////////////////////////////////////
// Command Line Interface
//////////////////////////////////////////////////////////////

// Start the thread for receiving the commands from the USBSerial port.

void Co2System::cmdStart(){

   hardwareThread = Thread("CommandBuffer", serialReadToBuffer, OS_THREAD_PRIORITY_DEFAULT + 1);
}


// the actual thread function responsible fo receiving the commands.
void Co2System::serialReadToBuffer() {
	serialCommandBuffer="\0";
    while(true)
      {
        if (Serial.available() > 0) {              //Device responded
        char inchar = (char)Serial.read();         //get the char we just received
        serialCommandBuffer += inchar;             //add the char to the var called sensorstring
        if (inchar == '\r') {                      //if the incoming character is a <CR> end of message
		  cmdProcessor(serialCommandBuffer);
		  serialCommandBuffer = "\0";
        }
      }
        HAL_Delay_Milliseconds(10);
      }
    }


// this function will define the commands and deligate the input command string to the CLI parser.

static void cmdProcessor(String buffer){
	if (!initialized) {
  		initialized = true;
		cli.setOnError(errorCallback); // Set error Callback
	
		Command srate = cli.addCommand("srate", srateCallback);
    	srate.addArgument("v");
		Command speriod = cli.addCommand("speriod", speriodCallback);
    	speriod.addArgument("v");
		Command lfreq = cli.addCommand("lfreq", lfreqCallback);
    	lfreq.addArgument("v");
	}
	cli.parse(buffer);
	if (cli.errored()) {
        CommandError cmdError = cli.getError();

        Serial.print("ERROR: ");
        Serial.println(cmdError.toString());
        if (cmdError.hasCommand()) {
            Serial.print("Did you mean \"");
            Serial.print(cmdError.getCommand().toString());
            Serial.println("\"?");
        }
    }
}


 static void speriodCallback(cmd* c) {
	Timing t;
    Command cmd(c); // Create wrapper object

	Argument inputArg = cmd.getArgument("v");
	int argValue = inputArg.getValue().toInt();
	t.samplingPeriod = argValue;
	Serial.print("Sampling Period = "); 
	Serial.print(t.samplingPeriod);
	Serial.println("   Ok!");
		
	}


 static void srateCallback(cmd* c) {
	Timing t;
    Command cmd(c); // Create wrapper object

	Argument inputArg = cmd.getArgument("v");
	int argValue = inputArg.getValue().toInt();
	t.samplingRate = argValue;
	Serial.print("Sampling Rate = ");
	Serial.print(t.samplingRate);
	Serial.println("   Ok!");	
	}



 static void lfreqCallback(cmd* c) {
	Timing t;
    Command cmd(c); // Create wrapper object
	Argument inputArg = cmd.getArgument("v");
	int argValue = inputArg.getValue().toFloat();
	t.loggingFrequency = argValue;
	Serial.print("Logging Frequency = ");
	Serial.print(t.loggingFrequency);
	Serial.println("   Ok!");	
	}





static void errorCallback(cmd_error* e) {
    CommandError cmdError(e); // Create wrapper object
    Serial.print("ERROR: ");
    Serial.println(cmdError.toString());

    if (cmdError.hasCommand()) {
        Serial.print("Did you mean \"");
        Serial.print(cmdError.getCommand().toString());
        Serial.println("\"?");
    }
}






















