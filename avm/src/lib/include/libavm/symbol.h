
#ifndef AVM_SYMBOL_H
#define AVM_SYMBOL_H

#include <libavm/intrinsic.h>

#include <stdexcept>
#include <stdint.h>
#include <string>
#include <utility>
#include <vector>

struct Symbol {

    HostWord location;

    enum class Kind : uint8_t {
        Function, Data
    } kind;

    enum class Linkage : uint8_t {
        Internal, External
    } linkage;

    enum class Visibility : uint8_t {
        Public, Private
    } visibility;

    std::string name;

    bool operator==(const Symbol &) const;
    std::string description() const;
};

struct SymbolError : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

class SymbolTable {
    std::vector<Symbol> symbols_;
public:
    SymbolTable() = default;
    SymbolTable(std::vector<Symbol> s) : symbols_{std::move(s)} {}
    static SymbolTable fromBytes(const std::vector<VMByte> &bytes, size_t begin, size_t onePastEnd);

    HostWord loadSymbol(HostWord index) const;
    bool operator==(const SymbolTable &other) const { return symbols_ == other.symbols_; }
    std::string description() const;
};

#endif
