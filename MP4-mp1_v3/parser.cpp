#include "parser.hpp"
#include <vector>

int getPrecedence(TokenType type){
    if(type == STAR) return 3;
    if(type == CONCAT) return 2;
    if(type == UNION) return 1;

    return 0;
}

std::vector<Token> infixToPostfix(const std::vector<Token>& infix_token){

    
}

