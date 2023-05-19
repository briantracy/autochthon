

#include "libavm/intrinsic.h"
#include <libavm/memory.h>

#include <algorithm>
#include <stdint.h>
#include <string>

VMWord DebugMemory::readWord(HostWord address) const {
    if (address <= 0 || static_cast<size_t>(address) + sizeof(VMWord) > rawMemory_.size()) {
        throw MemoryError{"read from invalid address: " + std::to_string(address)};
    }
    VMWord out{};
    std::copy(rawMemory_.begin() + address, rawMemory_.begin() + address + sizeof(VMWord), out.begin());
    return out;
}

void DebugMemory::writeWord(HostWord address, VMWord word) {
    if (address <= 0 || static_cast<size_t>(address) + word.size() > rawMemory_.size()) {
        throw MemoryError{"write to invalid address: " + std::to_string(address)};
    }
    std::copy(word.begin(), word.end(), rawMemory_.begin() + address);
}

VMByte DebugMemory::readByte(HostWord address) const {
    if (address <= 0 || static_cast<size_t>(address) >= rawMemory_.size()) {
        throw MemoryError{"write to invalid address: " + std::to_string(address)};
    }
    return rawMemory_.at(static_cast<size_t>(address));
}
void DebugMemory::writeByte(HostWord address, VMByte byte) {
    if (address <= 0 || static_cast<size_t>(address) >= rawMemory_.size()) {
        throw MemoryError{"write to invalid address: " + std::to_string(address)};
    }
    rawMemory_.at(static_cast<size_t>(address)) = byte;
}

void DebugMemory::map(HostWord startAddress, const std::vector<VMByte> &bytes) {
    if (startAddress <= 0 || static_cast<size_t>(startAddress) + bytes.size() >= rawMemory_.size()) {
        throw MemoryError{"invalid mapping to start address: " + std::to_string(startAddress) + " of length: " + std::to_string(bytes.size())};
    }
    std::copy(bytes.begin(), bytes.end(), rawMemory_.begin() + startAddress);
}
