#include "syntax_analyzer.hpp"

// Maps TokenType to a column index for the transition tables
int getTokenIndex(TokenType type) {
    switch(type) {
        case KEYWORD_TYPE:  return 0;
        case IDENTIFIER:    return 1;
        case ASSIGN_OP:     return 2;
        case LITERAL_VAL:   return 3;
        case COMMA:         return 4;
        case SEMICOLON:     return 5;
        case L_PARENTHESIS: return 6;
        case R_PARENTHESIS: return 7;
        default:            return -1;
    }
}