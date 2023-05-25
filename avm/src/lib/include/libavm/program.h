
#ifndef AVM_PROGRAM_H
#define AVM_PROGRAM_H

#include <libavm/intrinsic.h>
#include <libavm/symbol.h>

#include <stdexcept>
#include <stdint.h>
#include <string_view>
#include <vector>

struct Program {
    SymbolTable symbols;
    std::vector<VMByte> data;
    std::vector<VMByte> code;

    Program() = delete;
    explicit Program(const std::vector<VMByte> &rawBytes);
    explicit Program(std::string_view filePath);
private:
    void parse(const std::vector<VMByte> &rawBytes);
};

struct ProgramLoadError : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

#endif
