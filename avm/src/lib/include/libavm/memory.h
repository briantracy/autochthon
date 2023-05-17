
#ifndef AVM_MEMORY_H
#define AVM_MEMORY_H

#include <libavm/intrinsic.h>

#include <vector>

struct Memory {

    virtual HostWord readWord(HostWord address) const = 0;
    virtual void writeWord(HostWord address, HostWord word) = 0;

    virtual VMByte readByte(HostWord address) const = 0;
    virtual void writeByte(HostWord address, VMByte byte) = 0;

    virtual void map(HostWord startAddress, const std::vector<VMByte> &bytes) = 0;
};


class DebugMemory : public Memory {

    std::vector<VMByte> rawMemory_;

public:
    HostWord readWord(HostWord address) const override;
};

#endif