//
//  Statement.cpp
//  Database
//
//  Created by rick gessner on 3/20/19.
//  Copyright © 2019 rick gessner. All rights reserved.
//

#include "Statement.h"

namespace deltaPCo2 {

Statement::Statement(Keywords aStatementType){}
Statement::Statement(const Statement &aCopy) {}
Statement::~Statement(){}
StatusResult Statement::parse(Tokenizer &aTokenizer) {
    aTokenizer.next();
    return StatusResult{};
}
StatusResult Statement::run(ostream &aStream) const{
    return StatusResult();
}

}
