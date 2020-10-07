#include "regex.h"

Token* parser(std::string input) {
    Token* head = new Token('A');
    Token* now = head;
    for (char chr : input) {
        Token *newtoken = new Token(chr);
        if (chr == '(' || chr == ')' || chr == '?' || chr == '|' || chr == '+' || chr == '*') {
            newtoken->kind = Tokenkind::SPECIAL;
        } else if (!isalpha(chr)) {
            std::cerr << "ERROR:INVALID SYMBOL\n";
            exit(1);
        }
        now->next = newtoken;
        now = now->next;
    }
    Token* ans = head->next;
    delete head;
    return ans;
}

