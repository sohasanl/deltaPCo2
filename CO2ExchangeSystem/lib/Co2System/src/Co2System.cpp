#include "Co2System.h"
#include "SleepState.h"
#include "PublishState.h"
#include "Serial4/Serial4.h"

Co2System::Co2System(unsigned int sr, unsigned int sp, float lf){

	SYSTEM_THREAD(ENABLED);

	stateTime = 0;
	samplingRate = sr;
	samplingPeriod = sp; 
	loggingFrequency = lf; 
	m_CurrentState = new PublishState();
	czr = new COZIR(Serial1);
	SD = new SdFat();
	co2Level = 0;

	GPS = new Adafruit_GPS(&Serial4);
	GPS->begin(9600);
	GPS->sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
	GPS->sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
	GPS->sendCommand(PGCMD_ANTENNA);
}

Co2System::~Co2System() {

}
//////////////////////////////////////////
// getters and setters
//////////////////////////////////////////
void Co2System::setSamplingRate(unsigned int min){
	samplingRate = min;
}
void Co2System::setSamplingPeriod(unsigned int min) {
	samplingPeriod = min;
}
void Co2System::setLoggingFrequency(float Hz) {
	loggingFrequency = Hz;
}
void Co2System::setStateTime(unsigned long millsec){
	stateTime = millsec;
}
void Co2System::setCo2Level(int aCo2){
	co2Level = aCo2;
}

unsigned int Co2System::getSamplingRate() {
	return samplingRate;
}
unsigned int Co2System::getSamplingPeriod() {
	return samplingPeriod;
}
float Co2System::getLoggingFrequency() {
	return loggingFrequency;
}
unsigned long Co2System::getStateTime(){
	return stateTime;
}
int Co2System::getCo2Level(){
	return co2Level;	
}
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

void Co2System::cmdStart(){

   hardwareThread = Thread("CommandBuffer", serialReadToBuffer, OS_THREAD_PRIORITY_DEFAULT + 1);
}

bool Co2System::initSdCard(char* fileName, uint8_t chipSelect, uint8_t cardDetect)
{
	// Is there even a card?
	if (!digitalRead(cardDetect))
	{
		Serial.print(F("No card detected. Waiting for card."));
		delay(250);
		return false;
	}
	// Card seems to exist.  begin() returns failure
	// even if it worked if it's not the first call.
	if (!SD->begin(chipSelect, SPI_FULL_SPEED))  
	{
		Serial.print(F("SD Initialization failed!\n"));
		delay(250);
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
    serializeJson(doc, fd);
    fd.close();
  }
  
}

void Co2System::serialReadToBuffer() {
	String serialCommandBuffer="";
    while(true)
      {
        if (Serial.available() > 0) {              //Device responded
        char inchar = (char)Serial.read();         //get the char we just received
        serialCommandBuffer += inchar;                     //add the char to the var called sensorstring
        if (inchar == '\r') {                      //if the incoming character is a <CR> end of message
          Serial.println(serialCommandBuffer);
		  serialCommandBuffer = "\0";
        }
      }
        HAL_Delay_Milliseconds(10);
      }

    
    }
int Co2System::gps(){

	return 0;
}
int Co2System::co2(){
	co2Level = czr->CO2();
	return co2Level;
}
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





















