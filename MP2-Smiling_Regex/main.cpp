#include <iostream>
#include <regex>
#include "regex_converter.hpp"


int main(){

    int numTestCases;
    if (std::cin >> numTestCases){
        
        std::string dummy;
        std::getline(std::cin, dummy);

    }

    while (numTestCases--){
        std::string mpRegex;
        std::getline(std::cin, mpRegex);


        std::string standardRegex = convertToStandardRegex(mpRegex);

        try {
            // This is using ECMAScript syntax
            std::regex re(standardRegex);

            int numStrings;
            std::cin >> numStrings;
            std::string dummy;
            std::getline(std::cin, dummy);

            while (numStrings--){
                std::string inputStr;
                std::getline(std::cin, inputStr);

                // check for empty string
                if (inputStr == "e"){
                    inputStr = "";
                }
                // checking if entire string matches given regex
                if (std::regex_match(inputStr, re)){
                    std::cout << "yes" << std::endl;
                }else
                    std::cout << "no" << std::endl; 
            }
        }
        catch (const std::regex_error& e){
            std::cerr <<"Regex error: " << e.what() << std::endl;
        }
  }
  
    return 0;
}