
#include <gtest/gtest.h>
#include <libavm/symbol.h>

#include <vector>



TEST(SymbolTest, SymbolTableParse) {
    EXPECT_EQ(SymbolTable::fromBytes({}, 0, 1), SymbolTable{});
    EXPECT_THROW(SymbolTable::fromBytes({1, 2, 3}, 0, 3), SymbolError);
    EXPECT_EQ(SymbolTable::fromBytes({
        0x01, 0x23, 0x45, 0x67, 0x0, 0x1, 0x1, 'm', 'a', 'i', 'n', '\0'
    }, 0, 12), SymbolTable({
        Symbol{0x01234567, Symbol::Kind::Function, Symbol::Linkage::External,
            Symbol::Visibility::Private, "main"}
    }));
    EXPECT_THROW(SymbolTable::fromBytes({
        0x01, 0x23, 0x45, 0x67, 0x0, 0x1, 0x1, 'm', 'a', 'i', 'n', '\0'
    }, 0, 11), SymbolError); // no null terminator

    EXPECT_EQ(SymbolTable::fromBytes({
        0x01, 0x23, 0x45, 0x67, 0x0, 0x1, 0x1, 'm', 'a', 'i', 'n', '\0', // 12
        0x01, 0x23, 0x45, 0x67, 0x0, 0x0, 0x0, 'x', 'y', '\0', // 10
        0x01, 0x23, 0x45, 0x67, 0x1, 0x1, 0x1, 'q', 'w', 'e', 'r', 't', 'y', 'z', '\0', // 15
    }, 0, 37), SymbolTable({
        Symbol{0x01234567, Symbol::Kind::Function, Symbol::Linkage::External,
            Symbol::Visibility::Private, "main"},
        Symbol{0x01234567, Symbol::Kind::Function, Symbol::Linkage::Internal,
            Symbol::Visibility::Public, "xy"},
        Symbol{0x01234567, Symbol::Kind::Data, Symbol::Linkage::External,
            Symbol::Visibility::Private, "qwertyz"}
    }));
}