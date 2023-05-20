
#ifndef AVM_SYMBOL_H
#define AVM_SYMBOL_H

#include <libavm/intrinsic.h>

#include <stdexcept>
#include <stdint.h>
#include <string>
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
};

struct SymbolError : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

class SymbolTable {
    std::vector<Symbol> symbols_;
public:
    HostWord loadSymbol(HostWord index) const;
};

#endif
