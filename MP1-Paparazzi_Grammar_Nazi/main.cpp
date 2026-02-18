#include <iostream>
#include <string>
#include <vector>
#include "tokenizer.hpp"       
#include "syntax_analyzer.hpp" 

int main() {
    int testCases;
    
    if (!(std::cin >> testCases)) return 0; 

    std::string dummy;
    std::getline(std::cin, dummy);

    while (testCases--) {
        std::string line;
        
        std::getline(std::cin, line);
        
        // Safety check for empty lines
        if (line.length() < 3) {
            continue; 
        }

        // Parsing the Modes chosen by user
        char mode = line[0];
        std::string code = line.substr(2); 
        
        // Tokenizing the code inputted 
        std::vector<Token> tokens = tokenize(code);
        
        // Run the FSM that fits the conditions
        bool isValid = false;
        
        if (mode == '1') {
            // Mode 1 - Variable Declaration
            isValid = checkVariableDeclaration(tokens);
            
            if (isValid) {
                std::cout << "VALID VARIABLE DECLARATION" << std::endl;
            } else {
                std::cout << "INVALID VARIABLE DECLARATION" << std::endl;
            }
        } 
        else if (mode == '2') {
            // Mode 2 - Function Declaration
            isValid = checkFunctionDeclaration(tokens);
            
            if (isValid) {
                std::cout << "VALID FUNCTION DECLARATION" << std::endl;
            } else {
                std::cout << "INVALID FUNCTION DECLARATION" << std::endl;
            }
        }
        else {
             // Just in case the input doesn't start with 1 or 2 but idk, not stated in problem?
             std::cout << "UNKNOWN MODE" << std::endl;
        }
    }
    return 0;
}