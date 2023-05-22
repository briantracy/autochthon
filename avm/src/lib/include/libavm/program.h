
#ifndef AVM_PROGRAM_H
#define AVM_PROGRAM_H

#include <libavm/intrinsic.h>
#include <libavm/symbol.h>

#include <stdint.h>
#include <string_view>
#include <vector>

class Program {
    SymbolTable symbols_;
    std::vector<VMByte> data_;
    std::vector<VMByte> code_;
public:
    explicit Program(std::vector<uint8_t> rawBytes);
    explicit Program(std::string_view filePath);
};

#endif
