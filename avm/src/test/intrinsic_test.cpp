
#include <gtest/gtest.h>
#include <lib/intrinsic.h>

TEST(IntrinsicTest, toHostWord) {
  EXPECT_EQ(0, Intrinsic::toHostWord(0));
}