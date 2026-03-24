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

        if (line.length() < 3) continue; 

        char mode = line[0];
        std::string code = line.substr(2); 

        std::vector<Token> tokens = tokenize(code);
        bool isValid = false;

        if (mode == '1') {
            isValid = checkVariableDeclaration(tokens);
            if (isValid) std::cout << "VALID VARIABLE DECLARATION" << std::endl;
            else std::cout << "INVALID VARIABLE DECLARATION" << std::endl;
        } 
        else if (mode == '2') {
            isValid = checkFunctionDeclaration(tokens);
            if (isValid) std::cout << "VALID FUNCTION DECLARATION" << std::endl;
            else std::cout << "INVALID FUNCTION DECLARATION" << std::endl;
        }
        else {
             std::cout << "UNKNOWN MODE" << std::endl;
        }
    }
    return 0;
}