#include <iostream>
#include <string>
#include <vector>
#include "tokenizer.hpp"
#include "parser.hpp"
#include "nfa_builder.hpp"
#include "dfa_builder.hpp"

// Simulates running a string through the generated DFA Table
bool simulateDFA(const DFATable& dfa, const std::string& input) {
    int current_state = dfa.start_state;

    for (char c : input) {
        // If the current state has a transition for the character, take it
        if (dfa.transitions.count(current_state) && 
            dfa.transitions.at(current_state).count(c)) {
            
            current_state = dfa.transitions.at(current_state).at(c);
        } else {
            // No valid transition means the machine hits a dead state and rejects
            return false;
        }
    }

    // Accept if the final state is in the set of accept states
    return dfa.accept_states.count(current_state) > 0;
}

int main() {
    int num_test_cases;
    if (!(std::cin >> num_test_cases)) return 0;

    while (num_test_cases--) {
        std::string regex;
        std::cin >> regex;

        // 1. Build the Pipeline
        std::vector<Token> tokens = tokenize(regex);
        std::vector<Token> postfix = infixToPostfix(tokens);

        NFABuilder nfa_builder;
        NFA nfa = nfa_builder.buildNFA(postfix);

        DFABuilder dfa_builder(nfa_builder.getStates(), nfa.accept_state);
        DFATable dfa = dfa_builder.buildDFA(nfa.start_state);

        // 2. Read and test the strings
        int num_strings;
        std::cin >> num_strings;

        for (int i = 0; i < num_strings; ++i) {
            std::string test_string;
            std::cin >> test_string;

            // Handle the problem's specific edge case: 'e' represents an empty string
            if (test_string == "e") {
                test_string = ""; 
            }

            // 3. Simulate and Output
            if (simulateDFA(dfa, test_string)) {
                std::cout << "yes\n";
            } else {
                std::cout << "no\n";
            }
        }
    }

    return 0;
}