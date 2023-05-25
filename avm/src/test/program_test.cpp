
#include <gtest/gtest.h>

#include <libavm/intrinsic.h>
#include <libavm/program.h>
#include <libavm/symbol.h>

#include <stdint.h>

TEST(ProgramTest, parseProgramFailures) {
    // Need three words at the start
    EXPECT_THROW(Program(std::vector<VMByte>{}), ProgramLoadError);
    EXPECT_THROW(Program({0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0x10, 0x11}), ProgramLoadError);

    // Negative offsets
    EXPECT_THROW(Program({
        0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0x00,
        0xFF, 0xFF, 0xFF, 0x01
    }), ProgramLoadError);

}

TEST(ProgramTest, parseProgramBasic) {
    const auto prog1 = Program({
        0x00, 0x00, 0x00, 0x0c, // empty symbol table
        0x00, 0x00, 0x00, 0x0c, // one byte of data (0xd)
        0x00, 0x00, 0x00, 0x0d, // one byte of code (0xc)
        0xDD, 0xCC
    });
    EXPECT_EQ(prog1.symbols, SymbolTable(std::vector<Symbol>{}));
    EXPECT_EQ(prog1.data, std::vector<VMByte>{0xDD});
    EXPECT_EQ(prog1.code, std::vector<VMByte>{0xCC});
}