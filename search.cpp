#include "regex.h"

Token *token;

bool ismatch(std::string input_str, std::string regex) {
    token = parser(regex);
    Node* head = expr();
    Trie* start_state = new Trie();
    std::queue<State*> que;
    que.push(start_state);
    compile_re(head, que);
    if (simulate(input_str, start_state)) {
        std::cout << "Matched!\n";
        return true;
    } else {
        std::cout << "Not matched...\n";
        return false;
    }
}

bool simulate(std::string input_str, State* head) {
    std::set<State*> now_states;
    now_states.insert(head);
    for (char chr: input_str) {
        tour_unlabeled(now_states);
        std::set<State*> new_states;
        for (State* state : now_states) {
            int sz = state->get_size(chr);
            for (int i = 0; i < sz; ++i) {
                new_states.insert(state->get(chr, i));
                /* std::cout << "NOW AT :" << chr << "\n"; */
            }
        }
        now_states = new_states;
    }
    tour_unlabeled(now_states);
    for (State* state: now_states) {
        if (state->isEnd()) 
            return true;
    }
    return false;
}

void tour_helper(std::set<State*>& unlabeled, State* now_state) {
    int sz = now_state->get_size('#');
    for (int i = 0; i < sz; ++i) {
        State* to_state = now_state->get('#', i);
        if (unlabeled.find(to_state) == unlabeled.end()) {
            unlabeled.insert(to_state);
            tour_helper(unlabeled, to_state);
        }
    }
}

void tour_unlabeled(std::set<State*>& now_states) {
    std::set<State*> unlabeled;
    for (State* now_state : now_states) {
        tour_helper(unlabeled, now_state);
    }
    for (State* unlabeled_state : unlabeled) {
        now_states.insert(unlabeled_state);
    }
}

