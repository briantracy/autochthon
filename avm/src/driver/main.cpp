

#include <iostream>

#include <libavm/symbol.h>

int main(int argc, char *argv[]) {

    std::cout << "avm driver: " << static_cast<std::uint8_t>(Symbol::Kind::Function) << '\n';
}

