
#ifndef AVM_MEMORY_H
#define AVM_MEMORY_H

#include <vector>

#include "intrinsic.h"

struct Memory {

    virtual VMWord readWord(VMWord address) const = 0;
    virtual void writeWord(VMWord address, VMWord word) = 0;

    virtual VMByte readByte(VMWord address) const = 0;
    virtual void writeByte(VMWord address, VMByte byte) = 0;

    virtual void map(VMWord startAddress, const std::vector<VMByte> &bytes) = 0;
};


class DebugMemory : public Memory {

    std::vector<VMByte> rawMemory_;

public:
    VMWord readWord(VMWord address) const override;
};

#endif