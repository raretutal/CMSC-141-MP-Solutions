#include "tokenizer.hpp"
#include <iostream>
#include <sstream>
#include <cctype>
#include <vector>
#include <algorithm>

// ~MAIN TOKENIZE FUNCTION~

std::vector<Token> tokenize(std::string code){
    std::vector<Token> tokens;

    // PRE-PROCESSING portion to pad symbols with spaces
    std::string clean_code = "";
    for (char c : code){
        if (c == '=' || c == ',' || c == ';' || c == '(' || c == ')'){
            clean_code += " ";
            clean_code += c;
            clean_code += " ";

        }else{
            clean_code += c;
        }
    }

    // SPLITTING AND CLASSIFYING
    std::stringstream ss(clean_code);
    std::string word;

    while (ss >> word){
        Token t;
        t.value = word;
        t.type = UNKNOWN;

        if (word == "+") {
                    t.type = UNION;
                } else if (word == "*") {
                    t.type = STAR;
                } else if (word == "(") {
                    t.type = L_PARENTHESIS;
                } else if (word == ")") {
                    t.type = R_PARENTHESIS;
                } else if (word == "a" || word == "b" || word == "e") {
                    t.type = OPERAND;
                }
                tokens.push_back(t);
        }

    
        return tokens;
    }

    

    
