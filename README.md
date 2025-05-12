# CppND-System-Monitor

Starter code for System Monitor Project in the Object Oriented Programming Course of the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213).

Follow along with the classroom lesson to complete the project!

![System Monitor](images/monitor.png)

## Udacity Linux Workspace

[Udacity](https://www.udacity.com/) provides a browser-based Linux [Workspace](https://engineering.udacity.com/creating-a-gpu-enhanced-virtual-desktop-for-udacity-497bdd91a505) for students.

You are welcome to develop this project on your local machine, and you are not required to use the Udacity Workspace. However, the Workspace provides a convenient and consistent Linux development environment we encourage you to try.

## ncurses

[ncurses](https://www.gnu.org/software/ncurses/) is a library that facilitates text-based graphical output in the terminal. This project relies on ncurses for display output.

Within the Udacity Workspace, `.student_bashrc` automatically installs ncurses every time you launch the Workspace.

If you are not using the Workspace, install ncurses within your own Linux environment: `sudo apt install libncurses5-dev libncursesw5-dev`

## Make

This project uses [Make](https://www.gnu.org/software/make/). The Makefile has four targets:

* `build` compiles the source code and generates an executable
* `format` applies [ClangFormat](https://clang.llvm.org/docs/ClangFormat.html) to style the source code
* `debug` compiles the source code and generates an executable, including debugging symbols
* `clean` deletes the `build/` directory, including all of the build artifacts

## Instructions

1. Clone the project repository: `git clone https://github.com/udacity/CppND-System-Monitor-Project-Updated.git`

2. Build the project: `make build`

3. Run the resulting executable: `./build/monitor`
![Starting System Monitor](images/starting_monitor.png)

4. Follow along with the lesson.

5. Implement the `System`, `Process`, and `Processor` classes, as well as functions within the `LinuxParser` namespace.

6. Submit!

## Notes

* Linux stores a lot of system data in files within the `/proc` directory. Most of the data that this project requires exists in those files.
* **Operating System:** Information about the operating system exists outside of the `/proc` directory, in the `/etc/os-release` file.
  * `PRETTY NAME="Ubuntu 22.04.5 LTS"`
* **Kernel:** Information about the kernel exists /proc/version file. `cat /proc/version`
* **Memory Utilization:** Information about memory utilization exists in the /proc/meminfo file. `cat /proc/meminfo`
  * There are a variety(opens in a new tab) of ways(opens in a new tab) to use this data to calculate memory utilization. Hisham H. Muhammad(opens in a new tab), the author of htop(opens in a new tab), wrote a Stack Overflow answer(opens in a new tab) about how htop calculates memory utilization from the data in `/proc/meminfo`. Use the formula that makes the most sense to you!

htop author here. These are the calculations I make to get the numbers for the green, blue and yellow bars in the memory meter:

* Total used memory = MemTotal - MemFree
* Non cache/buffer memory (green) = Total used memory - (Buffers + Cached memory)
* Buffers (blue) = Buffers
* Cached memory (yellow) = Cached + SReclaimable - Shmem
* Swap = SwapTotal - SwapFree

* **Total Processes:** Information about the total number of processes on the system exists in the /proc/stat file.
* **Running Processes:** Information about the number of processes on the system that are currently running exists in the /proc/meminfo file. `cat /proc/stat`
* **Up Time:** Information about system up time exists in the `/proc/uptime` file.
  * This file contains two numbers (values in seconds): the uptime of the system (including time spent in suspend) and the amount of time spent in the idle process.

* Maybe use locally saved UpTime value instead of reparsing
* To convert from clock ticks:

```c++
#include <unistd.h>(opens in a new tab)
```

divide the "clock ticks" value by sysconf(_SC_CLK_TCK)
