//
//  Statement.h
//  Database
//
//  Created by rick gessner on 3/20/19.
//  Copyright © 2019 rick gessner. All rights reserved.
//

#ifndef Statement_h
#define Statement_h

#include "keywords.h"
#include "Tokenizer.h"
#include "Helpers.h"
#include "Errors.h"
#include "SdFat.h"


namespace deltaPCo2 {

class Tokenizer;

class Statement {
public:
    Statement(Keywords aStatementType=Keywords::unknown_kw);
    Statement(const Statement &aCopy);
    virtual                 ~Statement();
    virtual   StatusResult  parse(Tokenizer &aTokenizer);
    virtual   StatusResult  run(ostream &aStream) const;
};

}

#endif /* Statement_h */
