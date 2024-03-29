
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

    // non increasing sections
    EXPECT_THROW(Program({
        0x00, 0x00, 0x00, 0x01,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0xc
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

    const auto emptyProgram = Program({
        0x00, 0x00, 0x00, 0x0c, // empty symbol table
        0x00, 0x00, 0x00, 0x0c, // empty data
        0x00, 0x00, 0x00, 0x0c, // empty code
    });
    EXPECT_EQ(emptyProgram.symbols, SymbolTable(std::vector<Symbol>{}));
    EXPECT_EQ(emptyProgram.data, std::vector<VMByte>{});
    EXPECT_EQ(emptyProgram.code, std::vector<VMByte>{});
}

TEST(ProgramTest, testProgramFromFile) {
    const auto helloWorld = Program{"src/test/programs/hello_world.bin"};
    EXPECT_EQ(
        std::string(reinterpret_cast<const char *>(helloWorld.data.data())),
        std::string{"hello world!"}
    );
    EXPECT_EQ(helloWorld.code, std::vector<VMByte>(8, 0xFF));

    EXPECT_THROW(Program{"/not/existent/path"}, ProgramLoadError);
}