#include "regex.h"

extern Token *token;

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
    Token *newtoken = new Token('A');
    newtoken->kind = Tokenkind::EOS;
    now->next = newtoken;

    Token* ans = head->next;
    delete head;
    return ans;
}

bool at_eos() {
    return token->kind == Tokenkind::EOS;
}

bool consume(char op) {
    if (token->kind == Tokenkind::SPECIAL && token->chr == op) {
        token = token->next;
        return true;
    }
    return false;
}

void expect(char op) {
    if (token->chr != op) {
        std::cerr << "Expect " << op << ", but we have " << token->chr << "\n";
        exit(1);
    }
    token = token->next;
}

char expect_chr() {
    if (token->kind != Tokenkind::TERMINAL) {
        std::cerr << "Expect number, but we have " << token->chr << "\n";
        exit(1);
    }
    char chr = token->chr;
    token = token->next;
    return chr;
}

Node* expr() {
    if (at_eos()) return new Node('E', nullptr, nullptr, Nodekind::EOS);
    Node* node = primes();
    return new Node('.', node, expr(), Nodekind::CONCAT);
}

Node* primes() {
    Node* node = primary();
    if (consume('?')) {
        return new Node('?', node, nullptr, Nodekind::QUESTION);
    } else if (consume('*')) {
        return new Node('*', node, nullptr, Nodekind::STAR);
    } else if (consume('+')) {
        return new Node('+', node, nullptr, Nodekind::PLUS);
    } else if (consume('|')) {
        return new Node('|', node, primary(), Nodekind::OR);
    } else {
        return node;
    }
}

Node* primary() {
    if (consume('(')) {
        Node* node = expr();
        expect(')');
        return node;
    }
    return new Node(expect_chr(), nullptr, nullptr, Nodekind::CHR);
}
