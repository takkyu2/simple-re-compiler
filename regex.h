#include <string>
#include <iostream>
#include <vector>

const int ALPHA_NUM = 26*2;

enum class Tokenkind {
    TERMINAL,
    SPECIAL,
};

struct Token {
    Tokenkind kind;
    char chr;
    Token* next;

    Token(char input_chr) : chr {input_chr}, kind {Tokenkind::TERMINAL}, next {nullptr} {};
};

Token* parser(std::string input);
