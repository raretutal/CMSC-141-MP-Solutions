#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

#include <string>
#include <vector>

enum TokenType {
    OPERAND,
    UNION,
    STAR,
    CONCAT,
    UNKNOWN,
    L_PARENTHESIS,
    R_PARENTHESIS
};

struct Token {
    std::string value;
    TokenType type;
};

std::vector<Token> tokenize(std::string regex);
#endif