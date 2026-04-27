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

    
        if (isType(word)) t.type = KEYWORD_TYPE;
        else if (word == "=") t.type = ASSIGN_OP;
        else if (word == ",") t.type = COMMA;
        else if (word == ";") t.type = SEMICOLON;
        else if (word == "(") t.type = L_PARENTHESIS;
        else if (word == ")") t.type = R_PARENTHESIS;
        else if (isNumber(word)) t.type = LITERAL_VAL;
        else if (word.length() >= 3 && word.front() == '\'' && word.back() == '\''){
            t.type = LITERAL_VAL;
        }
        else if (isValidIdentifier(word)) t.type = IDENTIFIER;

        tokens.push_back(t);
        
    }
    return tokens;

}