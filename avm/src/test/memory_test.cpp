
#include <gtest/gtest.h>

#include <libavm/intrinsic.h>
#include <libavm/memory.h>

#include <stdint.h>

#include <iostream>

TEST(MemoryTest, debugMemory) {
    constexpr size_t addressSpaceSize = 10;
    auto mem = DebugMemory{addressSpaceSize};
    for (size_t i = 1; i < addressSpaceSize; ++i) {
        EXPECT_EQ(mem.readByte(static_cast<HostWord>(i)), 0xBB);
    }

    mem.writeByte(4, 0xAB);
    EXPECT_EQ(mem.readByte(4), 0xAB);

    mem.writeWord(5, {0x0a, 0x0b, 0x0c, 0x0d});
    EXPECT_EQ(0x0a0b0c0d, Intrinsic::toHostWord(mem.readWord(5)));
    std::vector<VMByte> bytes(4);
    mem.readRawBytes(5, 4, bytes);
    EXPECT_EQ(bytes.at(0), 0x0a);
    EXPECT_EQ(bytes.at(1), 0x0b);
    EXPECT_EQ(bytes.at(2), 0x0c);
    EXPECT_EQ(bytes.at(3), 0x0d);

    EXPECT_THROW(mem.writeByte(0, 0xAA), MemoryError);
    EXPECT_THROW(mem.writeByte(10, 0xAA), MemoryError);
    EXPECT_THROW(mem.writeByte(-1, 0xAA), MemoryError);
    constexpr VMWord word = {0xa, 0xb, 0xc, 0xd};
    EXPECT_THROW(mem.writeWord(addressSpaceSize - 3, word), MemoryError);
    EXPECT_THROW(mem.writeWord(addressSpaceSize - 2, word), MemoryError);
    EXPECT_THROW(mem.writeWord(addressSpaceSize - 1, word), MemoryError);
    EXPECT_THROW(mem.writeWord(0, word), MemoryError);
    EXPECT_THROW(mem.writeWord(0, word), MemoryError);
    std::cout << mem.debug();
}