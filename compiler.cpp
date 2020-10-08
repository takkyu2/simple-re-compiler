#include "regex.h"

void compile_re(Node* now, std::queue<State*>& nodelist) {
    if (now == nullptr) return;
    int sz = nodelist.size();
    switch (now->kind) {
        case Nodekind::EOS:
            for (int i = 0; i < sz; ++i) {
                State* tmp = nodelist.front();nodelist.pop();
                tmp->setEnd();
            }
            return;
        case Nodekind::CHR:
            for (int i = 0; i < sz; ++i) {
                State* tmp = nodelist.front();nodelist.pop();
                nodelist.push(tmp->set(now->chr));
            }
            return;
        case Nodekind::CONCAT:
            compile_re(now->lhs, nodelist);
            compile_re(now->rhs, nodelist);
            return;
        case Nodekind::OR: {
            std::queue<State*> e1list, e2list;
            for (int i = 0; i < sz; ++i) {
                State* tmp = nodelist.front();nodelist.pop();
                e1list.push(tmp->set('#'));
                e2list.push(tmp->set('#'));
            }
            compile_re(now->lhs, e1list);
            compile_re(now->rhs, e2list);
            while (e1list.size()) {
                State* tmp = e1list.front();e1list.pop();
                nodelist.push(tmp);
            }
            while (e2list.size()) {
                State* tmp = e2list.front();e2list.pop();
                nodelist.push(tmp);
            }
            return;
        }
        case Nodekind::QUESTION: {
            std::queue<State*> e1list, e2list;
            for (int i = 0; i < sz; ++i) {
                State* tmp = nodelist.front();nodelist.pop();
                e1list.push(tmp->set('#'));
                e2list.push(tmp->set('#'));
            }
            compile_re(now->lhs, e1list);
            while (e1list.size()) {
                State* tmp = e1list.front();e1list.pop();
                nodelist.push(tmp);
            }
            while (e2list.size()) {
                State* tmp = e2list.front();e2list.pop();
                nodelist.push(tmp);
            }
            return;
        }
        case Nodekind::STAR : {
            for (int i = 0; i < sz; ++i) {
                State* tmp = nodelist.front();nodelist.pop();
                std::queue<State*> enow;
                enow.push(tmp->set('#'));
                compile_re(now->lhs, enow);
                while (enow.size()) {
                    State* tmp2 = enow.front();enow.pop();
                    tmp2->set_to('#', tmp);
                }
                nodelist.push(tmp->set('#'));
            }
            return;
        }
        case Nodekind::PLUS : {
            for (int i = 0; i < sz; ++i) {
                State* tmp = nodelist.front();nodelist.pop();
                std::queue<State*> enow;
                enow.push(tmp->set('#'));
                compile_re(now->lhs, enow);
                while (enow.size()) {
                    State* tmp2 = enow.front();enow.pop();
                    tmp2->set_to('#', tmp);
                    nodelist.push(tmp2);
                }
            }
            return;
        }
    }
}
