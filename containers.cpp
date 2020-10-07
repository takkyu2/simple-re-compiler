#include "regex.h"

extern const int ALPHA_NUM;

class Trie : public State {
    private:
        std::vector<Trie*> children;
        bool endflag;
        int chr_to_idx(char chr) {
            if ('a' <= chr && chr <= 'z') {
                return chr - 'a';
            } else if ('A' <= chr && chr <= 'Z') {
                return 26 + (chr - 'A');
            } else {
                std::cerr << "Error, not alphabet\n";
                exit(1);
            }
        }
    public:
        Trie() : children(ALPHA_NUM+1, nullptr), endflag {false} {};

        Trie* get(char chr) override {
            return children[chr_to_idx(chr)];
        }

        Trie* set(char chr) override {
            int idx = chr_to_idx(chr);
            if (children[idx] != nullptr) {
                return children[idx];
            } else {
                Trie* next = new Trie();
                children[idx] = next;
                return next;
            }
        }

        bool isEnd() override {
            return endflag;
        }

        void setEnd() override {
            endflag = true;
        }
};
