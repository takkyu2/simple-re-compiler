#include "regex.h"

int main(int argc, char** argv) {
    if (argc == 0) {
        std::cerr << "NO USER INPUT, EXIT\n";
        exit(1);
    }
    std::string user_input = argv[1];

    Token* head = parser(user_input);
    while (head != nullptr) {
        std::cout << head->chr << std::endl;
        head = head->next;
    }


}
