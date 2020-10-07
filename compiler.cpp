#include "regex.h"

std::queue<State*> nownodes;

void comb_queues_with_nownodes(std::queue<State*>& destnodes) {
    std::set<State*> nodeset;
    while (destnodes.size()) {
        nodeset.insert(destnodes.front()); destnodes.pop();
    }
    while (nownodes.size()) {
        nodeset.insert(nownodes.front()); nownodes.pop();
    }
    for (State* elem : nodeset) {
        nownodes.push(elem);
    }
    return;
}

void compile_re(Node* now) {
    /* if (now == nullptr) return; */
    int sz = nownodes.size();
    switch (now->kind) {
        case Nodekind::EOS:
            for (int i = 0; i < sz; ++i) {
                State* tmp = nownodes.front();nownodes.pop();
                tmp->setEnd();
            }
            return;
        case Nodekind::CHR:
            for (int i = 0; i < sz; ++i) {
                State* tmp = nownodes.front();nownodes.pop();
                nownodes.push(tmp->set(now->chr));
            }
            return;
        case Nodekind::CONCAT:
            compile_re(now->lhs);
            compile_re(now->rhs);
            return;
        case Nodekind::OR: {
            std::queue<State*> orignodes = nownodes;
            compile_re(now->lhs);
            std::queue<State*> destnodes = nownodes;
            nownodes = orignodes;
            compile_re(now->rhs);
            comb_queues_with_nownodes(destnodes);
            return;
        }
        case Nodekind::QUESTION: {
            std::queue<State*> orignodes = nownodes;
            compile_re(now->lhs);
            comb_queues_with_nownodes(orignodes);
            return;
        }

    }
    compile_re(now->lhs);

    compile_re(now->rhs);
}
