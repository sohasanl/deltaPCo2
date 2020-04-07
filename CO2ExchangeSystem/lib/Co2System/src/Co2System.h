#pragma once
#include "libraries.h"

class State;

class Co2System {
	
public:
	Co2System(unsigned int sr, unsigned int sp, float lf);
	~Co2System();


	/////////////////////////////////////////////////
	// setters and getters
	/////////////////////////////////////////////////

	void setSamplingRate(unsigned int min);
	void setSamplingPeriod(unsigned int min);
	void setLoggingFrequency(float Hz);
	void setStateTime(unsigned long millsec);
	void setCo2Level(int aCo2);

	unsigned int getSamplingRate();
	unsigned int getSamplingPeriod();
	float getLoggingFrequency();
	unsigned long getStateTime();
	int getCo2Level();

    ////////////////////////////////////////////////
	// Methods to control and read/write prepherals
	////////////////////////////////////////////////

    bool initSdCard(char* fileName, uint8_t chipSelect, uint8_t cardDetect);
	void writeJson(char* fileName);
	static void serialReadToBuffer();
	int co2();
	int gps();



    /////////////////////////////////////////////////
	// State Machine Methods
	/////////////////////////////////////////////////
	void cmdStart();
	bool readSensors();
	bool publish();
	bool sleep();
	bool log();
	bool wakeup();
	void setCurrentState(State* currentState);

	//////////////////////////////////////////////////
	//////////////////////////////////////////////////
private:

	int co2Level;
	double longitude;
	double latitude;

	float loggingFrequency;
	unsigned long stateTime;
	unsigned int samplingRate;
	unsigned int samplingPeriod;


	SdFat* SD;
	COZIR* czr;
	Adafruit_GPS* GPS;
	State* m_CurrentState;
	Thread hardwareThread;
	
	enum Addr
    {
        SRATE      = 0,
        SPERIOD    = 1,
		LFREQUENCY = 2
    };




};
