#include <dirent.h>
#include <unistd.h>
#include <sstream>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() 
{
  string line{}, key{}, mem_size_type{};
  long value{};
  float mem_total{0}, mem_free{0};
  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  if (stream.is_open())
  {
    while(std::getline(stream, line))
    {
      std::istringstream linestream(line);
      while(linestream >> key >> value >> mem_size_type)
      {
        if (key == "MemTotal:")
        {
          mem_total = static_cast<float>(value);
        }
        if (key == "MemFree:")
        {
          mem_free = static_cast<float>(value);
        }
        if (mem_total > 0 && mem_free > 0)
        {
          break;
        }
      }
    }
  }
  float used_memory = (mem_total - mem_free)/ mem_total;
  return used_memory; 
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() 
{
  string line{};
  long up_time{}, idle_time{};
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open())
  {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> up_time >> idle_time;
  }
  return up_time;
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() 
{
  long jiffies{};
  auto values = CpuUtilization();
  for (auto val : values)
  {
    jiffies += std::stol(val);
  }
  
  return jiffies;
}

// TODO: Read and return the number of active jiffies for a PID
long LinuxParser::ActiveJiffies(int pid) 
{
  string line{}, temp{};
  long jiffies{}, utime{}, stime{}, cutime{}, cstime{};
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatFilename);
  if (stream.is_open())
  {
    std::getline(stream, line);
    std::istringstream linestream(line);
    for (auto i=0; i<13; i++) linestream >> temp;
    linestream >> utime >> stime >> cutime >> cstime;
  }
  jiffies = utime + stime + cutime + cstime;
  return jiffies;
}

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() 
{
  return Jiffies() - IdleJiffies();
}

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() 
{
  long idle_jiffies{};
  auto values = CpuUtilization();
  idle_jiffies += std::stol(values[CPUStates::kIdle_]) + std::stol(values[CPUStates::kIOwait_]);
  return idle_jiffies;
}

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() 
{
  vector<string> cpu;
  string line_name, user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice;
  string line{};
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open())
  {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> line_name >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal >> guest >> guest_nice;
  }
  cpu.emplace_back(user);
  cpu.emplace_back(nice);
  cpu.emplace_back(system);
  cpu.emplace_back(idle);
  cpu.emplace_back(iowait);
  cpu.emplace_back(irq);
  cpu.emplace_back(softirq);
  cpu.emplace_back(steal);
  cpu.emplace_back(guest);
  cpu.emplace_back(guest_nice);
  return cpu; 
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() 
{
  int total_processes{};
  string line{}, line_name{};
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open())
  {
    while (std::getline(stream, line))
    {
      std::istringstream linestream(line);
      linestream >> line_name;
      if (line_name != "processes") continue;
      else linestream >> total_processes;
    }
  }
  return total_processes; 
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() 
{
  int running_processes{};
  string line{}, line_name{};
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open())
  {
    while (std::getline(stream, line))
    {
      std::istringstream linestream(line);
      linestream >> line_name;
      if (line_name != "procs_running") continue;
      else linestream >> running_processes;
    }
  }
  return running_processes;
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) 
{
  const long ticks_per_second = sysconf(_SC_CLK_TCK); // [ticks/seconds]

  string line{}, temp{};
  long starttime{}; // [ticks]
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatFilename);
  if (stream.is_open())
  {
    std::getline(stream, line);
    std::istringstream linestream(line);
    for (auto i=0; i<21; i++) linestream >> temp;
    linestream >> starttime;
  }

  long pid_uptime{};

  long system_uptime = LinuxParser::UpTime(); // [seconds]

  pid_uptime = system_uptime - starttime/ticks_per_second; 

  return pid_uptime; // [seconds]
}
