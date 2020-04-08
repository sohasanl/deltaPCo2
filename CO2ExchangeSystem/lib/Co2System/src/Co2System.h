#pragma once
#include "libraries.h"

class State;
class Co2System {
	
public:
	Co2System(unsigned int sr, unsigned int sp, float lf);
	~Co2System();

	//////////////////////////////////////////
	// getters and setters
	//////////////////////////////////////////
	void setCo2Level(int aCo2);
	int getCo2Level();
		
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
	
	 ////////////////////////////////////////////////
	// Methods to control and read/write prepherals
	////////////////////////////////////////////////
	int co2();
	int gps();
    bool initSdCard(char* fileName, uint8_t chipSelect, uint8_t cardDetect);
	void writeJson(char* fileName);
	static void serialReadToBuffer();

	Timing T;

private:

	int co2Level;
	double longitude;
	double latitude;


	SdFat* SD;
	COZIR* czr;
	//SimpleCLI cli;
	Adafruit_GPS* GPS;
	//SimpleCLI cli;
	State* m_CurrentState;
	Thread hardwareThread;
	enum Addr
    {
        SRATE      = 0,
        SPERIOD    = 1,
		LFREQUENCY = 2
    };




};
