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
        if (c == '+' || c == '*' || c == '(' || c == ')'){
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

// Inject implicit concatenation tokens

    std::vector<Token> final_tokens;

    for(size_t i = 0; i<tokens.size(); i++){
        final_tokens.push_back(tokens[i]);

        if(i<tokens.size() - 1){
            TokenType curr = tokens[i].type;
            TokenType next = tokens[i+1].type;

            bool curr_valid = (curr == OPERAND || curr == STAR || curr == R_PARENTHESIS);
            bool next_valid = (next == OPERAND || next == L_PARENTHESIS);

            if(curr_valid && next_valid){
                Token concat_token;
                concat_token.value = ".";
                concat_token.type = CONCAT;
                final_tokens.push_back(concat_token);
            }
        }
    }

    return final_tokens;
}



    
