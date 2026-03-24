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

bool checkVariableDeclaration(const std::vector<Token>& tokens) {
    // Columns: TYPE, ID, =, VAL, COMMA, SEMI, (, )
    int table[7][8] = {
        { 1, -1, -1, -1, -1, -1, -1, -1}, // State 0: Start
        {-1,  2, -1, -1, -1, -1, -1, -1}, // State 1: Seen Type
        {-1, -1,  3, -1,  5,  6, -1, -1}, // State 2: Seen ID
        {-1,  4, -1,  4, -1, -1, -1, -1}, // State 3: Seen =
        {-1, -1,  3, -1,  5,  6, -1, -1}, // State 4: Seen Value
        {-1,  2, -1, -1, -1, -1, -1, -1}, // State 5: Seen Comma
        { 1, -1, -1, -1, -1, -1, -1, -1}  // State 6: Accepting (Semi)
    };

    int state = 0;
    for (const auto& token : tokens) {
        int input = getTokenIndex(token.type);
        if (input == -1) return false;

        state = table[state][input];
        if (state == -1) return false;
    }
    
    return (state == 6);
}