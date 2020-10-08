#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <set>

const int ALPHA_NUM = 26*2;

enum class Tokenkind {
    TERMINAL,
    SPECIAL,
    EOS,
};

enum class Nodekind {
    CONCAT,
    OR,
    QUESTION,
    STAR,
    PLUS,
    CHR,
    EOS,
};

struct Token {
    Tokenkind kind;
    char chr;
    Token* next;
    Token(char input_chr) : chr {input_chr}, kind {Tokenkind::TERMINAL}, next {nullptr} {};
};

struct Node {
    Nodekind kind;
    char chr;
    Node* lhs;
    Node* rhs;
    Node(char input_chr, Node* lhs, Node* rhs, Nodekind kind) : chr {input_chr}, lhs {lhs}, rhs {rhs}, kind {kind} {};
};

class State {
    public:
        virtual int get_size(char chr) = 0;
        virtual State* get(char chr, int idx) = 0;
        virtual State* set(char chr) = 0;
        virtual void set_to(char chr, State* to) = 0;
        virtual bool isEnd() = 0;
        virtual void setEnd() = 0;
};

Token* parser(std::string input);

Node* expr();
Node* primes();
Node* primary();
char expect_chr();
void expect(char op);
bool at_eos();
bool consume(char op);
void compile_re(Node* now, std::queue<State*>& nodelist);

extern const int ALPHA_NUM;

class Trie : public State {
    private:
        std::vector<std::vector<Trie*>> children;
        bool endflag;
        int chr_to_idx(char chr) {
            if ('a' <= chr && chr <= 'z') {
                return chr - 'a';
            } else if ('A' <= chr && chr <= 'Z') {
                return 26 + (chr - 'A');
            } else if (chr == '#') { // unlabeled arrow is represenetd by #
                return ALPHA_NUM;
            } else {
                std::cerr << "Error, not alphabet\n";
                exit(1);
            }
        }
    public:
        Trie() : children(ALPHA_NUM+1), endflag {false} {};

        int get_size(char chr) override {
            return children[chr_to_idx(chr)].size();
        }

        Trie* get(char chr, int idx) override {
            return children[chr_to_idx(chr)][idx];
        }

        void set_to(char chr, State* to) override {
            children[chr_to_idx(chr)].push_back(dynamic_cast<Trie*>(to));
        }

        Trie* set(char chr) override {
            int idx = chr_to_idx(chr);
            Trie* newnode = new Trie();
            children[idx].push_back(newnode);
            return newnode;
        }

        bool isEnd() override {
            return endflag;
        }

        void setEnd() override {
            endflag = true;
        }
};
void tour_helper(std::set<State*>& unlabeled, State* now_state);
void tour_unlabeled(std::set<State*>& now_states);
bool simulate(std::string input_str, State* head);
bool ismatch(std::string input_str, std::string regex);
