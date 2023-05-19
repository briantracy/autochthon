

#include <libavm/intrinsic.h>

#include <stdint.h>

namespace Intrinsic {
    HostWord toHostWord(VMWord vmWord) {
        return static_cast<HostWord>(
            (static_cast<uint32_t>(vmWord.at(3)) << 0) |
            (static_cast<uint32_t>(vmWord.at(2)) << 8) |
            (static_cast<uint32_t>(vmWord.at(1)) << 16) |
            (static_cast<uint32_t>(vmWord.at(0)) << 24)
        );
    }

    VMWord fromHostWord(HostWord hostWord) {
        return {
            static_cast<VMByte>((static_cast<uint32_t>(hostWord) & 0xFF000000) >> 24),
            static_cast<VMByte>((static_cast<uint32_t>(hostWord) & 0x00FF0000) >> 16),
            static_cast<VMByte>((static_cast<uint32_t>(hostWord) & 0x0000FF00) >> 8),
            static_cast<VMByte>((static_cast<uint32_t>(hostWord) & 0x000000FF) >> 0),
        };
    }
}