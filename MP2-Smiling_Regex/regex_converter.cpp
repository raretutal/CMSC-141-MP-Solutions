#include "regex_converter.hpp"
#include <string>

std::string convertToStandardRegex(std::string pattern){

    std::string standardPattern = "";

    for (char c : pattern){
        if (c == ' '){
            continue;
        }
        else if (c == '+'){
            standardPattern += '|'; // since C++'s union is denoted by '|', not '+' 
        }
        else if (c == 'e'){
            standardPattern += "()"; // empty string is denoated by "()" in C++
        }
        else{
            standardPattern += c;
        }
    }
    return standardPattern;
}

