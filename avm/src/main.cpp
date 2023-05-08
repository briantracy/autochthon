



#include <iostream>
#include <stdexcept>
#include <string>
#include <istream>
#include <cstdint>
#include <vector>
#include <string_view>
#include <utility>
#include <iterator>


struct EndianConversion {
    using VMWord = std::tuple<std::uint8_t, std::uint8_t, std::uint8_t, std::uint8_t>;
    constexpr std::uint32_t unsignedWordFromBytes(VMWord word) {
        return (static_cast<std::uint32_t>(std::get<0>(word)) << 24) |
               (static_cast<std::uint32_t>(std::get<1>(word)) << 16) |
               (static_cast<std::uint32_t>(std::get<2>(word)) << 8)  |
               (static_cast<std::uint32_t>(std::get<3>(word)) << 0);
    }
};

struct BinaryReaderError : public std::runtime_error {
    using std::runtime_error::runtime_error;
    virtual ~BinaryReaderError() {}
};

/**
 *
 */
class BinaryReader {

    std::vector<std::uint8_t> buffer_;
    std::uint64_t index_ = 0;

public:

    BinaryReader(std::vector<std::uint8_t> buff) : buffer_{std::move(buff)} {}

    bool canRead() {
        return index_ < buffer_.size();
    }

    std::uint8_t readByte() {
        if (canRead()) {
            return buffer_.at(index_++);
        } else {
            throw BinaryReaderError{"read past end of binary of size " + std::to_string(buffer_.size())};
        }
    }

    std::vector<std::uint8_t> readBytes(const std::size_t n) {
        if (index_ + n > buffer_.size()) {
            throw BinaryReaderError{"read of " + std::to_string(n) + " bytes, which is over the size"};
        }
        std::vector<std::uint8_t> ret(n);
        std::copy(
            buffer_.begin() + static_cast<std::int64_t>(index_),
            buffer_.begin() + static_cast<std::int64_t>(index_ + n),
            ret.begin()
        );
        return ret;
    }

    std::string readString() {
        std::string out{};
        std::uint8_t byte = 0;
        while ((byte = readByte()) != 0) {
            out.push_back(static_cast<char>(byte));
        }
        return out;
    }
};


struct Symbol {

    std::int32_t location;

    enum class Kind {
        Function, Data
    } kind;

    enum class Linkage {
        Internal, External
    } linkage;

    enum class Visibility {
        Public, Private
    } visibility;

    std::string name;
};

class SymbolTable {

    std::vector<Symbol> symbols;
public:

    void merge(const SymbolTable &other);
};


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
