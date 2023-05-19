
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
}