#include "regex.h"

extern const int ALPHA_NUM;

class Trie {
    private:
        std::vector<Trie*> children;
    public:
        Trie() : children(ALPHA_NUM+1, nullptr) {};
};
