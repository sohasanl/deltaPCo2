//
//  TokenSequence.cpp
//  141B
//
//  Created by Omid Hasanli on 5/11/20.
//  Copyright © 2020 Omid Hasanli. All rights reserved.
//

#include "TokenSequence.h"

namespace deltaPCo2{
TokenSequence::TokenSequence(Tokenizer &aTokenizer): tokenizer(&aTokenizer){}

TokenSequence::~TokenSequence(){}

StatusResult    TokenSequence::getParameters(Keywords *theKeywords, SamplingCommands& parameters){
    Token& theToken = tokenizer->nextOne();
    StatusResult theResult{syntaxError};
    float aValue = 0;
    bool result;
    do{
        if(theToken.type == TokenType::keyword){
            switch (theToken.keyword){
                case Keywords::period_kw:
                    if(!(theResult=getValue(aValue))){ return theResult;}
                    parameters.insert(std::pair<Keywords,float>(theToken.keyword, aValue));
                    break;
                case Keywords::duration_kw:
                    if(!(theResult=getValue(aValue))){ return theResult;}
                    parameters.insert(std::pair<Keywords,float>(theToken.keyword, aValue));
                    break;
                case Keywords::rate_kw:
                    if(!(theResult=getValue(aValue))){ return theResult;}
                    parameters.insert(std::pair<Keywords,float>(theToken.keyword, aValue));
                    break;
                default: return StatusResult{unknownCommand};
            }
        } else { return StatusResult{syntaxError};  }
        if(tokenizer->more()){theToken = tokenizer->nextOne();}
        } while((result = tokenizer->more()));
    return StatusResult{noError};
}


StatusResult   TokenSequence::getValue(float& aValue){
    if(tokenizer->more()){
        Token &theToken = tokenizer->nextOne();
        if(theToken.type == TokenType::number){
            aValue = atof(theToken.data.c_str());
            return StatusResult{noError};
        }
    }
    return StatusResult{syntaxError};
}

}
