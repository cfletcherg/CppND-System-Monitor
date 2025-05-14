#include "processor.h"
#include <gtest/gtest.h>
#include <thread>

TEST(ProcessorTest, Initialization) {
  Processor cpu;
  float u0 = cpu.Utilization();
  EXPECT_GE(u0, 0.0f);
  EXPECT_LE(u0, 1.0f);
}

TEST(ProcessorTest, SteadyStateRange) {
  Processor cpu;
  cpu.Utilization();
  std::this_thread::sleep_for(std::chrono::seconds(1));
  float u1 = cpu.Utilization();
  EXPECT_GE(u1, 0.0f);
  EXPECT_LE(u1, 1.0f);
}
