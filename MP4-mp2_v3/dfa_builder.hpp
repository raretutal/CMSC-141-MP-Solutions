#ifndef DFA_BUILDER_HPP
#define DFA_BUILDER_HPP

#include "nfa_builder.hpp"
#include <set>
#include <map>
#include <vector>

// Represents the final 2D transition table for the DFA
struct DFATable {
    int start_state;
    std::set<int> accept_states;
    // Format: transitions[current_state_id][character] = next_state_id
    std::map<int, std::map<char, int>> transitions;
};

class DFABuilder {
private:
    std::vector<State> nfa_states;
    int nfa_accept_state;

    // Core Subset Construction algorithms
    std::set<int> epsilonClosure(const std::set<int>& T);
    std::set<int> move(const std::set<int>& T, char a);

public:
    DFABuilder(const std::vector<State>& nfa_states_in, int accept_state_in);
    DFATable buildDFA(int nfa_start_state);
};

#endif