
#ifndef AVM_MEMORY_H
#define AVM_MEMORY_H

#include <libavm/intrinsic.h>

#include <stdexcept>
#include <vector>

/*
    The memory API is very straightforward: you can read/write single bytes and words.
    In addition, you can map in a swath of bytes.
*/
struct Memory {

    virtual VMWord readWord(HostWord address) const = 0;
    virtual void writeWord(HostWord address, VMWord word) = 0;

    virtual VMByte readByte(HostWord address) const = 0;
    virtual void writeByte(HostWord address, VMByte byte) = 0;

    virtual void map(HostWord startAddress, const std::vector<VMByte> &bytes) = 0;
};

struct MemoryError : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

/// Non paged, raw slab of memory
class DebugMemory : public Memory {

    std::vector<VMByte> rawMemory_;

public:

    DebugMemory(size_t addressSpaceSize) : rawMemory_(addressSpaceSize, 0xBB) {}

    VMWord readWord(HostWord address) const override;
    void writeWord(HostWord address, VMWord word) override;
    VMByte readByte(HostWord address) const override;
    void writeByte(HostWord address, VMByte byte) override;
    void map(HostWord startAddress, const std::vector<VMByte> &bytes) override;
};

#endif