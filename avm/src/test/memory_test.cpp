
#include <gtest/gtest.h>

#include <libavm/intrinsic.h>
#include <libavm/memory.h>

#include <stdint.h>

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

    EXPECT_THROW(mem.writeByte(0, 0xAA), MemoryError);
    EXPECT_THROW(mem.writeByte(10, 0xAA), MemoryError);
    EXPECT_THROW(mem.writeByte(-1, 0xAA), MemoryError);
    constexpr VMWord word = {0xa, 0xb, 0xc, 0xd};
    EXPECT_THROW(mem.writeWord(addressSpaceSize - 3, word), MemoryError);
    EXPECT_THROW(mem.writeWord(addressSpaceSize - 2, word), MemoryError);
    EXPECT_THROW(mem.writeWord(addressSpaceSize - 1, word), MemoryError);
    EXPECT_THROW(mem.writeWord(0, word), MemoryError);
    EXPECT_THROW(mem.writeWord(0, word), MemoryError);
}