
#ifndef AVM_BINARYREADER_H
#define AVM_BINARYREADER_H

#include <cstdint>
#include <string>
#include <vector>

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

#endif