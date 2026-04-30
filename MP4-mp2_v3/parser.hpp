#ifndef PARSER_HPP
#define PARSER_HPP
#include "tokenizer.hpp"
#include <vector>

// get operator priority yes yes
int getPrecedence(TokenType type);

// Shunting-yard algorithm (goated alg yeah yeah)
std::vector<Token>infixToPostfix(const std::vector<Token>& infix_token);


#endif