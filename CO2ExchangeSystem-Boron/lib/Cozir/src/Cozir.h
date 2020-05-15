// 
//       FILE: Cozir.h
//     AUTHOR: Rob Tillaart & Michael Hawthorne
//    VERSION: 0.1.01
//    PURPOSE: library for COZIR range of sensors for Arduino
//        URL: http://www.cozir.com/
//  DATASHEET: http://www.co2meters.com/Documentation/Datasheets/COZIR-Data-Sheet-RevC.pdf
// USER GUIDE: http://www.co2meters.com/Documentation/Manuals/COZIR-Software-User-Guide-AL12-RevA.pdf
// READ DATASHEET BEFORE USE OF THIS LIB !
//
// Released to the public domain
//

#ifndef Cozir_h
#define Cozir_h


#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#define COZIR_LIB_VERSION 0.1.01

// OUTPUTFIELDS 
// See datasheet for details.
// These defines can be OR-ed for the SetOutputFields command
#define CZR_LIGHT 			0x2000
#define CZR_HUMIDITY		0x1000
#define CZR_FILTLED			0x0800
#define CZR_RAWLED			0x0400
#define CZR_MAXLED			0x0200
#define CZR_ZEROPOINT		0x0100
#define CZR_RAWTEMP			0x0080
#define CZR_FILTTEMP		0x0040
#define CZR_FILTLEDSIGNAL	0x0020
#define CZR_RAWLEDSIGNAL	0x0010
#define CZR_SENSTEMP		0x0008
#define CZR_FILTCO2			0x0004
#define CZR_RAWCO2			0x0002
#define CZR_NONE			0x0001

// easy default setting for streaming
#define CZR_HTC			(CZR_HUMIDITY | CZR_RAWTEMP | CZR_RAWCO2)
// not in datasheet for debug only
#define CZR_ALL				0x3FFF  

// OPERATING MODES
#define CZR_COMMAND			0x00
#define CZR_STREAMING		0x01
#define CZR_POLLING			0x02

class COZIR
{
  public:
	COZIR(USARTSerial&);// : CZR_Serial(nss)
	
	void SetOperatingMode(uint8_t mode);
		
	float Celsius();
	float Fahrenheit();
	float Humidity();
	float Light();
	uint16_t CO2();

	uint16_t FineTuneZeroPoint(uint16_t , uint16_t);
	uint16_t CalibrateFreshAir();
	uint16_t CalibrateNitrogen();
	uint16_t CalibrateKnownGas(uint16_t );
	uint16_t CalibrateManual(uint16_t );
	uint16_t SetSpanCalibrate(uint16_t );
	uint16_t GetSpanCalibrate();
		
	void SetDigiFilter(uint8_t );
	uint8_t GetDigiFilter();
	
	void SetOutputFields(uint16_t );
	void GetRecentFields();
	
	void SetEEPROM(uint8_t , uint8_t );
	uint8_t GetEEPROM(uint8_t );
	
	void GetVersionSerial();
	void GetConfiguration();
  
  private:
    USARTSerial& CZR_Serial;
    char buffer[20];
	void Command(char* );
	uint16_t Request(char* );
};

#endif
