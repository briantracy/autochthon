

#include "memory.h"

#include "exceptions.h"


VMWord DebugMemory::readWord(VMWord address) const {
    const HostWord hostAddress = Intrinsic::toHostWord(address);

}