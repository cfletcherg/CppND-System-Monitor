#include "format.h"
#include <gtest/gtest.h>

TEST(FormatTest, ZeroSeconds) {
  EXPECT_EQ( Format::ElapsedTime(0), "00:00:00" );
}

TEST(FormatTest, Typical) {
  // Test values come from <https://www.inchcalculator.com/seconds-to-time-calculator/>
  EXPECT_EQ( Format::ElapsedTime(8274), "02:17:54" );
}
