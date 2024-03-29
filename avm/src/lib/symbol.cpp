
#include <ios>
#include <libavm/intrinsic.h>
#include <libavm/symbol.h>

#include <cassert>
#include <stdint.h>
#include <string>
#include <sstream>

namespace SymbolDetail {

Symbol::Kind validateSymbolKind(VMByte byte) {
    if (byte > static_cast<uint8_t>(Symbol::Kind::Data)) {
        throw SymbolError{"invalid symbol kind: " + std::to_string(byte)};
    }
    return static_cast<Symbol::Kind>(byte);
}
Symbol::Linkage validateSymbolLinkage(VMByte byte) {
    if (byte > static_cast<uint8_t>(Symbol::Linkage::External)) {
        throw SymbolError{"invalid symbol Linkage: " + std::to_string(byte)};
    }
    return static_cast<Symbol::Linkage>(byte);
}
Symbol::Visibility validateSymbolVisibility(VMByte byte) {
    if (byte > static_cast<uint8_t>(Symbol::Visibility::Private)) {
        throw SymbolError{"invalid symbol Visibility: " + std::to_string(byte)};
    }
    return static_cast<Symbol::Visibility>(byte);
}

std::string kindString(Symbol::Kind kind) {
    switch (kind) {
    case Symbol::Kind::Function: return "function";
    case Symbol::Kind::Data: return     "data    ";
    default: throw SymbolError{"invalid symbol kind: " + std::to_string(static_cast<uint8_t>(kind))};
    }
}
std::string linkageString(Symbol::Linkage linkage) {
    switch (linkage) {
    case Symbol::Linkage::Internal: return "internal";
    case Symbol::Linkage::External: return "external";
    default: throw SymbolError{"invalid symbol linkage: " + std::to_string(static_cast<uint8_t>(linkage))};
    }
}
std::string visibilityString(Symbol::Visibility vis) {
    switch (vis) {
    case Symbol::Visibility::Public: return  "public ";
    case Symbol::Visibility::Private: return "private";
    default: throw SymbolError{"invalid symbol visibility: " + std::to_string(static_cast<uint8_t>(vis))};
    }
}

}

bool Symbol::operator==(const Symbol &other) const {
    return location == other.location &&
        kind == other.kind && linkage == other.linkage &&
        visibility == other.visibility && name == other.name;
}

std::string Symbol::description() const {
    std::stringstream ss;
    ss << "0x" << std::hex << static_cast<uint32_t>(location) << ' '
        << SymbolDetail::kindString(kind) << ' '
        << SymbolDetail::linkageString(linkage) << ' '
        << SymbolDetail::visibilityString(visibility) << ' '
        << '`' << name << '\'';
    return ss.str();
}

std::string SymbolTable::description() const {
    std::stringstream ss;
    for (const auto &symbol : symbols_) {
        ss << symbol.description() << '\n';
    }
    return ss.str();
}

HostWord SymbolTable::loadSymbol(HostWord index) const {
    if (index < 0 || static_cast<size_t>(index) >= symbols_.size()) {
        throw SymbolError{"invalid symbol index: " + std::to_string(index)};
    }
    return symbols_.at(static_cast<size_t>(index)).location;
}

SymbolTable SymbolTable::fromBytes(const std::vector<VMByte> &bytes, size_t begin, size_t onePastEnd) {
    assert(begin <= onePastEnd);
    SymbolTable table;
    size_t i = begin;
    // A single symbol is at least this large (the name needs to be one character + NUL)
    constexpr size_t SYMBOL_MIN_SIZE = sizeof(VMWord) + sizeof(Symbol::Kind) +
        sizeof(Symbol::Linkage) + sizeof(Symbol::Visibility) + 2;
    while (true) {
        if (i + 1 >= onePastEnd) { break; }
        if (i + SYMBOL_MIN_SIZE >= onePastEnd) {
            throw SymbolError{"not enough space left for symbol: i=" + std::to_string(i) + " end:" + std::to_string(onePastEnd)};
        }
        const HostWord location = Intrinsic::toHostWord({
            bytes.at(i), bytes.at(i + 1), bytes.at(i + 2), bytes.at(i + 3)
        });
        const auto kind = SymbolDetail::validateSymbolKind(bytes.at(i + 4));
        const auto linkage = SymbolDetail::validateSymbolLinkage(bytes.at(i + 5));
        const auto visibility = SymbolDetail::validateSymbolVisibility(bytes.at(i + 6));
        size_t nameTerminatorByteIndex = onePastEnd;
        for (size_t j = i + 7; j < onePastEnd; ++j) {
            if (bytes.at(j) == 0) {
                nameTerminatorByteIndex = j;
                break;
            }
        }
        if (nameTerminatorByteIndex == onePastEnd) {
            throw SymbolError{"could not find null terminator for symbol name, start = " + std::to_string(begin)};
        }
        table.symbols_.emplace_back(Symbol{
            location, kind, linkage, visibility, std::string(reinterpret_cast<const char *>(&bytes.at(i + 7)))
        });
        i = nameTerminatorByteIndex + 1;
    }

    return table;
}