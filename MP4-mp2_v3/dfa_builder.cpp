#include "dfa_builder.hpp"
#include <stack>

// Initializes the builder with the existing NFA structure
DFABuilder::DFABuilder(const std::vector<State>& nfa_states_in, int accept_state_in) {
    nfa_states = nfa_states_in;
    nfa_accept_state = accept_state_in;
}
// Move - Returns all NFA states directly reachable from set the set
std::set<int> DFABuilder::move(const std::set<int>& T, char a) {
    std::set<int> result;
    for (int state : T) {
        if (nfa_states[state].transitions.count(a)) {
            for (int u : nfa_states[state].transitions.at(a)) {
                result.insert(u);
            }
        }
    }
    return result;
}

// Returns all NFA states reachable from the set using only epsilon transitions
std::set<int> DFABuilder::epsilonClosure(const std::set<int>& T) {
    std::stack<int> stack;
    std::set<int> closure = T;

    for (int state : T) {
        stack.push(state);
    }

    while (!stack.empty()) {
        int t = stack.top();
        stack.pop();

        if (nfa_states[t].transitions.count('e')) {
            for (int u : nfa_states[t].transitions.at('e')) {
                if (closure.find(u) == closure.end()) {
                    closure.insert(u);
                    stack.push(u);
                }
            }
        }
    }
    return closure;
}

// The main subset construction loop that generates the 2D table
DFATable DFABuilder::buildDFA(int nfa_start_state) {
    DFATable table;
    table.start_state = 0; 

    // Maps a unique set of NFA states to a single integer DFA state ID
    std::map<std::set<int>, int> dfa_state_map;
    std::vector<std::set<int>> unmarked_states;
    int dfa_state_counter = 0;

    char alphabet[] = {'a', 'b'};

    // Initialize the starting DFA state
    std::set<int> start_set = epsilonClosure({nfa_start_state});
    dfa_state_map[start_set] = dfa_state_counter++;
    unmarked_states.push_back(start_set);

    if (start_set.count(nfa_accept_state)) {
        table.accept_states.insert(dfa_state_map[start_set]);
    }

    int current_unmarked_idx = 0;

    // Process all unmarked DFA states
    while (current_unmarked_idx < unmarked_states.size()) {
        std::set<int> T = unmarked_states[current_unmarked_idx++];
        int T_id = dfa_state_map[T];

        for (char a : alphabet) {
            // Find reachable states for the current character, including epsilon jumps
            std::set<int> move_T_a = move(T, a);
            if (move_T_a.empty()) continue;

            std::set<int> U = epsilonClosure(move_T_a);

            // If this exact config of states has not been seen before, save it
            if (dfa_state_map.find(U) == dfa_state_map.end()) {
                dfa_state_map[U] = dfa_state_counter++;
                unmarked_states.push_back(U);

                if (U.count(nfa_accept_state)) {
                    table.accept_states.insert(dfa_state_map[U]);
                }
            }

            // Populate the 2D transition table
            table.transitions[T_id][a] = dfa_state_map[U];
        }
    }

    return table;
}