#include "regex.h"

extern Token *token;

std::string add_dots(std::string input) {
    std::string added_str;
    if (input.size() == 0) {
        std::cerr << "ERROR, empty string\n";
        exit(1);
    }
    added_str.push_back(input[0]);
    for (int i = 1; i < input.size(); ++i) {
        char fr = input[i-1], ba = input[i];
        if (fr == '|' || ba == '|' || fr == '(' || ba == ')' || ba == '?' || ba == '*' || ba == '+') {
            added_str.push_back(ba);
            continue;
        }
        added_str.push_back('.');
        added_str.push_back(ba);
    }
    return added_str;
}

Token* parser(std::string input) {
    input = add_dots(input);
    std::cout << input << "\n";
    Token* head = new Token('A');
    Token* now = head;
    for (char chr : input) {
        Token *newtoken = new Token(chr);
        if (chr == '(' || chr == ')' || chr == '?' || chr == '|' || chr == '+' || chr == '*' || chr == '.') {
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
        std::cerr << "Expect char, but we have " << token->chr << "\n";
        exit(1);
    }
    char chr = token->chr;
    token = token->next;
    return chr;
}

Node* expr() {
    Node* node = primes();
    if (consume('.')) 
        return new Node('.', node, expr(), Nodekind::CONCAT);
    else {
        if (at_eos()) {
            Node* rhs =  new Node('E', nullptr, nullptr, Nodekind::EOS);
            return new Node('.', node, rhs, Nodekind::CONCAT);
        } else 
            return node;
    }
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
    char chr = expect_chr();
    /* std::cout << chr << "\n"; */
    return new Node(chr, nullptr, nullptr, Nodekind::CHR);
}
