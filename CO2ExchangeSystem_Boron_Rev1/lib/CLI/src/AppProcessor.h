//
//  AppProcessor.hpp
//
//  Created by Omid Hasanli on 4/30/20.
//  Copyright © 2020 Omid Hasanli. All rights reserved.

#ifndef AppProcessor_h
#define AppProcessor_h
#include "CommandProcessor.h"
#include "TokenSequence.h"
#include "Timing.h"

namespace deltaPCo2 {

class AppProcessor : public CommandProcessor{
  public:
    
    AppProcessor(CommandProcessor *aNext=nullptr);
    virtual ~AppProcessor();
    
    virtual Statement*    getStatement(Tokenizer &aTokenizer);
    virtual StatusResult  interpret(const Statement &aStatement);

    StatusResult samplingCommand(const SamplingCommands& parameters);
    StatusResult loggingCommand(const float mins);
    StatusResult timetableCommand();

    
  };

}

#endif /* AppProcessor_h */
