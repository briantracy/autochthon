

#include <iostream>
#include <vector>
#include <string_view>

int help() {
    std::cout << "avmdriver [run|dis|link]\n";
    std::cout << "avmdriver run <binary>\n";
    std::cout << "avmdriver dis <binary>\n";
    std::cout << "avmdriver link <binary> ... <binary>\n";
    return 0;
}

int main(int argc, char *argv[]) {
    const std::vector<std::string_view> args(argv, argv + argc);
    if (args.size() < 3) {
        return help();
    }
}

