#include "tokenizer.hpp"
#include <iostream>
#include <sstream>
#include <cctype>
#include <vector>
#include <algorithm>

bool isType(const std::string& s){
    return (s == "int" || s == "float" || s == "double" || s == "char"
    || s == "void");
}

bool isNumber(const std::string& s){
    if (s.empty()) return false;

    bool decimalPointSeen = false;
    size_t start = 0;

    if (s[0] == '-'){
        if (s.length() == 1) return false;
        start = 1;
    }

    for (size_t i = start; i < s.length(); i++){
        if (s[i] == '.') {
            if (decimalPointSeen) return false;
            decimalPointSeen = true;
        } else if (!isdigit(s[i])){
            return false;
        }
    
    }
    return true;
}

bool isValidIdentifier(const std::string& s){
    if (s.empty()) return false;

    // Rule 1:: Start with a letter or underscore
    if (!isalpha(s[0]) && s[0] != '_'){
        return false;
    }

    // Rule 2: the rest are just letters, numbers, or underscores
    for (size_t i = 1; i< s.length(); i++){
        if(!isalnum(s[i]) && s[i] != '_'){
            return false;
        }
    }

    //Rule 3: Keywords can't be identifiers
    if(isType(s)) return false;

    return true;

}

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