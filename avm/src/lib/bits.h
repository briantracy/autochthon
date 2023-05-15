
#ifndef AVM_BITS_H
#define AVM_BITS_H

#include <cstdint>
#include <tuple>

struct EndianConversion {
    using VMWord = std::tuple<std::uint8_t, std::uint8_t, std::uint8_t, std::uint8_t>;
    constexpr std::uint32_t unsignedWordFromBytes(VMWord word) {
        return (static_cast<std::uint32_t>(std::get<0>(word)) << 24) |
               (static_cast<std::uint32_t>(std::get<1>(word)) << 16) |
               (static_cast<std::uint32_t>(std::get<2>(word)) << 8)  |
               (static_cast<std::uint32_t>(std::get<3>(word)) << 0);
    }
};

#endif
