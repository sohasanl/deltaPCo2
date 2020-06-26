//
//  CommandProcessor.cpp
//
//  Created by Omid Hasanli on 4/30/20.
//  Copyright © 2020 Omid Hasanli. All rights reserved.
#include "AppProcessor.h"
#include "AppStatement.h"
#include "Tokenizer.h"
#include "Helpers.h"


namespace deltaPCo2{

    using StatementFactory = Statement* (*)(AppProcessor &aProcessor);

    Statement* samplingStatementFactory(AppProcessor &aProcessor){
        return new SamplingStatement(aProcessor);
    }

    Statement* loggingStatementFactory(AppProcessor &aProcessor){
        return new loggingStatement(aProcessor);
    }


    Statement* timetableStatementFactory(AppProcessor &aProcessor){
        return new timetableStatement(aProcessor);
    }

    AppProcessor::AppProcessor(CommandProcessor *aNext)
    : CommandProcessor(aNext){
    }

    AppProcessor::~AppProcessor() {}

    Statement* AppProcessor::getStatement(Tokenizer &aTokenizer) {
    static std::map<Keywords, StatementFactory> factories = {
        {Keywords::sampling_kw,   samplingStatementFactory},
        {Keywords::logging_kw,    loggingStatementFactory}, 
        {Keywords::timetable_kw,  timetableStatementFactory}, 
    };
    if(aTokenizer.size()){
        Token &theToken=aTokenizer.current();
        if(factories.count(theToken.keyword)){
            if(Statement *theStatement = factories[theToken.keyword](*this)){
                if(StatusResult theResult=theStatement->parse(aTokenizer)){
                    return theStatement;
                }
            }
        }
    }
    return nullptr;
}

// USE: -----------------------------------------------------
StatusResult AppProcessor::interpret(const Statement &aStatement) {//ok
    obufstream aStream;
    return aStatement.run(aStream);
}

StatusResult AppProcessor::samplingCommand(const SamplingCommands& parameters){
    for (std::map<Keywords, float>::const_iterator it = parameters.begin(); it!=parameters.end(); ++it){
        switch (it->first)
        {
        case Keywords::period_kw:
            //TimeTable.setSamplingPeriod(it->second);
            TimeTable.samplingPeriod=it->second;
            EEPROM.put(SAMPLING_PERIOD_ADDR,TimeTable.samplingPeriod); 
            Serial.print(" Sampling period was set to "); Serial.print(TimeTable.samplingPeriod); Serial.println(" minutes");
            break;
        case Keywords::duration_kw:
            //TimeTable.setSamplingDuration(it->second);
            TimeTable.samplingDuration=it->second;
            EEPROM.put(SAMPLING_DURATION_ADDR,TimeTable.samplingDuration); 
            Serial.print(" Sampling duration was set to "); Serial.print(TimeTable.samplingDuration); Serial.println(" minutes");
            break;
        case Keywords::rate_kw:
            //TimeTable.setSamplingRate(it->second);
            TimeTable.samplingRate=it->second;
            EEPROM.put(SAMPLING_RATE_ADDR,TimeTable.samplingRate);
            Serial.print(" Sampling rate was set to "); Serial.print(TimeTable.samplingRate); Serial.println(" minutes");
            break;
        }
    }

    return StatusResult{noError};
}
StatusResult AppProcessor::loggingCommand(const float mins){
    Serial.print(" Logging frequency was set to "); 
    TimeTable.loggingFrequency=mins;
    EEPROM.put(LOGGING_FREQUENCY_ADDR,TimeTable.loggingFrequency);
    Serial.print(TimeTable.loggingFrequency); Serial.println(" minutes!");
    return StatusResult{noError};
}


StatusResult AppProcessor::timetableCommand(){
    Serial.println("\n Dumping out TimeTable values...");
    Serial.print(" Init byte is: "); Serial.println(TimeTable.init);
    Serial.print(" LoggingFrequency is: "); Serial.println(TimeTable.loggingFrequency);
    Serial.print(" samplingRate is: "); Serial.println(TimeTable.samplingRate);
    Serial.print(" samplingDuration is: "); Serial.println(TimeTable.samplingDuration);
    Serial.print(" samplingPeriod is: "); Serial.println(TimeTable.samplingPeriod);
    return StatusResult{noError};
}
  
}
