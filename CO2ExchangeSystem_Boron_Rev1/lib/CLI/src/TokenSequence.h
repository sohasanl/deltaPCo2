//
//  TokenSequence.hpp
//  141B
//
//  Created by Omid Hasanli on 5/11/20.
//  Copyright © 2020 Omid Hasanli. All rights reserved.
//

#ifndef TokenSequence_h
#define TokenSequence_h


#include "Tokenizer.h"
#include "keywords.h"
#include "Errors.h"


#include <vector>

namespace deltaPCo2{

using StringList = std::vector<std::string>;
using StringCollection =std::vector<StringList>;
using SamplingCommands = std::map<Keywords, float>;

class TokenSequence{
public:
    TokenSequence(Tokenizer &aTokenizer);
    ~TokenSequence();


    StatusResult        getParameters(Keywords *theKeywords, SamplingCommands& parameters);
    StatusResult        getValue(float& aValue);

protected:
    Tokenizer *tokenizer;
};

}

#endif /* TokenSequence_h */
