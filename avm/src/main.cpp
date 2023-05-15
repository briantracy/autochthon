



#include <iostream>
#include <stdexcept>
#include <string>
#include <istream>
#include <cstdint>
#include <vector>
#include <string_view>
#include <utility>
#include <iterator>


int main(int const argc, const char *const argv[]) {
    (void)argc, (void)argv;

    BinaryReader reader{{'a', 'b', 'c'}};
    auto bytes = reader.readBytes(3);
    for (const auto &b : bytes) {
        std::cout << b << '\n';
    }
    //std::cout << reader.readString() << std::endl;

    return 0;
}
