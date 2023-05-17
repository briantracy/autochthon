
#ifndef AVM_SYMBOL_H
#define AVM_SYMBOL_H

#include <cstdint>
#include <string>
#include <vector>

struct Symbol {

    std::int32_t location;

    enum class Kind : std::uint8_t {
        Function, Data
    } kind;

    enum class Linkage : std::uint8_t {
        Internal, External
    } linkage;

    enum class Visibility : std::uint8_t {
        Public, Private
    } visibility;

    std::string name;
};

class SymbolTable {

    std::vector<Symbol> symbols;
public:

    void merge(const SymbolTable &other);
};

#endif
