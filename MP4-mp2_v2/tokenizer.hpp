#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

#include <string>
#include <vector>

enum TokenType {
    UNKNOWN,
    KEYWORD_TYPE,
    IDENTIFIER,
    LITERAL_VAL,
    ASSIGN_OP,
    COMMA,
    SEMICOLON,
    L_PARENTHESIS,
    R_PARENTHESIS
};

struct Token {
    std::string value;
    TokenType type;
};

std::vector<Token> tokenize(std::string code);
bool checkVariableDeclaration(const std::vector<Token>& tokens);
bool checkFunctionDeclaration(const std::vector<Token>& tokens);

bool isType(const std::string& s);
bool isValidIdentifier(const std::string& s);

#endif