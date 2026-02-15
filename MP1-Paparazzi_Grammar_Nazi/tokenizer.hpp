#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

#include <string>
#include <vector>

// Allows FSM to sitch on "types" instead of just usig raw strings
enum TokenType{
    UNKNOWN,
    KEYWORD_TYPE, // int, float, double, etc..
    IDENTIFIER, // either variable or function
    LITERAL_VAL, // numbers or characters
    ASSIGN_OP,
    COMMA,
    SEMICOLON,
    L_PARENTHESIS,
    R_PARENTHESIS
};

struct Token{
    std::string value;
    TokenType type;
};

std::vector<Token> tokenize(std::string code);

bool checkVariableDeclaration(const std::vector<Token>& tokens);

bool checkFunctionDeclaration(const std::vector<Token>& tokens);

// helper function declarations
bool isType(const std::string& s);
bool isValidIdentifier(const std::string& s);



#endif