#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

typedef set<int> State;
typedef map<char, State> Transition;

struct NFA {
    int num_states;
    vector<Transition> transitions;
    set<int> final_states;
};

struct DFA {
    vector<Transition> transitions;
    set<int> final_states;
};

State epsilon_closure(const NFA &nfa, const State &state) {
    State closure = state;
    for (int s : state) {
        if (nfa.transitions[s].count('\0')) {
            State epsilon_moves = nfa.transitions[s].at('\0');
            closure.insert(epsilon_moves.begin(), epsilon_moves.end());
        }
    }
    return closure;
}

State move(const NFA &nfa, const State &state, char symbol) {
    State next_state;
    for (int s : state) {
        if (nfa.transitions[s].count(symbol)) {
            State moves = nfa.transitions[s].at(symbol);
            next_state.insert(moves.begin(), moves.end());
        }
    }
    return next_state;
}

DFA nfa_to_dfa(const NFA &nfa) {
    map<State, int> dfa_states;
    DFA dfa;
    queue<State> pending;
    State initial = {0};
    initial = epsilon_closure(nfa, initial);
    dfa_states[initial] = 0;
    pending.push(initial);

    while (!pending.empty()) {
        State current = pending.front();
        pending.pop();
        int current_id = dfa_states[current];

        if (any_of(current.begin(), current.end(), [&](int s) { return nfa.final_states.count(s); })) {
            dfa.final_states.insert(current_id);
        }

        for (char symbol = '0'; symbol <= '1'; symbol++) {
            State next = move(nfa, current, symbol);
            next = epsilon_closure(nfa, next);
            if (next.empty()) continue;

            if (dfa_states.count(next) == 0) {
                int new_id = dfa_states.size();
                dfa_states[next] = new_id;
                pending.push(next);
            }
            dfa.transitions[current_id][symbol] = dfa_states[next];
        }
    }

    return dfa;
}

int main() {
    NFA nfa;
    nfa.num_states = 5;
    nfa.transitions.resize(nfa.num_states);
    nfa.transitions[0]['\0'] = {1, 3};
    nfa.transitions[1]['0'] = {2};
    nfa.transitions[1]['1'] = {1};
    nfa.transitions[2]['\0'] = {1, 3};
    nfa.transitions[3]['1'] = {4};
    nfa.transitions[4]['0'] = {4};
    nfa.transitions[4]['1'] = {4};
    nfa.final_states = {4};

    DFA dfa = nfa_to_dfa(nfa);

    cout << "DFA Transitions:\n";
    for (size_t i = 0; i < dfa.transitions.size(); i++) {
        for (const auto &p : dfa.transitions[i]) {
            cout << "State " << i << " -- " << p.first << " --> State " << p.second << endl;
        }
    }

    cout << "DFA Final States: ";
    for (int state : dfa.final_states) {
        cout << state << " ";
    }
        cout << endl;
    return 0;
}