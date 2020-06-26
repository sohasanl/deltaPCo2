//
//  AppStatement.hpp
//  Created by Omid Hasanli on 4/30/20.
//  Copyright © 2020 Omid Hasanli. All rights reserved.
//

#ifndef AppStatement_h
#define AppStatement_h

#include "Statement.h"
#include "AppProcessor.h"
#include "keywords.h"
#include "Tokenizer.h"
#include "Helpers.h"
#include "Errors.h"
#include "TokenSequence.h"



namespace deltaPCo2 {

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///AppStatement subclass
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class AppStatement: public Statement{
public:
    AppStatement(Keywords aStatementType, AppProcessor &aProcessor): Statement(aStatementType), appprocessor(aProcessor){};
    
    AppStatement(const AppStatement &aCopy): Statement(aCopy), appprocessor(aCopy.appprocessor){};
    StatusResult  parse(Tokenizer &aTokenizer) override;
    StatusResult  run(ostream &aStream) const;
    
    std::string name;
    AppProcessor& appprocessor;
};




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///SamplingStatement subclass
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class SamplingStatement : public AppStatement {
public:
    SamplingStatement(AppProcessor &aProcessor) :  AppStatement(Keywords::sampling_kw, aProcessor) {}
    StatusResult  parse(Tokenizer &aTokenizer);
    StatusResult  run(ostream &aStream) const;
    SamplingCommands valueCollection;
    uint16_t period;
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///loggingStatement subclass
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class loggingStatement : public AppStatement {
public:
    loggingStatement(AppProcessor &aProcessor) :  AppStatement(Keywords::logging_kw, aProcessor) {}
    StatusResult  parse(Tokenizer &aTokenizer);
    StatusResult  run(ostream &aStream) const;
    float frequency;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///timetableStatement subclass
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class timetableStatement : public AppStatement {
public:
    timetableStatement(AppProcessor &aProcessor) :  AppStatement(Keywords::timetable_kw, aProcessor) {}
    StatusResult  parse(Tokenizer &aTokenizer);
    StatusResult  run(ostream &aStream) const;
};

}

#endif /* AppStatement_h */
