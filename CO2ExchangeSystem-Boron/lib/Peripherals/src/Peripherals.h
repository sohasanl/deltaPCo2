#pragma once
#include "Particle.h"
#include "Cozir.h"

 
namespace deltaPCo2{

class Peripherals{
public:

    Peripherals(USARTSerial& aHardwareSerial);
    ~Peripherals();

	int getCo2();

    protected:

    COZIR* czr; 
    };
}