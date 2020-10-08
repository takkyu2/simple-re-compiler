#include "regex.h"

/* extern const int ALPHA_NUM; */

/* class Trie : public State { */
/*     private: */
/*         std::vector<std::vector<Trie*>> children; */
/*         bool endflag; */
/*         int chr_to_idx(char chr) { */
/*             if ('a' <= chr && chr <= 'z') { */
/*                 return chr - 'a'; */
/*             } else if ('A' <= chr && chr <= 'Z') { */
/*                 return 26 + (chr - 'A'); */
/*             } else if (chr == '#') { // unlabeled arrow is represenetd by # */
/*                 return ALPHA_NUM; */
/*             } else { */
/*                 std::cerr << "Error, not alphabet\n"; */
/*                 exit(1); */
/*             } */
/*         } */
/*     public: */
/*         Trie() : children(ALPHA_NUM+1), endflag {false} {}; */

/*         int get_size(char chr) override { */
/*             return children[chr_to_idx(chr)].size(); */
/*         } */

/*         Trie* get(char chr, int idx) override { */
/*             return children[chr_to_idx(chr)][idx]; */
/*         } */

/*         void set_to(char chr, State* to) override { */
/*             children[chr_to_idx(chr)].push_back(dynamic_cast<Trie*>(to)); */
/*         } */

/*         Trie* set(char chr) override { */
/*             int idx = chr_to_idx(chr); */
/*             Trie* newnode = new Trie(); */
/*             children[idx].push_back(newnode); */
/*             return newnode; */
/*         } */

/*         bool isEnd() override { */
/*             return endflag; */
/*         } */

/*         void setEnd() override { */
/*             endflag = true; */
/*         } */
/* }; */
