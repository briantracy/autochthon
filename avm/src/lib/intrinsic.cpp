

#include "intrinsic.h"

namespace Intrinsic {
    HostWord toHostWord(VMWord vmword) {
        return static_cast<HostWord>(
            (vmword & 0xFF000000)
        );
    }
}