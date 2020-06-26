//
//  AppStatement.cpp
//
//  Created by Omid Hasanli on 4/30/20.
//  Copyright © 2020 Omid Hasanli. All rights reserved.

#include "AppStatement.h"

namespace deltaPCo2 {

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///AppStatement methods
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

StatusResult  AppStatement::parse(Tokenizer &aTokenizer){
    return StatusResult{noError};
}
StatusResult  AppStatement::run(ostream &aStream) const{
    return StatusResult{noError};
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///SamplingStatement methods
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
StatusResult  SamplingStatement::parse(Tokenizer &aTokenizer){
     const int kMinLength = 3;
     StatusResult theResult{syntaxError};
     if(kMinLength <= aTokenizer.remaining()){
         Keywords theKeywords[]={Keywords::period_kw,Keywords::duration_kw, Keywords::rate_kw};
         TokenSequence theParse(aTokenizer);
         theResult=theParse.getParameters(theKeywords, valueCollection);
         return theResult;
     } 
    return theResult;
}
StatusResult SamplingStatement::run(ostream &aStream) const{
    return appprocessor.samplingCommand(valueCollection);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///loggingStatement methods
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

StatusResult  loggingStatement::parse(Tokenizer &aTokenizer){
    if(3<=aTokenizer.remaining()){
        Token &theFirstToken = aTokenizer.peek(1);
        Token &theSecondToken = aTokenizer.peek(2);
        if(Keywords::frequency_kw == theFirstToken.keyword && TokenType::number == theSecondToken.type){
            frequency = atof(theSecondToken.data.c_str());
            aTokenizer.next(2);
            return StatusResult{Errors::noError};
        } 
    } 
    return StatusResult{Errors::syntaxError};
}

StatusResult loggingStatement::run(ostream &aStream) const{
    return appprocessor.loggingCommand(frequency);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///timetableStatement methods
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
StatusResult  timetableStatement::parse(Tokenizer &aTokenizer){
    // if(1==aTokenizer.size()){
    //     return StatusResult{Errors::noError};
    // } 
    // return StatusResult{Errors::syntaxError};
    return StatusResult{Errors::noError};
}
StatusResult  timetableStatement::run(ostream &aStream) const{
    return appprocessor.timetableCommand();
}

}
