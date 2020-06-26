//
//  CommandProcessor.hpp
//  Created by rick gessner on 3/17/19.
//  Copyright © 2019 rick gessner. All rights reserved.
//

#ifndef CommandProcessor_h
#define CommandProcessor_h

#include <stdio.h>
#include <string>
#include "Statement.h"

namespace deltaPCo2 {
  
  class Statement;
  class Tokenizer;

  class CommandProcessor {
  public:
    CommandProcessor(CommandProcessor *aNext=nullptr);
    ~CommandProcessor();
    
    virtual StatusResult  processInput(Tokenizer &aTokenizer);

    virtual Statement*    getStatement(Tokenizer &aTokenizer)=0;
    virtual StatusResult  interpret(const Statement &aStatement)=0;

    
    CommandProcessor *next;
  };
   
}

#endif /* CommandProcessor_h */
