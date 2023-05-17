

#include <libavm/intrinsic.h>

namespace Intrinsic {
    HostWord toHostWord(VMWord vmword) {
        return static_cast<HostWord>(
            (static_cast<std::uint32_t>(vmword.at(3)) << 0) |
            (static_cast<std::uint32_t>(vmword.at(2)) << 8) |
            (static_cast<std::uint32_t>(vmword.at(1)) << 16) |
            (static_cast<std::uint32_t>(vmword.at(0)) << 24)
        );
    }
}