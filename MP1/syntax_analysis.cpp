#include "syntax_analyzer.hpp"
#include <iostream>
#include <set>

// VARIABLE DECLARATOIN FSM

bool checkVariableDeclaration(const std::vector<Token>& tokens){
    int state = 0;

    std::set<std::string> declared_vars; // to track variables declared later
    for (const auto& token : tokens){

        switch(state){
            case 0: // Start -> Expect TYPE
                if (token.type == KEYWORD_TYPE) state = 1;
                else return false;
                break;

            case 1: // Has seen type already -> Expect IDENTIFIER
                if (token.type == IDENTIFIER){
                    if (declared_vars.count(token.value)) return false;

                    declared_vars.insert((token.value));
                    state = 2;
                }
                else return false;
                break;

            case 2: //
                if (token.type == ASSIGN_OP) state = 3;
                else if (token.type == COMMA) state = 5;
                else if (token.type == SEMICOLON) state = 100;
                else return false;
                break;

            case 3: // has seen '=' -> Expect VALUE
                    // Accept literals or other variables
                if (token.type == LITERAL_VAL){
                    state = 4;
                } 
                else if (token.type == IDENTIFIER){
                    if (declared_vars.find(token.value) == declared_vars.end()) return false;

                    state = 6;
                }
                else return false;
                break;

            case 4: // has seen Value -> Expect '.' or ';'
                if (token.type == COMMA) state = 5;
                else if (token.type == SEMICOLON) state = 100;
                else return false;
                break;

            case 5: // Has seen comma -> Expect IDENTIFIER
                if (token.type == IDENTIFIER){
                    if (declared_vars.count(token.value)) return false;

                    declared_vars.insert(token.value);
                    state = 2;
                }
                else return false;
                break;
            
            case 6: // takes into account changed assignment
                if (token.type == COMMA) state = 5;
                else if (token.type == SEMICOLON) state = 100;
                else if (token.type == ASSIGN_OP) state = 3;
                else return false;
                break;

            case 100: // represents the end state (seen ';')
                      // if another type is seen like "int", then FSM is reset
                if (token.type == KEYWORD_TYPE){
                    state = 1;
                }
                else return false;
                break;
        }
    }

    return (state == 100);
}

// FUNCTION DECLARATION FSM

bool checkFunctionDeclaration(const std::vector<Token>& tokens){
    int state = 0;

    for (const auto& token: tokens){
        switch(state){
            case 0: // Start -> Expect TYPE or VOID
                if (token.type == KEYWORD_TYPE) state = 1;
                else return false;
                break;

            case 1: // Return Type -> Expect FUNCITON NAME
                if (token.type == IDENTIFIER) state =2;
                else return false;
                break;

            case 2: // Function Name -> Expect '('
                if (token.type == L_PARENTHESIS) state = 3;
                else return false;
                break;
            
            case 3: // Inside that parenthesis -> Expect TYPE, VOID, or ')'
                if (token.type == R_PARENTHESIS) state = 7;
                else if (token.type == KEYWORD_TYPE) state = 4;
                else return false;
                break;

            case 4: // Has seen Paramter Type -> Expect ID, ',' or ';'
                if (token.type == IDENTIFIER) state = 5;
                else if (token.type == COMMA) state = 6;
                else if (token.type == R_PARENTHESIS) state = 7;
                else return false;
                break;

            case 5: // Has seen Parameter Name -> Expect ',' or ')'
                if (token.type == COMMA) state = 6;
                else if (token.type == R_PARENTHESIS) state = 7;
                else return false;
                break;

            case 6: // Seen comma inside params -> Expect TYPE
                if (token.type == KEYWORD_TYPE) state = 4;
                else return false;
                break;

            case 7: // Seen ')' -> Functoin header is done. Expect ';' or ','
                if (token.type == SEMICOLON) state = 100;
                else if (token.type == COMMA) state = 8;
                else return false;
                break;

            case 8: // Seen comma after function -> Expect IDENTIFIER or name of the next function
                if (token.type == IDENTIFIER) state = 2;
                else return false;
                break;

            case 100: // end
                if (token.type == KEYWORD_TYPE){
                    state = 1; // reset FSM
                }
                else return false;
                break;
        }
    }
    return (state == 100);
}