
#include <libavm/symbol.h>

#include <stdint.h>
#include <string>

HostWord SymbolTable::loadSymbol(HostWord index) const {
    if (index < 0 || static_cast<size_t>(index) >= symbols_.size()) {
        throw SymbolError{"invalid symbol index: " + std::to_string(index)};
    }
    return symbols_.at(static_cast<size_t>(index)).location;
}