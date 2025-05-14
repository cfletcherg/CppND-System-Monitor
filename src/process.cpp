#include "process.h"

#include <unistd.h>

#include <cctype>
#include <sstream>
#include <string>
#include <vector>

using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
int Process::Pid()
{
  return pid_;
}

// TODO: Return this process's CPU utilization
// Taken from
// <https://stackoverflow.com/questions/16726779/how-do-i-get-the-total-cpu-usage-of-an-application-from-proc-pid-stat/16736599#16736599>
float Process::CpuUtilization() const
{
  auto total_time = LinuxParser::ActiveJiffies(pid_);
  auto seconds    = LinuxParser::UpTime() - LinuxParser::UpTime(pid_);
  if (seconds <= 0) return 0.0f;
  auto cpu_usage  = ((float(total_time) / sysconf(_SC_CLK_TCK)) / float(seconds));
  return cpu_usage;
}

// TODO: Return the command that generated this process
string Process::Command()
{
  return LinuxParser::Command(pid_);
}

// TODO: Return this process's memory utilization
string Process::Ram()
{
  return LinuxParser::Ram(pid_);
}

// TODO: Return the user (name) that generated this process
string Process::User()
{
  return LinuxParser::User(pid_);
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime()
{
  return LinuxParser::UpTime(pid_);
}

// TODO: Overload the "less than" comparison operator for Process objects
bool Process::operator<(Process const& a) const
{
  return this->CpuUtilization() > a.CpuUtilization();
}