
#ifndef AVM_PROGRAM_H
#define AVM_PROGRAM_H

#include <libavm/intrinsic.h>
#include <libavm/symbol.h>

#include <stdexcept>
#include <stdint.h>
#include <string_view>
#include <vector>

class Program {
    SymbolTable symbols_;
    std::vector<VMByte> data_;
    std::vector<VMByte> code_;
    void parse(const std::vector<VMByte> &rawBytes);
public:
    Program() = delete;
    explicit Program(const std::vector<VMByte> &rawBytes);
    explicit Program(std::string_view filePath);
};

struct ProgramLoadError : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

#endif
