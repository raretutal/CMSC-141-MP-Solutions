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
            while(!operator_stack.empty() && operator_stack.back().type != L_PARENTHESIS){
                output_queue.push_back(operator_stack.back());
                operator_stack.pop_back();
            }
            if(!operator_stack.empty() && operator_stack.back().type == L_PARENTHESIS){
                operator_stack.pop_back();
            }            

        }else if(token.type == STAR || token.type == CONCAT || token.type == UNION){
            while(!operator_stack.empty() && operator_stack.back().type != L_PARENTHESIS
            && getPrecedence(operator_stack.back().type) >= getPrecedence(token.type)){

                output_queue.push_back(operator_stack.back());
                operator_stack.pop_back();
            }
            operator_stack.push_back(token);
        }

    }
    // clean remaining shit in the operator stack onto the operator queue to finish postfix
    while(!operator_stack.empty()){
        output_queue.push_back(operator_stack.back());
        operator_stack.pop_back();
    }
    return output_queue;
}

