#include "nfa_builder.hpp"
#include <stack>

int NFABuilder::createNewState(){
    State s;
    s.id = state_counter++;
    states.push_back(s);
    return s.id;
}

std::vector<State> NFABuilder::getStates() const {
    return states;
}

NFA NFABuilder::buildNFA(const std::vector<Token>& postfix_tokens){
    std::stack<NFA> nfa_stack;

    for(const Token& token: postfix_tokens){
        if(token.type == OPERAND){
            int start = createNewState();
            int accept = createNewState();

            states[start].transitions[token.value[0]].push_back(accept);
            nfa_stack.push({start,accept});

        }else if(token.type == CONCAT ){
            // first item popped is the right side of the concatenation
            NFA nfa2 = nfa_stack.top(); nfa_stack.pop();
            // the second item popped is the left side of the concatenation
            NFA nfa1 = nfa_stack.top(); nfa_stack.pop();

            // add a 'e' transition from accept state of nfa1 to start state of nfa2
            states[nfa1.accept_state].transitions['e'].push_back(nfa2.start_state);

            nfa_stack.push({nfa1.start_state, nfa2.accept_state});

        }else if(token.type == UNION){
            // same thing with CONCAT because of how a stack works
            NFA nfa2 = nfa_stack.top(); nfa_stack.pop();
            NFA nfa1 = nfa_stack.top(); nfa_stack.pop();

            // create new start and accept state.
            int start = createNewState();
            int accept = createNewState();

            // creates branches from the new start state onto the NFAs' old start state
            states[start].transitions['e'].push_back(nfa1.start_state);
            states[start].transitions['e'].push_back(nfa2.start_state);

            // connects the NFAs' previous accept states onto a single accept state
            states[nfa1.accept_state].transitions['e'].push_back(accept);
            states[nfa2.accept_state].transitions['e'].push_back(accept);
            
            nfa_stack.push({start, accept});

        }else if(token.type == STAR){
            // it only applies to one 'fragment' so it pops one NFA from the stack only.
            NFA nfa = nfa_stack.top(); nfa_stack.pop();

            int start = createNewState();
            int accept = createNewState();

            /*
            Creates empty transitions for:
            - From the new start state to the old start state
            - From the new start state to the new accept state (for zero occurences)
            - From old accept state back to back to the old start state (for looping)
            - From old accept state to the new accept state (for finishing and exiting the loop)
            */
            states[start].transitions['e'].push_back(nfa.start_state);
            states[start].transitions['e'].push_back(accept);
            states[nfa.accept_state].transitions['e'].push_back(nfa.start_state);
            states[nfa.accept_state].transitions['e'].push_back(accept);

            nfa_stack.push({start, accept});
        }
    }
    return nfa_stack.top();
}