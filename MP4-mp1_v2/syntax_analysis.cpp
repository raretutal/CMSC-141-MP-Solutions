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

bool checkFunctionDeclaration(const std::vector<Token>& tokens) {
    // Columns: TYPE, ID, =, VAL, COMMA, SEMI, (, )
    int table[10][8] = {
        { 1, -1, -1, -1, -1, -1, -1, -1}, // State 0: Start
        {-1,  2, -1, -1, -1, -1, -1, -1}, // State 1: Seen Ret Type
        {-1, -1, -1, -1, -1, -1,  3, -1}, // State 2: Seen Func Name
        { 4, -1, -1, -1, -1, -1, -1,  7}, // State 3: Seen (
        {-1,  5, -1, -1,  6, -1, -1,  7}, // State 4: Seen Param Type
        {-1, -1, -1, -1,  6, -1, -1,  7}, // State 5: Seen Param ID
        { 4, -1, -1, -1, -1, -1, -1, -1}, // State 6: Seen Comma in params
        {-1, -1, -1, -1,  8,  9, -1, -1}, // State 7: Seen )
        {-1,  2, -1, -1, -1, -1, -1, -1}, // State 8: Seen Comma after func
        { 1, -1, -1, -1, -1, -1, -1, -1}  // State 9: Accepting (Semi)
    };

    int state = 0;
    for (const auto& token : tokens) {
        int input = getTokenIndex(token.type);
        if (input == -1) return false;

        state = table[state][input];
        if (state == -1) return false;
    }
    
    return (state == 9);
}