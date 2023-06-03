
#ifndef AVM_INSTRUCTION_H
#define AVM_INSTRUCTION_H

#include <cstdint>
#include <cstddef>

enum class Opcode : std::uint8_t {
    Debug,
    LoadSymbol,
    LoadByte,
    LoadWord
};

namespace Instruction {
constexpr std::size_t LongestInstructionLength = 6;
}


#endif
