
#include <gtest/gtest.h>
#include <lib/intrinsic.h>

TEST(IntrinsicTest, toHostWord) {
  EXPECT_EQ(0, Intrinsic::toHostWord({0, 0, 0, 0}));
  EXPECT_EQ(1, Intrinsic::toHostWord({0, 0, 0, 1}));
  EXPECT_EQ(255, Intrinsic::toHostWord({0, 0, 0, 0xFF}));
  EXPECT_EQ(-1, Intrinsic::toHostWord({0xFF, 0xFF, 0xFF, 0xFF}));
}