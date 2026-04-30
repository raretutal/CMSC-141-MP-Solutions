#ifndef NFA_BUILDER
#define NFA_BUILDER

#include <vector>
#include <map>
#include "tokenizer.hpp" // to have access to Token and TokenType  :))

// state in NFA
struct State{
    int id;
    std::map<char, std::vector<int> >transitions;
};

// saves start and accept states during NFA construction
struct NFA{
    int start_state;
    int accept_state;
};

// ooga booga 
class NFABuilder{
    private:
        std::vector<State> states;
        int state_counter = 0;

        // Helper to create a brand new state
        int createNewState();

    public:
        // builder of the complete NFA from postfix tokens.
        NFA buildNFA(const std::vector<Token>& postfix_tokens);
        
        // retrieve full list of states for DFA conversion
        std::vector<State> getStates() const;
};


#endif