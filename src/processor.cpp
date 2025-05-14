#include "processor.h"
#include "linux_parser.h"
#include <vector>
#include <string>

// TODO: Return the aggregate CPU utilization
float Processor::Utilization()
{
  long total_ticks  = LinuxParser::Jiffies();
  long idle_ticks   = LinuxParser::IdleJiffies();
  long active_ticks = LinuxParser::ActiveJiffies();

  auto total_difference = total_ticks - PrevTotal;
  auto idle_difference  = idle_ticks - PrevIdle;

  float cpu_percentage =
      float((total_difference - idle_difference)) / float(total_difference);

  PrevTotal   = total_ticks;
  PrevIdle    = idle_ticks;
  PrevNonIdle = active_ticks;

  return cpu_percentage;
}