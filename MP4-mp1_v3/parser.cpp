#include "parser.hpp"
#include <vector>

int getPrecedence(TokenType type){
    if(type == STAR) return 3;
    if(type == CONCAT) return 2;
    if(type == UNION) return 1;

    return 0;
}

std::vector<Token> infixToPostfix(const std::vector<Token>& infix_token){
    
    std::vector<Token> output_queue;
    std::vector<Token> operator_stack;

    for(const Token& token: infix_token){
        if( token.type == OPERAND){
            output_queue.push_back(token);

        }else if(token.type == L_PARENTHESIS){
            operator_stack.push_back(token);

        }else if(token.type == R_PARENTHESIS){

            

        }
    }
    
}

