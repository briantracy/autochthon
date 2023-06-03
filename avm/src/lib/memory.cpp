

#include <libavm/intrinsic.h>
#include <libavm/memory.h>

#include <algorithm>
#include <iomanip>
#include <stdint.h>
#include <string>
#include <sstream>

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

void DebugMemory::readRawBytes(HostWord startAddress, size_t numBytes, std::vector<VMByte> &dest) {
    if (startAddress <= 0 || numBytes < 0 ||
        static_cast<size_t>(startAddress) + numBytes >= rawMemory_.size()) {
        throw MemoryError{"readRawBytes of invalid address, size: " + std::to_string(startAddress) + ", " + std::to_string(numBytes)};
    }
    for (size_t i = 0; i < numBytes; ++i) {
        dest.at(i) = rawMemory_.at(static_cast<size_t>(startAddress) + i);
    }
}

std::string DebugMemory::debug() const {
    std::stringstream out;
    out << std::hex;
    for (size_t i = 0; i < rawMemory_.size(); ++i) {
        if (i % 16 == 0) {
            out << std::setfill('0') << std::setw(8) << i << ": ";
        }
        out << std::setfill('0') << std::setw(2)
            << static_cast<unsigned int>(rawMemory_.at(i));
        if ((i + 1) % 16 == 0) {
            out << '\n';
        } else if ((i + 1) % 4 == 0) {
            out << "  ";
        } else {
            out << ' ';
        }
    }
    if (rawMemory_.size() % 16 != 0) {
        out << '\n';
    }
    return out.str();
}