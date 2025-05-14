#include "process.h"
#include "linux_parser.h"
#include <gtest/gtest.h>
#include <thread>

TEST(ProcessTest, CpuUtilizationRange) {
  int pid = getpid();
  Process me(pid);

  std::this_thread::sleep_for(std::chrono::seconds(1));
  float u = me.CpuUtilization();
  EXPECT_GE(u, 0.0f);
  EXPECT_LE(u, 1.0f);
}

TEST(ProcessTest, OperatorLess) {
  int pid1 = getpid();
  int pid2 = LinuxParser::Pids().front();
  Process a(pid1), b(pid2);
  bool a_hotter = a.CpuUtilization() > b.CpuUtilization();
  EXPECT_EQ(a < b, a_hotter);
}
