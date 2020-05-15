#include "Peripherals.h"

namespace deltaPCo2{

    
    Peripherals::Peripherals(USARTSerial& aHardwareSerial){
        czr = new COZIR(aHardwareSerial);
    }
    Peripherals::~Peripherals(){
        if(czr){delete czr;}
    }

	int Peripherals::getCo2(){
        return czr->CO2();
    }

    
}