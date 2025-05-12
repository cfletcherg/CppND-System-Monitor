#include "linux_parser.h"
#include <gtest/gtest.h>
#include <string>
#include <vector>

TEST(LinuxParserTest, MemoryUtilizationRange) 
{
  float util = LinuxParser::MemoryUtilization();
  EXPECT_GT(util, 0.0f);
  EXPECT_LT(util, 1.0f);
}

TEST(LinuxParserTest, UpTimePositive) 
{
  long up = LinuxParser::UpTime();
  EXPECT_GT(up, 0L);
  EXPECT_LT(up, 100000000L);
}

TEST(LinuxParserTest, CpuUtilizationLength)
{
  std::vector<std::string> cpu = LinuxParser::CpuUtilization();
  ASSERT_EQ(cpu.size(), 10u);
}

TEST(LinuxParserTest, TotalProcessesPositive)
{
    int total_processes = LinuxParser::TotalProcesses();
    EXPECT_GT(total_processes, 0L);
}

TEST(LinuxParserTest, RunningProcessesPositive)
{
    int running_processes = LinuxParser::RunningProcesses();
    EXPECT_GT(running_processes, 0L);
}

TEST(LinuxParserTest, JiffiesPositive)
{
    long active_jiffies = LinuxParser::ActiveJiffies();
    EXPECT_GT(active_jiffies, 0L);
}

TEST(LinuxParserTest, JiffiesComparison)
{
    long jiffies = LinuxParser::Jiffies();
    long idle_jiffies = LinuxParser::IdleJiffies();
    EXPECT_GT(jiffies, idle_jiffies);
}

TEST(LinuxParserTest, ProcessUpTimeReasonable) {
  long age = LinuxParser::UpTime(1);
  long sys = LinuxParser::UpTime();
  EXPECT_GE(age, 0L);
  EXPECT_LE(age, sys);
}