#include "tokenizer.hpp"
#include <iostream>

int main() {
    std::string test_regex = "a(a+b)*b";
    std::vector<Token> tokens = tokenize(test_regex);

    for (const auto& t : tokens) {
        std::cout << "Value: " << t.value << " | Type: " << t.type << "\n";
    }

    return 0;
}