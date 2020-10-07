#include <string>
#include <iostream>
#include <vector>

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

Token* parser(std::string input);

Node* expr();
Node* primes();
Node* primary();
char expect_chr();
void expect(char op);
bool at_eos();
bool consume(char op);
