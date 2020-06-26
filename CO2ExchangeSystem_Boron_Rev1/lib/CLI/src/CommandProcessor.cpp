//
//  CommandProcessor.cpp
//
//  Created by rick gessner on 3/30/18.
//  Copyright © 2018 rick gessner. All rights reserved.
//


#include "CommandProcessor.h"

#include "Statement.h"
#include "Tokenizer.h"
#include <memory>

namespace deltaPCo2 {
  
  CommandProcessor::CommandProcessor(CommandProcessor *aNext) : next(aNext) {}
  
  CommandProcessor::~CommandProcessor() {}

  StatusResult CommandProcessor::processInput(Tokenizer &aTokenizer) {
    std::unique_ptr<Statement> theStatement(getStatement(aTokenizer));
    if(theStatement) {
      return interpret(*theStatement);
    }
    else if(next) {
      return next->processInput(aTokenizer);
    }
    return StatusResult{unknownCommand};
  }

}
