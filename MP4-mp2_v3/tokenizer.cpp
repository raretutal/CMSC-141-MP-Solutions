#include "tokenizer.hpp"
#include <cctype>

// ~MAIN TOKENIZER FUNCTION~
std::vector<Token> tokenize(std::string regex) {
    std::vector<Token> tokens;

    // Read character by character
    for (char c : regex) {
        // Ignore spaces entirely
        if (std::isspace(c)) continue;

        Token t;
        t.value = std::string(1, c);
        t.type = UNKNOWN;

        if (c == '+') t.type = UNION;
        else if (c == '*') t.type = STAR;
        else if (c == '(') t.type = L_PARENTHESIS;
        else if (c == ')') t.type = R_PARENTHESIS;
        else if (c == 'a' || c == 'b' || c == 'e') t.type = OPERAND;

        // Only push valid tokens
        if (t.type != UNKNOWN) {
            tokens.push_back(t);
        }
    }

    // Inject explicit concatenation tokens
    std::vector<Token> final_tokens;

    for (size_t i = 0; i < tokens.size(); i++) {
        final_tokens.push_back(tokens[i]);

        if (i < tokens.size() - 1) {
            TokenType curr = tokens[i].type;
            TokenType next = tokens[i + 1].type;

            bool curr_valid = (curr == OPERAND || curr == STAR || curr == R_PARENTHESIS);
            bool next_valid = (next == OPERAND || next == L_PARENTHESIS);

            if (curr_valid && next_valid) {
                Token concat_token;
                concat_token.value = ".";
                concat_token.type = CONCAT;
                final_tokens.push_back(concat_token);
            }
        }
    }

    return final_tokens;
}