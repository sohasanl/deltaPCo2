//  Helpers.hpp
//  Created by rick gessner on 4/14/19.
//  Copyright © 2019 rick gessner. All rights reserved.
//

#ifndef Helpers_h
#define Helpers_h

#include "keywords.h"
#include <algorithm>

namespace deltaPCo2 {

template<typename T, size_t aSize>
bool in_array(T (&anArray)[aSize], const T &aValue) {
    return std::find(std::begin(anArray), std::end(anArray), aValue);
};


static std::map<std::string, Operators> gOperators = {
    std::make_pair(".", Operators::dot_op),
    std::make_pair("+", Operators::add_op),
    std::make_pair("-", Operators::subtract_op),
    std::make_pair("*", Operators::multiply_op),
    std::make_pair("/", Operators::divide_op),
    std::make_pair("^", Operators::power_op),
    std::make_pair("%", Operators::mod_op),
    std::make_pair("=", Operators::equal_op),
    std::make_pair("!=", Operators::notequal_op),
    std::make_pair("not", Operators::notequal_op),
    std::make_pair("<", Operators::lt_op),
    std::make_pair("<=", Operators::lte_op),
    std::make_pair(">", Operators::gt_op),
    std::make_pair(">=", Operators::gte_op),
    std::make_pair("and", Operators::and_op),
    std::make_pair("or", Operators::or_op),
    std::make_pair("nor", Operators::nor_op),
    std::make_pair("between", Operators::between_op),
};

//a list of known functions...
static std::map<std::string,int> gFunctions = {
    std::make_pair("avg", 10),
    std::make_pair("count", 20),
    std::make_pair("max", 30),
    std::make_pair("min", 40)
};


//This map binds a keyword string with a Keyword (token)...
static std::map<std::string,  Keywords> gDictionary = {
    std::make_pair("update",     deltaPCo2::Keywords::update_kw),
    std::make_pair("version",    deltaPCo2::Keywords::version_kw),
    std::make_pair("sampling",   deltaPCo2::Keywords::sampling_kw),
    std::make_pair("logging",    deltaPCo2::Keywords::logging_kw),
    std::make_pair("rate",       deltaPCo2::Keywords::rate_kw),
    std::make_pair("duration",   deltaPCo2::Keywords::duration_kw),
    std::make_pair("period",     deltaPCo2::Keywords::period_kw),
    std::make_pair("frequency",  deltaPCo2::Keywords::frequency_kw),
    std::make_pair("timetable",  deltaPCo2::Keywords::timetable_kw),

};

class Helpers {
public:
    
    static Keywords getKeywordId(const std::string aKeyword) {
        auto theIter = gDictionary.find(aKeyword);
        if (theIter != gDictionary.end()) {
            return theIter->second;
        }
        return Keywords::unknown_kw;
    }
    
    //convert from char to keyword...
    static Keywords charToKeyword(char aChar) {
        switch(toupper(aChar)) {
            case 'I': return Keywords::integer_kw;
            case 'T': return Keywords::datetime_kw;
            case 'B': return Keywords::boolean_kw;
            case 'F': return Keywords::float_kw;
            case 'V': return Keywords::varchar_kw;
            default:  return Keywords::unknown_kw;
        }
    }
    
    static const char* keywordToString(Keywords aType) {
        switch(aType) {
            case Keywords::integer_kw:  return "integer";
            case Keywords::float_kw:    return "float";
            case Keywords::boolean_kw:  return "bool";
            case Keywords::datetime_kw: return "datetime";
            case Keywords::varchar_kw:  return "varchar";
            default:                    return "unknown";
        }
    }
    
    
    static const char* BlockTypeToString(char aType) {
        switch(aType) {
            case 'S':  return "Schema";
            case 'M':    return "Meta";
            case 'D':  return "Data";
            case 'E': return "Entity";
            case 'F':  return "Free";
            case 'I':  return "Index";
            default:                    return "Unknown";
        }
    }
    
    // USE: ---validate that given keyword is a datatype...
    static bool isDatatype(Keywords aKeyword) {
        switch(aKeyword) {
            case Keywords::char_kw:
            case Keywords::datetime_kw:
            case Keywords::float_kw:
            case Keywords::integer_kw:
            case Keywords::varchar_kw:
                return true;
            default: return false;
        }
    }
    
    static Operators toOperator(std::string aString) {
        auto theIter = gOperators.find(aString);
        if (theIter != gOperators.end()) {
            return theIter->second;
        }
        return Operators::unknown_op;
    }
    
    static int getFunctionId(const std::string anIdentifier) {
        auto theIter = gFunctions.find(anIdentifier);
        if (theIter != gFunctions.end()) {
            return theIter->second;
        }
        return 0;
    }
    
    static bool isNumericKeyword(Keywords aKeyword) {
        static Keywords theTypes[]={Keywords::decimal_kw, Keywords::double_kw, Keywords::float_kw, Keywords::integer_kw};
        for(auto k : theTypes) {
            if(aKeyword==k) return true;
        }
        return false;
    }
    
};


}
#endif /* Helpers_h */
