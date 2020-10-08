#include "regex.h"

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "INVALID USER INPUT, EXIT\n";
        exit(1);
    }
    std::string user_input = argv[1], regex = argv[2];
    if (ismatch(user_input, regex)) {
        return 1;
    } else {
        return 0;
    }
}
