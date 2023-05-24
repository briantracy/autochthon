
#include <libavm/intrinsic.h>
#include <libavm/symbol.h>

#include <cassert>
#include <stdint.h>
#include <string>

HostWord SymbolTable::loadSymbol(HostWord index) const {
    if (index < 0 || static_cast<size_t>(index) >= symbols_.size()) {
        throw SymbolError{"invalid symbol index: " + std::to_string(index)};
    }
    return symbols_.at(static_cast<size_t>(index)).location;
}

SymbolTable SymbolTable::fromBytes(const std::vector<VMByte> &bytes, size_t begin, size_t end) {
    assert(begin < end);
    SymbolTable table;
    size_t i = begin;
    // A single symbol is at least this large (the name needs to be one character + NUL)
    constexpr size_t SYMBOL_MIN_SIZE = sizeof(VMWord) + sizeof(Symbol::Kind) +
        sizeof(Symbol::Linkage) + sizeof(Symbol::Visibility) + 2;
    while (true) {
        if (end - i < SYMBOL_MIN_SIZE) {
            throw SymbolError{"not enough space left for symbol: i=" + std::to_string(i)};
        }
        const HostWord location = Intrinsic::toHostWord({
            bytes.at(i), bytes.at(i + 1), bytes.at(i + 2), bytes.at(i + 3)
        });

    }

    return table;
}